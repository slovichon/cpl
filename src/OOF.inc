<?php
	/* $Id$ */
	require_once 'CPL.inc';

	CPL::define("OOF_LIST_UN", 1);
	CPL::define("OOF_LIST_OD", 2);

	# Default values for required attributes.
	CPL::nice_define("OOF_DEF_TEXTAREA_WIDTH", 4);
	CPL::nice_define("OOF_DEF_TEXTAREA_HEIGHT", 20);
	CPL::nice_define("OOF_DEF_FORM_METHOD", "post");
	CPL::nice_define("OOF_DEF_HEADER_SIZE", 3);

	class OOF {
		var $prefs = array();
		var $obj;

		function OOF(&$cpl, $type, $prefs = array()) {
			if (!preg_match("/^[a-z]+$/i", $type) ||
			    !@include_once("OOF/$type.inc"))
				$cpl->handle_error("Invalid type");
			$class = "OOF_$type";
			$this->obj = new $class($this, &$cpl);
			if (is_array($prefs))
				$this->_loadprefs($prefs);
		}

		function _loadprefs($prefs) {
			foreach ($prefs as $elem => $elem_prefs)
				foreach ($elem_prefs as $name => $value)
					$this->_loadpref($elem, $name, $value);
		}

		function _loadpref($elem, $name, $value) {
			$this->prefs[$elem][$name] = $value;
		}

		function _getprefs($elem, $prefs) {
			if (!is_array($prefs))
				$prefs = array();
			if (array_key_exists($elem, $this->prefs))
				return (array_merge($this->prefs[$elem], $prefs));
			else
				return ($prefs);
		}

		function form() {
			$args = func_get_args();
			$prefs = array();

			if (is_array($args[0]))
				$prefs = array_shift($args);
			return ($this->obj->form_start($prefs) .
				join('', $args) .
				$this->obj->form_end());
		}

		function form_start($prefs = NULL) {
			return ($this->obj->form_start($prefs));
		}

		function form_end() {
			return ($this->obj->form_end());
		}

		function fieldset() {
			$args = func_get_args();
			return (call_user_func_array(array(&$this->obj,
			    'fieldset'), $args));
		}

		function table() {
			$args = func_get_args();
			$prefs = array();

			if (is_array($args[0]))
				$prefs = array_shift($args);
			$html = $this->obj->table_start($prefs);
			foreach ($args as $row) {
				if (is_array($row))
					$html .= call_user_func_array(array(&$this->obj,
					    'table_row'), $row);
				else
					$html .= $this->obj->table_row($row);
			}
			$html .= $this->table_end();
			return ($html);
		}

		function table_end() {
			return ($this->obj->table_end());
		}

		function table_start($prefs = NULL) {
			return ($this->obj->table_start($prefs));
		}

		function table_row() {
			$args = func_get_args();
			return (call_user_func_array(array(&$this->obj,
			    'table_row'), $args));
		}

		function table_head() {
			$args = func_get_args();
			return (call_user_func_array(array(&$this->obj,
			    'table_head'), $args));
		}

		function p() {
			$args = func_get_args();
			return (call_user_func_array(array(&$this->obj,
			    'p'), $args));
		}

		function link() {
			$args = func_get_args();
			return (call_user_func_array(array(&$this->obj,
			    'link'), $args));
		}

		function hr($prefs = NULL) {
			return ($this->obj->hr($prefs));
		}

		function input($prefs) {
			return ($this->obj->input($prefs));
		}

		function br($prefs = NULL) {
			return ($this->obj->br($prefs));
		}

		function list_start($type) {
			return ($this->obj->list_start($type));
		}

		function list_end($type) {
			return ($this->obj->list_end($type));
		}

		function list_item($val) {
			return ($this->obj->list_end($type));
		}

		function oof_list() {
			$args = func_get_args();
			$type = array_shift($args);

			$html = $this->list_start($type);
			foreach ($args as $item)
				$html .= $this->list_item($item);
			$html .= $this->list_end($type);
			return ($html);
		}

		function header() {
			$args = func_get_args();
			return (call_user_func_array(array(&$this->obj,
			    'header'), $args));
		}

		function emph() {
			$args = func_get_args();
			return (call_user_func_array(array(&$this->obj,
			    'emph'), $args));
		}

		function pre() {
			$args = func_get_args();
			return (call_user_func_array(array(&$this->obj,
			    'pre'), $args));
		}

		function code() {
			$args = func_get_args();
			return (call_user_func_array(array(&$this->obj,
			    'code'), $args));
		}

		function strong() {
			$args = func_get_args();
			return (call_user_func_array(array(&$this->obj,
			    'strong'), $args));
		}

		function span() {
			$args = func_get_args();
			return (call_user_func_array(array(&$this->obj,
			    'span'), $args));
		}

		function div() {
			$args = func_get_args();
			return (call_user_func_array(array(&$this->obj,
			    'div'), $args));
		}

		function img($prefs) {
			return ($this->obj->img($prefs));
		}

		function email() {
			$args = func_get_args();
			return (call_user_func_array(array(&$this->obj,
			    'email'), $args));
		}
	}
?>
