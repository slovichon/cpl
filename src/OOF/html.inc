<?php
	/* $Id$ */
	class OOF_html {
		var $cpl;
		var $oof;

		function OOF_html($oof, $cpl) {
			$this->oof = $oof;
			$this->cpl = $cpl;
		}

		function _getprefs($elem, $prefs) {
			return ($this->oof->_getprefs($elem, $prefs));
		}

		function _start($name, $dprefs) {
			$prefs = $this->_getprefs($name, $dprefs);
			$html = "<" . $name;
			foreach ($prefs as $name => $value)
				$html .= " $name=\"$value\"";
			$html .= ">";
			return ($html);
		}

		function _end($name) {
			return ("</$name>");
		}

		function _gen($name, $prefs, $data) {
			if (!empty($data) || $name == "div" || $name == "a")
				return ($this->_start($name, $prefs) .
					$data .
					$this->_end($name));
			else
				return (preg_replace("/>$/",
				    $this->_start($name, $prefs)) . " />");
		}

		function form_start($prefs) {
			/* Initiate default values */
/*
			if (!array_key_exists("action", $prefs))
				$prefs["action"] = $_SERVER["PHP_SELF"];

			if (!array_key_exists("method", $prefs))
				$prefs["method"] = OOF_DEF_FORM_METHOD;

			if (!array_key_exists("enctype", $prefs))
				$prefs["enctype"] = "application/x-www-form-urlencoded";
*/
			return ($this->_start('form', $prefs));
		}

		function form_end() {
			return ($this->_end('form'));
		}

		function fieldset() {
			return ($this->_gen('fieldset', array(),
			    join('', func_get_args())));
		}

		function table_end() {
			return ($this->_end('table'));
		}

		function table_start() {
			$args = func_get_args();
			$prefs = array();

			if (is_array($args[0]))
				$prefs = array_shift($args);

/*
			if (!array_key_exists("cellspacing", $prefs))
				$prefs["cellspacing"] = 0;
			if (!array_key_exists("cellpadding", $prefs))
				$prefs["cellpadding"] = 0;
			if (!array_key_exists("border", $prefs))
				$prefs["border"] = 0;
*/

			$cols = FALSE;
			if (array_key_exists("cols", $prefs) &&
			    is_array($prefs["cols"])) {
				$cols = $prefs["cols"];
				unset($prefs["cols"]);
			}

			$html = $this->_start('table', $prefs);
			if ($cols) {
				$cg = "";
				foreach ($cols as $i_prefs)
					$cg .= $this->_gen('col', $i_prefs);
				$html .= $this->_gen('colgroup', array(), $cg);
			}
			return ($html);
		}

		function table_row() {
			$cols = func_get_args();
			$html = "";

			foreach ($cols as $col) {
				if (!is_array($col))
					$col = array("value" => $col);
				$value = "";
				if (array_key_exists("value", $col)) {
					$value = $col["value"];
					unset($col["value"]);
				}
				$html .= $this->_gen('td', $col, $value);
			}
			return ($this->_gen('tr', array(), $html));
		}

		function table_head() {
			$headers = func_get_args();
			$html = "";

			foreach ($headers as $header) {
				if (!is_array($header))
					$header = array('value' => $header);
				$value = "";
				if (array_key_exists("value", $header)) {
					$value = $header["value"];
					unset($header["value"]);
				}
				$html .= $this->_gen('th', $header, $value);
			}
			return ($this->_gen('tr', array(), $html));
		}

		function p() {
			$args = func_get_args();
			$prefs = array();

			if (is_array($args[0]))
				$prefs = array_shift($args);
			return ($this->_gen('p', $prefs, join('', $args)));
		}

		function link() {
			$args = func_get_args();
			$prefs = array();

			if (is_array($args[0]))
				$prefs = array_shift($args);
			else
				list($prefs["value"], $prefs["href"]) = $args;

			if (!array_key_exists("value", $prefs))
				$this->cpl->handle_error("No value specified " .
				    "in OOF::" . __FUNCTION__ . "()");
			$value = $prefs["value"];
			unset($prefs["value"]);

			return ($this->_gen('a', $prefs, $value));
		}

		function hr() {
			return ($this->_gen('hr', array(), ''));
		}

		function input($prefs) {
			$html = "";

			if ($prefs["type"] == "select") {
				unset($prefs["type"]);

				$value = "";
				if (array_key_exists("value", $prefs)) {
					$value = $prefs["value"];
					unset($prefs["value"]);
				}

				$options = $prefs["options"];
				unset($prefs["options"]);

				$t_html = "";
				foreach ($options as $opt_name => $opt_val) {
					$opt_prefs = array('value' => $opt_name);
					if ($opt_name == $value)
						$opt_prefs['selected'] = 'selected';
					$t_html .= $this->_gen('option',
					    $opt_prefs, $opt_val);
				}

				$html = $this->_gen('select', $prefs, $t_html);
			} elseif ($prefs["type"] == "textarea") {
				unset($prefs["type"]);

				$value = "";
				if (array_key_exists("value", $prefs)) {
					$value = htmlEntities($prefs["value"]);
					unset($prefs["value"]);
				}

/*
				if (!array_key_exists('rows', $prefs))
					$prefs['rows'] = OOF_DEF_TEXTAREA_WIDTH;
				if (!array_key_exists('cols', $prefs))
					$prefs['cols'] = OOF_DEF_TEXTAREA_HEIGHT;
*/

				$html = $this->_gen('textarea', $prefs, $value);
			} else {
				$label = "";
				if (array_key_exists("label", $prefs)) {
					$label = $prefs["label"];
					unset($prefs["label"]);
				}

				/* Generate a random ID. */
				if ($label && !array_key_exists('id', $prefs))
					$prefs['id'] = $this->_gen_rand_id();

				$html = $this->_gen('input', $prefs, '');
				if ($label)
					$html = $this->_gen('label',
					    array('for' => $prefs['id']),
					    "$html $label");
			}
			return ($html);
		}

		function _gen_rand_id() {
			static $used = array();

			$id = "";
			do {
				$id = "OOFInput" . md5(uniqid("OOFInput", TRUE));
			} while (in_array($id, $used));
			array_push($used, $id);
			return ($id);
		}

		function br() {
			return ($this->_gen('br', array(), ''));
		}

		function list_start($type) {
			$types = array(
				OOF_LIST_UN => "ul",
				OOF_LIST_OD => "od"
			);
			if (!array_key_exists($type, $types))
				CPL::handle_error("Unknown OOF::" . __FUNCTION__ .
				    "() type; type: $type");
			return ($this->_start($types[$type], array()));
		}

		function list_end($type) {
			$types = array(
				OOF_LIST_UN => "ul",
				OOF_LIST_OD => "od"
			);
			if (!array_key_exists($type, $types))
				CPL::handle_error("Unknown OOF::" . __FUNCTION__ .
				    "() type; type: $type");
			return ($this->_end($types[$type], array()));
		}

		function list_item($val) {
			return ($this->_gen('li', array(), $val));
		}

		function header() {
			$args = func_get_args();
			$prefs = array();

			if (is_array($args[0])) {
				$prefs = $args[0];
			} else {
				$prefs = array(
					'value'	=> @$args[0],
					'size'	=> @$args[1]
				);
			}

			if (!array_key_exists("value", $prefs))
				CPL::handle_error("No value specified in OOF::" .
				    __FUNCTION__ . "()");
			$value = $prefs['value'];
			unset($prefs['value']);

			if (!array_key_exists("size", $prefs) || !$prefs['size'])
				$prefs['size'] = OOF_DEF_HEADER_SIZE;
			$tag = "h" . $prefs['size'];
			unset($prefs['size']);

			return ($this->_gen($tag, $prefs, $value));
		}

		function emph() {
			$args = func_get_args();
			$prefs = array();

			if (is_array($args[0]))
				$prefs = array_shift($args);
			return ($this->_gen('em', $prefs, join('', $args)));
		}

		function pre() {
			$args = func_get_args();
			$prefs = array();

			if (is_array($args[0]))
				$prefs = array_shift($args);
			return ($this->_gen('pre', $prefs,
			    htmlEntities(join('', $args))));
		}

		function code() {
			$args = func_get_args();
			$prefs = array();

			if (is_array($args[0]))
				$prefs = array_shift($args);
			return ($this->_gen('code', $prefs, join('', $args)));
		}

		function strong() {
			$args = func_get_args();
			$prefs = array();

			if (is_array($args[0]))
				$prefs = array_shift($args);
			return ($this->_gen('strong', $prefs, join('', $args)));
		}

		function span() {
			$args = func_get_args();
			$prefs = array();

			if (is_array($args[0]))
				$prefs = array_shift($args);
			return ($this->_gen('span', $prefs, join('', $args)));
		}

		function div() {
			$args = func_get_args();
			$prefs = array();

			if (is_array($args[0]))
				$prefs = array_shift($args);
			return ($this->_gen('span', $prefs, join('', $args)));
		}

		function img($prefs) {
			if (!array_key_exists('src', $prefs))
				CPL::handle_error("No `src' defined for image in OOF::img()");
			if (!array_key_exists('alt', $prefs))
				$prefs['alt'] = '';
			return ($this->_gen('img', $prefs, ''));
		}

		function email() {
			$args = func_get_args();
			$count = func_num_args();
			$prefs = array();

			if (is_array($args[0]))
				$prefs = $args[0];
			else
				$prefs = array(
					'value' => $args[0],
					'display' => TRUE
				);
				switch ($count) {
				case 3:
					$prefs['display'] = $args[2];
					/* FALLTHROUGH */
				case 2:
					$prefs['addr'] = $args[1];
					break;
				case 1:
					$prefs['addr'] = $args[0];
					break;
				default:
					CPL::handle_error("Invalid OOF::email() call. Check arguments");
				}

			preg_match("/^(.+)@(.+)$/",$prefs['addr'],$matches);

			# Display link
			if ($args['display']) {
				return 	  "<script type='text/javascript'>"
					.	"<!--"
					.		"document.write('<a href=\"mailto:'+'$matches[0]'+'@'+'$matches[1]'\">{$prefs['value']}</a>')"
					.	"//-->"
					. "</script>"
					. "<noscript>"
					.	$prefs['value']
					#. 	" - "
					.	"&lt;"
					.	preg_replace("/@/",":<!--\n-->:AT:<!--\n-->:",$prefs['addr'])
					.	"&gt;"
					. "</noscript>";
			} else {
				return	  "<script type='text/javascript'>"
					. 	"<!--"
					.		"document.write('$matches[1]'+'@'+'$matches[1]')"
					.	"//-->"
					. "</script>"
					. "<noscript>"
					.	preg_replace("/@/",":<!--\n-->:AT:<!--\n-->:",$prefs['addr'])
					. "</noscript>";
			}
		}
	}
?>
