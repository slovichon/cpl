<?php
	/* $Id$ */
	require_once 'CPL.inc';

	/* Returns the next line from a file descriptor */
	function fgetln($fp) {
		$line = NULL;
		while ($ch = @fgetc($fp)) {
			$line .= $ch;

			if ($ch == "\n") {
				return $line;
			} elseif ($ch == "\r") {
				$next_ch = fgetc($fp);
				if ($next_ch == "\n")
					$line .= $next_ch;
				else
					fseek($fp,-1,SEEK_CUR);
				return $line;
			}
		}

		/* We hit EOF */
		return $line;
	}

	/* Returns an array of filenames in a directory */
	function readdira($dp) {
		$files = array();

		if (!@rewinddir($dp))
			CPL::handle_error("Cannot rewind directory pointer");
		while ($file = readdir($dp))
			$files[] = $file;
		return $files;
	}

	/* Calculates the size of a directory */
	function dirsize($dir_path) {
		global $php_errormsg;

		$dirsize	= 0;
		$dir		= @opendir($dir_path);

		if (!$dir)
			CPL::handle_error("Cannot open directory; directory: $dir_path");

		while ($file = readdir($dir))
		{
			if ($file == "." || $file == "..")
				continue;

			$file = $dir_path . "/" . $file;

			if (is_dir($file))
			{
				$dirsize += dirsize($file);

			} elseif (is_file($file)) {

				$dirsize += filesize($file);
			}
		}

		closedir($dir);

		return $dirsize;
	}
?>
