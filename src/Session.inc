<?php
	/* $Id$ */
	require_once "Util/fs.inc";

	class Session {
		var $id;
		var $data = array();
		var $file = "/tmp/php.Session.data";
		var $timeout = 1200; # 60 * 20 = 20 minutes.
		var $timestamp;
		var $cookie_name = "PHPSESSID";

		function Session() {
			global $HTTP_COOKIE_VARS;

			$id = $HTTP_COOKIE_VARS[$this->cookie_name];

			# Check whether a new session is being create or an old one is being referred.
			$fp = fopen($this->file, "r");
			while ($session = unserialize(chop(fgetln($fp)))) {
				if ($session->id == $id &&
				    $session->timestamp + $session->timeout > time()) {
					$this->id = $session->id;
					$this->data = $session->data;
					fclose($fp);
					return ($this);
				}
			}
			fclose($fp);

			$this->id = generate_session_id($this->file);
			setCookie($this->cookie_name,$this->id);
			return ($this);
		}

		function save($name) {
			global $$name;

			$this->data[$name] = $$name;
		}

		function load($name) {
			return $this->data[$name];
		}

		function store() {
			$key = "";
			$is_new = TRUE;
			$session = array();
			$sess = array();
			$sessions = array();

			# If in the file, replace old one; if not, add it.
			$sessions = file($this->file);

			# Change the timestamp to now.
			$this->timestamp = time();

			foreach ($sessions as $key => $sess) {
				$session = unserialize($sess);
				if ($session->id == $this->id) {
					$sessions[$key] = serialize($this);
					$is_new = FALSE;
				}
			}

			if ($is_new)
				array_push($sessions,serialize($this) . "\n");

			$fp = @fopen($this->file, "w");
			/* XXX: handle errors. */
			if ($fp) {
				fputs($fp, join("", $sessions));
				fclose($fp);
			}
		}
	}

	function generate_session_id($filename) {
		$time = time();
		$id = uniqid($time, crypt($time,$time));
		$fp = @fopen($filename, "r");
		if ($fp) {
			while ($line = fgetln($fp)) {
				$session = @unserialize(chop($line));
				if (!$session)
					continue;
				if ($session->id == $id) {
					fclose($fp);
					return (generate_session_id($filename));
				}
			}
			fclose($fp);
		}
		return ($id);
	}
?>
