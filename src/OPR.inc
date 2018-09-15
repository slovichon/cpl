<?php
	/* $Id$ */
	/*
	 * OPR - Preference repository for OOF
	 *
	 * This class defines the routines which OF-specific
	 * classes will use to specify their own preferences.
	 */

	require_once 'CPL.inc';

	class OFPR {
		var $dec; # abstract
		var $prefs;

		function OFPR($prefs) {
			$this->dec = array();
			$this->prefs = array();

			# Declare available preferences
			$this->dec = array();

			# Initialize argued preferences
			$this->set($prefs);
		}

		function set($prefs) {
			foreach ($prefs as $group => $group_prefs)
				foreach ($group_prefs as $name => $value)
					if (array_key_exists($group,$this->dec) &&
					    array_key_exists($name,$this->dec[$group])) {
						if (!array_key_exists($group, $this->prefs))
							$this->prefs[$group] = array();
						$this->prefs[$group][$name] = $value;
					} else
						CPL::handle_error("");
		}

		function get($group) {
			if (array_key_exists($group, $this->dec)) {
				if (array_key_exists($group, $this->prefs))
					return $this->prefs[$group];
				else
					return array();
			} else
				CPL::handle_error("Undefined group in preference lookup; group: $group");
		}
	}
?>
