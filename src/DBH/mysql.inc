<?php
	/* $Id$ */
	require_once 'CPL.inc';

	CPL::define("DB_COL",	1);
	CPL::define("DB_ROW",	2);
	CPL::define("DB_ROWS",	3);
	CPL::define("DB_NULL",	4);

	CPL::define("SQL_WILD",		1); # Wildcard character strings
	CPL::define("SQL_REG",		2); # Regular strings
	CPL::define("SQL_REGEX",	3); # Regular expression strings
	CPL::define("SQL_RE",		3);
	CPL::define("SQL_REGEXP",	3);

	class DBH_MySQL {
		var $link_id;
		var $result_id;

		function DBH_MySQL() {
			static $saved = array();

			$args = func_get_args();
			$argc = func_num_args();

			if (is_array($args[0])) {
				$host = @$args[0]['host'];
				$username = @$args[0]['username'];
				$password = @$args[0]['password'];
				$database = @$args[0]['database'];
			} else if ($argc == 4) {
				$host = $args[0];
				$username = $args[1];
				$password = $args[2];
				$database = $args[3];
			} else {
				$this->handle_error("Invalid call to DBH constructor, check arguments");
			}

			# Check if an (exact) instance already exists
			foreach ($saved as $i_saved) {
				if ($i_saved['host'] == $host &&
				    $i_saved['username'] == $username &&
				    $i_saved['password'] == $password) {
					$this->link_id = $i_saved['link_id'];
					/* This is probably dangerous... */
					$this->select_database($database);
					return ($this);
				}
			}

			$this->link_id = @mysql_pconnect($host,$username,$password);

			if (!$this->link_id)
				$this->handle_error("Cannot connect to database; " .
				    "host: $host; username: $username; using password: yes");

			$this->select_database($database);

			array_push($saved, array (
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
			if (!@mysql_select_db($new_db, $this->link_id))
				$this->handle_error("Cannot select database; database: $database");
			$saved[$this->link_id] = $new_db;
		}

		function query($stmt, $type) {
			# mysql_unbuffered_query()?
			$this->result_id = @mysql_query($stmt,$this->link_id);

			if (!$this->result_id)
				$this->handle_error("Unable to query database; query: $stmt");
			switch ($type) {
			case DB_COL:
				# Grab first data row/column value
				$data = @mysql_result($this->result_id, 0, 0);
				mysql_free_result($this->result_id);
				return ($data);
#				return $this->normalize_data($data);
			case DB_ROW:
				/*
				 * Return first row.  We should probably use
				 * $this->fetch_row() to do this.
				 */
				$data = @mysql_fetch_array($this->result_id); // db_assoc ?
				mysql_free_result($this->result_id);
				return ($data);
#				return $this->normalize_data($data);
			case DB_ROWS:
				# No errors, let user call fetch_row() to gather data
				return 1;
			case DB_NULL:
				/* No data expected, return number of rows. */
				return (mysql_affected_rows($this->link_id));
			default:
				$this->handle_error("Invalid query type; type: $type");
			}
		}

		function last_insert_id() {
			$id = @mysql_insert_id($this->link_id);
			if (!$id)
				$this->handle_error("Could not fetch last insert id");
			return ($id);
		}

		function num_rows() {
			if ($this->result_id)
				return @mysql_num_rows($this->result_id);
			return (0);
		}

		function fetch_row() {
			if ($this->result_id) {
				if (@mysql_num_rows($this->result_id)) {
					$data = @mysql_fetch_array($this->result_id);

					if ($data) {
						return ($data);
#						return $this->normalize_data($data);
					} else {
						# No data gathered, result set must be diminished
						mysql_free_result($this->result_id);
						unset($this->result_id);
					}
				} else {
					@mysql_free_result($this->result_id);
					unset($this->result_id);
				}
			}
			return (0);
		}

		function disconnect() {
			if ($this->link_id) {
				if (!@mysql_close($this->link_id))
					$this->handle_error("Cannot disconnect from database");
			} else
				@mysql_close();
			unset($this->link_id);
		}

		function handle_error($msg) {
			$msg .= "; MySQL error=" . ($this->link_id ? mysql_error($this->link_id) : mysql_error());

			/* disconnect() may call us again. */
#			$this->disconnect();
			CPL::handle_error($msg);
			exit(1);
		}

		# Make a string safe to place in an SQL query
		function prepare_str($str, $type = SQL_REG) {
			switch ($type) {
			case SQL_WILD:
				/* Escape `%' and `_' with `\'. */
				$str = preg_replace("/[\\\"'_%]/", "\\\\1", $str);
				break;
			case SQL_REG:
				$str = addSlashes($str);
				break;
			case SQL_REGEX:
				/* Escape metachars with `\'. */
				$str = preg_replace("/[\\\"'\$^()\[\]{}+*?.]/", "\\\\1", $str);
				break;
			default:
				CPL::handle_error("Unknown sql_safe type; type: $type");
			}
			return ($str);
		}

		# "Normalizes" data received from the database
		function normalize_data($data) {
			/* Undo any magic quotes */
			if (ini_get('magic_quotes_runtime')) {
				if (is_array($data)) {
					foreach ($data as $key => $value)
						$data[$key] = stripSlashes($value);
				} else
					$data = stripSlashes($data);
			}
			return ($data);
		}
	}
?>
