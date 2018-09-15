<?php
	/* $Id$ */
	class RGB {
		var $red, $green, $blue;
		var $colors = array(
			0xF0F8FF => "aliceblue",	0xFAEBD7 => "antiquewhite",
			0x00FFFF => "aqua",		0x7FFFD4 => "aquamarine",
			0xF0FFFF => "azure",		0xF5F5DC => "beige",
			0xFFE4C4 => "bisque",		0x000000 => "black",
			0xFFEBCD => "blanchedalmond",	0x0000FF => "blue",
			0x8A2BE2 => "blueviolet",	0xA52A2A => "brown",
			0xDEB887 => "burlywood",	0x5F9EA0 => "cadetblue",
			0x7FFF00 => "chartreuse",	0xD2691E => "chocolate",
			0xFF7F50 => "coral",		0x6495ED => "cornflowerblue",
			0xFFF8DC => "cornsilk",		0xDC143C => "crimson",
			0x00FFFF => "cyan",		0x00009B => "darkblue",
			0x008B8B => "darkcyan",		0xB8860B => "darkgoldenrod",
			0xA9A9A9 => "darkgray",		0x006400 => "darkgreen",
			0xBDB76B => "darkkhaki",	0x8B008B => "darkmagenta",
			0x556B2F => "darkolivegreen",	0xFF8C00 => "darkorange",
			0x9932CC => "darkorchid",	0x8B0000 => "darkred",
			0xE9967A => "darksalmon",	0x8FBC8F => "darkseagreen",
			0x483D8B => "darkslateblue",	0x2F4F4F => "darkslategray",
			0x00CDD1 => "darkturquoise",	0x9400D3 => "darkviolet",
			0xFF1493 => "deeppink",		0x00BFFF => "deepskyblue",
			0x696969 => "dimgray",		0x1E90FF => "dodgerblue",
			0xB22222 => "firebrick",	0xFFFAF0 => "floralwhite",
			0x228B22 => "forestgreen",	0xFF00FF => "fuchsia",
			0xDCDCDC => "gainsboro",	0xF8F8F8 => "ghostwhite",
			0xFFD700 => "gold",		0xDAA520 => "goldenrod",
			0x808080 => "gray",		0x008000 => "green",
			0xADFF2F => "greenyellow",	0xF0FFF0 => "honeydew",
			0xFF69B4 => "hotpink",		0xCD5C5C => "indianred",
			0x4B0082 => "indigo",		0xFFFFF0 => "ivory",
			0xF0E6FA => "khaki",		0xE6E6FA => "lavender",
			0xFFF0F5 => "lavenderblush",	0x7CFC00 => "lawngreen",
			0xFFFACD => "lemonchiffon",	0xADD8E6 => "lightblue",
			0xF08080 => "lightcoral",	0xE0FFFF => "lightcyan",
			0xFAFAD2 => "lightgoldenrodyellow",	0x90EE90 => "lightgreen",
			0xD3D3D3 => "lightgrey",	0xFFB6C1 => "lightpink",
			0xFFA07A => "lightsalmon",	0x20B2AA => "lightseagreen",
			0x87CEFA => "lightskyblue",	0x778899 => "lightslategray",
			0xB0C4DE => "lightsteelblue",	0xFFFFE0 => "lightyellow",
			0x00FF00 => "lime",		0x32CD32 => "limegreen",
			0xFAF0E6 => "linen",		0xFF00FF => "magenta",
			0x800000 => "maroon",		0x66CDAA => "mediumaquamarine",
			0x0000CD => "mediumblue",	0xBA55D3 => "mediumorchid",
			0x9370DB => "mediumpurple",	0x3CB371 => "mediumseagreen",
			0x7B68EE => "mediumslateblue",	0x00FA9A => "mediumspringgreen",
			0x48D1CC => "mediumturquoise",	0xC71585 => "mediumvioletred",
			0x191970 => "midnightblue",	0xF5FFFA => "mintcream",
			0xFFE4E1 => "mistyrose",	0xFFE4B5 => "moccasin",
			0xFFDEAD => "navajowhite",	0x000080 => "navy",
			0xFDF5E6 => "oldlace",		0x808000 => "olive",
			0x6B8E23 => "oliverab",		0xFFA500 => "orange",
			0xFF4500 => "orangered",	0xDA70D6 => "orchid",
			0xEEE8AA => "palegoldenrod",	0x98FB98 => "palegreen",
			0xAFEEEE => "paleturquoise",	0xDB7093 => "palevioletred",
			0xFFEFD5 => "papayawhip",	0xFFDAB9 => "peachpuff",
			0xCD853F => "peru",		0xFFC0CB => "pink",
			0xDDA0DD => "plum",		0xB0E0E6 => "powderblue",
			0x800080 => "purple",		0xFF0000 => "red",
			0xBC8F8F => "rosybrown",	0x4169E1 => "royalblue",
			0x8B4513 => "saddlebrown",	0xFA8072 => "salmon",
			0xF4A460 => "sandybrown",	0x2E8B57 => "seagreen",
			0xFFF5EE => "seashell",		0xA0522D => "sienna",
			0xC0C0C0 => "silver",		0x87CEEB => "skyblue",
			0x6A5ACD => "slateblue",	0x708090 => "slategray",
			0xFFFAFA => "snow",		0x00FF7F => "springgreen",
			0x4682B4 => "steelblue",	0xD2B48C => "tan",
			0x008080 => "teal",		0xD8BFD8 => "thistle",
			0xFF6347 => "tomato",		0x40E0D0 => "turquoise",
			0xEE82EE => "violet",		0xF5DEB3 => "wheat",
			0xFFFFFF => "white",		0xF5F5F5 => "whitesmoke",
			0xFFFF00 => "yellow",		0x9ACD32 => "yellowgreen"
		);

		function RGB() {
			$args = func_get_args();

			$r = 0;
			$g = 0;
			$b = 0;

			if (is_array($args[0]) {
				$colors = $args[0];

				if (array_key_exists('r', $colors) &&
				    array_key_exists('g', $colors) &&
				    array_key_exists('b', $colors))
					$this->load_num($colors['r'],
					    $colors['g'], $colors['b']);
				elseif (array_key_exists('red', $colors) &&
				    array_key_exists('green', $colors) &&
				    array_key_exists('blue', $colors))
					$this->load_num($colors['red'],
					    $colors['green'], $colors['blue']);
				else
					$this->load_num($colors[0],
					    $colors[1], $colors[2]);
			} elseif (preg_match("/^#?[0-9a-fA-F]{6}$/",$args[0]))
				# Hex
				$this->load_string($args[0]);
			elseif ($args[0] && $args[1] && $args[2])
				# Numbers as arguments
				$this->load_num($args[0], $args[1], $args[2]);
			elseif ($args[0] > 1)
				# True value
				$this->load_long($args[0]);
		}

		function fix() {
			$this->red = (int)$this->red;
			$this->green = (int)$this->green;
			$this->blue = (int)$this->blue;

			if ($this->red < 0 || $this->red > 255)
				$this->red = 0;
			if ($this->green < 0 || $this->green > 255)
				$this->green = 0;
			if ($this->blue < 0 || $this->blue > 255)
				$this->blue = 0;
		}

		function to_hex() {
			$this->fix();

			$r1 = floor($this->red / 16);
			$r2 = $this->red % 16;

			$g1 = floor($this->green / 16);
			$g2 = $this->green % 16;

			$b1 = floor($this->blue / 16);
			$b2 = $this->blue % 16;

			$rgb = array(0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
			    "A", "B", "C", "D", "E", "F");

			return ($rgb[$r1] . $rgb[$r2] . $rgb[$g1] . $rgb[$g2] .
			    $rgb[$b1] . $rgb[$b2]);
		}

		function load_hex() {
			$args = func_get_args();

			if (func_num_args() == 3)
				$args[0] .= $args[1] . $args[2];
			if (preg_match("/^#?([a-zA-Z0-9]{2})([a-zA-Z0-9]{2})([a-zA-Z0-9]{2})$/",
			    $args[0], $matches)) {
				$this->red = eval("return 0x$matches[1]");
				$this->green = eval("return 0x$matches[2]");
				$this->blue = eval("return 0x$matches[3]");
			else
				return (FALSE);
			return (TRUE);
		}

		function load_true_hex($num) {
			return $this->load_long($num);
		}

		function to_long() {
			$this->fix();

			return ($this->red * 255 * 255) +
			    ($this->green * 255) + ($this->blue);
		}

		function load_long($num) {
			$this->red = floor($num / (255 * 255));
			$num %= (255 * 255);

			$this->green = floor($num / 255);
			$num %= 255;

			$this->blue = $num;
		}

		function to_num() {
			$this->fix();

			return (array($this->red, $this->green, $this->blue));
		}

		function load_num($r, $b, $g) {
			$this->red = $r;
			$this->green = $g;
			$this->blue = $b;
			$this->fix();
		}

		function to_name() {
			$val = $this->to_long();
			if (array_key_exists($val, $this->colors))
				return ($this->colors[$val]);
			else
				return ("");
		}

		function load_name($name) {
			$name = preg_replace("/\s+/", "", strtolower($name));
			$val = array_search($name, $this->colors);
			if ($val) {
				$this->load_long($val);
				return (TRUE);
			}
			return (FALSE);
		}
	}
?>
