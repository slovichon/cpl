<?php
	/* $Id$ */
	require_once 'CPL.inc';

	CPL::define("OF_LIST_UN", 1);
	CPL::define("OF_LIST_OD", 2);

	# People may want to override these
	CPL::nice_define("OF_DEF_TEXTAREA_WIDTH",4);
	CPL::nice_define("OF_DEF_TEXTAREA_HEIGHT",20);
	CPL::nice_define("OF_DEF_FORM_METHOD","post");
	CPL::nice_define("OF_DEF_HEADER_SIZE",3);

	class OF_HTML {
		var $prefs;

		function OF() {
			$args = func_get_args();
			$this->prefs = array();

			if (is_array($args[0]))
				$this->of_loadprefs($args[0]);
		}

		function of_loadprefs($prefs) {
			foreach ($prefs as $group => $group_prefs)
				foreach ($group_prefs as $name => $value)
					$this->of_loadpref($group, $name, $value);
		}

		function of_loadpref($group, $name, $value) {
			$this->prefs[$group][$name] = $value;
		}

		function form() {
			$args = func_get_args();
			$prefs = array();

			/* The first argument may be prefs */
			if (is_array($args[0]))
				$prefs = array_shift($args);
			$content = join('',$args);
			return	$this->form_start($prefs) .
				$content .
				$this->form_end();
		}

		function form_start($prefs = NULL) {
			if (!is_array($prefs))
				$prefs = array();

			/* Initiate default values */
/*			if (!array_key_exists("action",$prefs))
				$prefs["action"] = $_SERVER["PHP_SELF"];

			if (!array_key_exists("method",$prefs))
				$prefs["method"] = OF_DEF_FORM_METHOD;

			if (!array_key_exists("enctype",$prefs))
				$prefs["enctype"] = "application/x-www-form-urlencoded";
*/
			/* Build HTML */
			$html = "<form";
			foreach ($prefs as $name => $value)
				$html .= " $name=\"$value\"";
			$html .= ">";
			return ($html);
		}

		function form_end() {
			return ("</form>");
		}

		function fieldset() {
			$args = func_get_args();
			$data = join('',$args);

			return ("<fieldset>$data</fieldset>");
		}

		function table() {
			$args = func_get_args();
			$prefs = array();

			/* The first argument may be prefs */
			if (is_array($args[0]))
				$prefs = array_shift($args);

			/* This is just a wrapper for table_start() and table_end() */
			$content = join('', $args);
			$html = $this->table_start($prefs) .
			    $content .
			    $this->table_end();
			return ($html);
		}

		function table_end() {
			return ("</table>");
		}

		function table_start() {
			$args = func_get_args();
			$prefs = array();

			/* The first argument can be preferences */
			if (is_array($args[0]))
				$prefs = array_shift($args);

			/* Initiate default values */
			if (!array_key_exists("cellspacing", $prefs))
				$prefs["cellspacing"] = 0;

			if (!array_key_exists("cellpadding", $prefs))
				$prefs["cellpadding"] = 0;

			if (!array_key_exists("border", $prefs))
				$prefs["border"] = 0;

			/* Build HTML */
			$html = "<table";
			$cols = FALSE;

			if (array_key_exists("cols", $prefs) &&
			    is_array($prefs["cols"])) {
				$cols = $prefs["cols"];
				unset($prefs["cols"]);
			}

			foreach ($prefs as $pref_name => $pref_val)
				$html .= " $pref_name=\"$pref_val\"";

			$html .= ">";

			if ($cols) {
				$html .= "<colgroup>";
				foreach ($cols as $i_prefs) {
					$html .= "<col";
					foreach ($i_prefs as $pref_name => $pref_val)
						$html .= " $pref_name=\"$pref_val\"";
					$html .= " />";
				}
				$html .= "</colgroup>";
			}
			return ($html);
		}

		function table_row() {
			$cols = func_get_args();
			$html = "<tr>";

			foreach ($cols as $col) {
				if (!is_array($col))
					$col = array("value" => $col);

				$html .= "<td";
				$value = "";

				if (array_key_exists("value", $col)) {
					$value = $col["value"];
					unset($col["value"]);
				} else {
					$value = "&nbsp;";
				}

				foreach ($col as $pref_name => $pref_val)
					$html .= " $pref_name=\"$pref_val\"";
				$html .= ">$value</td>";
			}
			$html .= "</tr>";
			return ($html);
		}

		function table_head() {
			$headers = func_get_args();
			$html = "<tr>";

			foreach ($headers as $header) {
				if (!is_array($header))
					$header = array('value' => $header);

				$html .= "<th";
				$value = "";

				if (array_key_exists("value", $header)) {
					$value = $header["value"];
					unset($header["value"]);
				} else {
					$value = "";
				}

				foreach ($header as $pref_name => $pref_val)
					$html .= " $pref_name=\"$pref_val\"";
				$html .= ">$value</th>";
			}
			$html .= "</tr>";
			return ($html);
		}

		function p() {
			$args = func_get_args();
			$prefs = array();

			/* Check if the first argument contains paragraph preferences */
			if (is_array($args[0]))
				$prefs = array_shift($args);

			$content = join('',$args);
			$html = "<p";

			foreach ($prefs as $pref_name => $pref_value)
				$html .= " $pref_name=\"$pref_value\"";
			$html .= ">$content</p>";
			return ($html);
		}

		function link() {
			$args = func_get_args();
			$prefs = array();

			if (is_array($args[0])) {
				$prefs = array_shift($args);
			} else {
				list($prefs["value"],
				    $prefs["href"]) = $args;
			}

			if (!array_key_exists("value",$prefs))
				CPL::handle_error("No value specified in OF::link()");

			$value = $prefs["value"];
			unset($prefs["value"]);
			$html = "<a";

			foreach ($prefs as $pref_name => $pref_value)
				$html .= " $pref_name=\"$pref_value\"";
			$html .= ">$value</a>";
			return ($html);
		}

		function hr() {
			return "<hr />";
		}

		function input($prefs) {
			$html = "";

			if ($prefs["type"] == "select") {
				$html = "<select";
				$options = $prefs["options"];
				unset($prefs["options"]);
				unset($prefs["type"]);

				$value = "";

				if (array_key_exists("value", $prefs)) {
					$value = $prefs["value"];
					unset($prefs["value"]);
				}

				foreach ($prefs as $pref_name => $pref_value)
					$html .= " $pref_name=\"$pref_value\"";

				$html .= ">";

				foreach ($options as $opt_name => $opt_val)
					$html .= "<option value=\"$opt_name\"" . ($opt_name == $value ? " selected=\"selected\"" : "") . ">$opt_val</option>";
				$html .= "</select>";
			} elseif ($prefs["type"] == "textarea") {
				$html = "<textarea";
				$value = "";

				if (array_key_exists("value", $prefs)) {
					$value = htmlEntities($prefs["value"]);
					unset($prefs["value"]);
				}

/*
				if (!array_key_exists('rows', $prefs))
					$prefs['rows'] = OF_DEF_TEXTAREA_WIDTH;

				if (!array_key_exists('cols', $prefs))
					$prefs['cols'] = OF_DEF_TEXTAREA_HEIGHT;
*/

				unset($prefs["type"]);

				foreach ($prefs as $pref_name => $pref_value)
					$html .= " $pref_name=\"$pref_value\"";
				$html .= ">$value</textarea>";
			} else {
				$html = "<input";
				$label = "";

				if (array_key_exists("label", $prefs)) {
					$label = $prefs["label"];
					unset($prefs["label"]);
				}

				if (array_key_exists("checked", $prefs)) {
					$html .= " checked=\"checked\"";
					unset($prefs["checked"]);
				}

				/* Generate a random ID */
				if ($label && !array_key_exists('id',$prefs))
					$prefs['id'] = $this->_gen_rand_id();

				foreach ($prefs as $pref_name => $pref_value)
					$html .= " $pref_name=\"$pref_value\"";
				$html .= " />";
				if ($label)
					$html = "<label for=\"{$prefs["id"]}\">$html $label</label>";
			}
			return ($html);
		}

		function _gen_rand_id() {
			static $used = array();

			$id = "";
			do {
				$id = "OFInput" . md5(uniqid("OFInput", TRUE));
			} while (in_array($id, $used));
			array_push($used, $id);
			return ($id);
		}

		function br() {
			return "<br />";
		}

		function list_start($type) {
			$tag = "";

			switch ($type) {
			case OF_LIST_UN:
				$tag = "ul";
				break;
			case OF_LIST_OD:
				$tag = "ol";
				break;
			default:
				CPL::handle_error("Unknown OF::list_start() type; type: $type");
			}
			return "<$tag>";
		}

		function list_end($type) {
			$tag = "";

			switch ($type) {
			case OF_LIST_UN:
				$tag = "ul";
				break;
			case OF_LIST_OD:
				$tag = "ol";
				break;
			default:
				CPL::handle_error("Unknown OF::list_start() type; type: $type");
			}
			return "</$tag>";
		}

		function list_item($val) {
			return "<li>$val</li>";
		}

		function of_list() {
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
			$prefs = array();

			if (is_array($args[0])) {
				$prefs = $args[0];
			} else {
				$prefs = array(
					'value'	=> @$args[0],
					'size'	=> @$args[1]
				);
			}

			if (!array_key_exists("value",$prefs))
				CPL::handle_error("No value specified in OF::header()");
			$value = $prefs['value'];
			unset($prefs['value']);
			if (!array_key_exists("size",$prefs) || !$prefs['size'])
				$prefs['size'] = OF_DEF_HEADER_SIZE;
			$tag = "h" . $prefs['size'];
			unset($prefs['size']);
			$html = "<$tag";
			foreach ($prefs as $pref_name => $pref_value)
				$html .= " $pref_name=\"$pref_value\"";
			$html .= ">$value</$tag>";
			return $html;
		}

		function emph() {
			$args = func_get_args();
			$data = join('',$args);

			return "<em>$data</em>";
		}

		function pre($str) {
			return "<pre>" . htmlEntities($str) . "</pre>";
		}

		function code($str) {
			return "<code>" . htmlEntities($str) . "</code>";
		}

		function strong() {
			$args = func_get_args();
			$data = join('', $args);

			return "<strong>$data</strong>";
		}

		function div() {
			$args = func_get_args();
			$prefs = array();

			if (is_array($args[0]))
				$prefs = array_shift($args);
			$attr = "";
			foreach ($prefs as $name => $value)
				$attr .= " $pref=\"$value\"";
			$data = join('',$args);
			return "<div$attr>$data</div>";
		}

		function img() {
			$args = func_get_args();
			$prefs = array();

			if (is_array($prefs[0]))
				$prefs = array_shift($args);
			if (!array_key_exists('src',$prefs))
				CPL::handle_error("No `src' defined for image in OF::img()");
			if (!array_key_exists('alt',$prefs))
				$prefs['alt'] = '';
			if (!array_key_exists('border',$prefs))
				$prefs['border'] = 0;

			$data = "<img";
			foreach ($prefs as $name => $value)
				$data .= " $name=\"$value\"";
			$data .= " />";
		}

		# email() - Tries to reduce spam
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
					CPL::handle_error("Invalid OF::email() call. Check arguments");
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
