<?php
	# Version: 1.7

	require_once 'CPL/1.0.inc';

	CPL::define("DB_COL",	1);
	CPL::define("DB_ROW",	2);
	CPL::define("DB_ROWS",	3);
	CPL::define("DB_NULL",	4);

	CPL::define("SQL_WILD",	1); # Wildcard character strings
	CPL::define("SQL_REG",	2); # Regular strings
	CPL::define("SQL_REGEX",	3); # Regular expression strings
	CPL::define("SQL_RE",		3);
	CPL::define("SQL_REGEXP",	3);

	class DBH_PostgreSQL
	{
		var $link_id;
		var $result_id;
		var	$_host,
			$_username,
			$_password;

		function DBH_PostgreSQL($host,$username,$password,$database)
		{
			static $saved = array();

			# Check if an (exact) instance already exists
			foreach ($saved as $i_saved)
			{
				if
				(
					$i_saved['host']	== $host	&&
					$i_saved['username']	== $username	&&
					$i_saved['password']	== $password
				)
				{
					$this->link_id = $i_saved['link_id'];

/*
 * Okay this one will be expensive
 */
#					$this->select_database($database);

					return $this;
				}
			}

			$this->link_id	= @pg_pconnect("host=$host user=$username password=$password dbname=$database");

			if (!$this->link_id)
				$this->handle_error("Cannot connect to database; host: $host; username: $username; using password: yes");

			$this->_host		= $host;
			$this->_username	= $username;
			$this->_password	= $password;

			array_push
			(
				$saved,
				array
				(
					'link_id'	=> $this->link_id,
					'host'		=> $host,
					'username'	=> $username,
					'password'	=> $password
				)
			);

			return $this;
		}

		function select_database($new_db)
		{
			static $saved = array();

			if (@$saved[$this->link_id] == $new_db)
				return;

			$o = new DBH_PostgreSQL($this->_host,$this->_username,$this->_password,$new_db);

			$this->link_id		= $o->link_id;
			$this->result_id	= NULL;

			$saved[$this->link_id] = $new_db;

			return;
		}

		function query($stmt,$type)
		{
			$this->result_id	= @pg_query($stmt,$this->link_id);

			if (!$this->result_id)
				$this->handle_error("Unable to query database; query=$stmt");

			switch ($type)
			{
				case DB_COL:
				{
					$data	= @pg_result($this->result_id,0,0);
					pg_free_result($this->result_id);

					return $data;
				}

				case DB_ROW:
				{
					$data	= @pg_fetch_array($this->result_id);
					pg_free_result($this->result_id);

					return $data;
				}

				case DB_ROWS:
				{
					return 1;
				}

				case DB_NULL:
				{
					return pg_affected_rows($this->link_id);
				}

				default:
				{
					$this->handle_error("Invalid query type; type=$type");
				}
			}

			return;
		}

		function last_insert_id()
		{
			$id = @pg_last_oid($this->link_id);

			if (!$id)
				$this->handle_error("Could not fetch last insert id");

			return $id;
		}


		function num_rows()
		{
			if ($this->result_id)
				return @pg_num_rows($this->result_id);

			return 0;
		}

		function fetch_row()
		{
			if ($this->result_id)
			{
				if (@pg_num_rows($this->result_id))
				{
					$data = @pg_fetch_array($this->result_id);

					if ($data)
					{
						return $data;
					} else {
						pg_free_result($this->result_id);
					}
				} else {
					@pg_free_result($this->result_id);
					unset($this->result_id);
				}
			}

			return 0;
		}

		function disconnect()
		{
			if ($this->link_id)
			{
				@pg_close($this->link_id) || $this->handle_error("Cannot disconnect from database");
			} else {
				@pg_close();
			}

			$this->link_id = 0;

			return;
		}

		function handle_error($msg)
		{
			$msg .= "; PostgreSQL error=" . ($this->link_id ? pg_error($this->link_id) : pg_error());

# sometimes creates infiniute loops
#			$this->disconnect();

			CPL::handle_error($msg);

			exit();
		}

		# Make a string safe to place in an SQL query
		function prepare_str($str,$type)
		{
			switch ($type)
			{
				/*
				 * PostgreSQL wildcard characters include
				 * the percent '%' and underscore '_'
				 * in addition that of regular
				 * string escaping
				 */
				case SQL_WILD:
					$str = preg_replace("/[\\\"'_%]/","\\\\1",$str);
					break;

				/*
				 * Regular strings must be escaped of
				 * characters such as quotes and
				 * slashes (same as in PHP)
				 */
				case SQL_REG:
					$str = addSlashes($str);
					break;

				/*
				 * All common regular expression meta-
				 * characters will need to be escaped
				 * be PostgreSQL's `/' character
				 */
				case SQL_REGEX:
					$str = preg_replace("/[\\\"'\$^()\[\]{}+*?.]/","\\\\1",$str);
					break;

				default:
					CPL::handle_error("Unknown sql_safe type; type: $type");
			}

			return $str;
		}
	}
?>
