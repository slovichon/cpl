<?php
	/* $Id$ */
	require_once 'CPL.inc';

	CPL::define("DB_COL",	1);
	CPL::define("DB_ROW",	2);
	CPL::define("DB_ROWS",	3);
	CPL::define("DB_NULL",	4);

	CPL::define("SQL_WILD",	1); # Wildcard character strings
	CPL::define("SQL_REG",	2); # Regular strings
	CPL::define("SQL_REGEX",	3); # Regular expression strings

	class DBH_mSQL {
		var $link_id;
		var $result_id;
		var $_last_table;

		function DBH_mSQL($host, $username, $password, $database) {
			static $saved = array();

			# Check if an (exact) instance already exists
			foreach ($saved as $i_saved) {
				if ($i_saved['host'] == $host &&
				    $i_saved['username'] == $username &&
				    $i_saved['password'] == $password) {
					$this->link_id = $i_saved['link_id'];
					$this->select_database($database);
					return ($this);
				}
			}

			$this->link_id	= @msql_pconnect($host, $username, $password);

			if (!$this->link_id)
				$this->handle_error("Cannot connect to database; "
				    "host: $host; username: $username; using password: yes");

			$this->select_database($database);

			array_push($saved, array(
				'link_id'	=> $this->link_id,
				'host'		=> $host,
				'username'	=> $username,
				'password'	=> $password
			));
		}

		function select_database($new_db) {
			static $saved = array();

			if (@$saved[$this->link_id] == $new_db)
				return;

			@msql_select_db($new_db,$this->link_id) ||
				$this->handle_error("Cannot select database; database=$database");

			$saved[$this->link_id] = $new_db;
		}

		function query($stmt,$type) {
			$this->result_id = @msql_query($stmt, $this->link_id);

			if (!$this->result_id)
				$this->handle_error("Unable to query database; query=$stmt");

			switch ($type) {
			case DB_COL:
				$data = @msql_result($this->result_id, 0, 0);
				msql_free_result($this->result_id);
				return ($data);
			case DB_ROW:
				$data = @msql_fetch_array($this->result_id);
				msql_free_result($this->result_id);
				return ($data);
			case DB_ROWS:
				return 1;
			case DB_NULL:
				/* Could possibly want last insert ID */
				if (preg_match("/^\s*insert\s+into\s+(\w+)/i", $stmt, $matches))
					$this->_last_table = $matches[1];
				return (msql_affected_rows($this->link_id));
			default:
				$this->handle_error("Invalid query type; type=$type");
			}
		}

		function last_insert_id() {
			/*
			 * Let's hope no one made an UPDATE or other row modification
			 * after inserting a row
			 */
			$id = $this->query("
				SELECT
					_rowid
				FROM
					{$this->_last_table}
				ORDER BY
					_timestamp DESC
				LIMIT
					1",DB_COL);
			if (!$id)
				$this->handle_error("Could not fetch last insert ID");
			return ($id);
		}

		function num_rows() {
			if ($this->result_id)
				return @msql_num_rows($this->result_id);
			return (0);
		}

		function fetch_row() {
			if ($this->result_id) {
				if (@msql_num_rows($this->result_id)) {
					$data = @msql_fetch_array($this->result_id);

					if ($data)
						return ($data);
					else
						msql_free_result($this->result_id);
				} else {
					@msql_free_result($this->result_id);
					unset($this->result_id);
				}
			}
			return (0); /* XXX: null */
		}

		function disconnect() {
			if ($this->link_id)
				@msql_close($this->link_id) ||
				    $this->handle_error("Cannot disconnect from database");
			else
				@msql_close();

			$this->link_id = 0;
		}

		function handle_error($msg) {
			$msg .= "; mSQL error=" . ($this->link_id ? msql_error($this->link_id) : msql_error());
			/* $this->disconnect(); */
			CPL::handle_error($msg);
			exit();
		}

		# Make a string safe to place in an SQL query
		function prepare_str($str, $type) {
			switch ($type) {
			case SQL_WILD:
				/* Escape `%' and `_' with `\'.
				$str = preg_replace("/[\\\"'_%]/","\\\\1",$str);
				break;
			case SQL_REG:
				$str = addSlashes($str);
				break;
			case SQL_REGEX:
				/* Escape metachars with `\'. */
				$str = preg_replace("/[\\\"'\$^()\[\]{}+*?.]/","\\\\1",$str);
				break;
			default:
				CPL::handle_error("Unknown escape type; type: $type");
			}
			return ($str);
		}
	}
?>
