<?php
	/* $Id$ */
	class Graph {
		var	$width	= 100,
			$height	= 100,
			$x_min	= -10,
			$x_max	= 10,
			$x_scl	= 1,
			$y_min	= -10,
			$y_max	= 10,
			$y_scl	= 1,
			$img,
			$expr	= array(),
			$colors	= array(),
			$built	= 0;

		function Graph() {
			$argv = func_get_args();
			$argc = func_num_args();

			switch ($argc) {
			case 6:
				$this->x_min = $argv[0];
				$this->x_max = $argv[1];
				$this->x_scl = $argv[2];
				$this->y_min = $argv[3];
				$this->y_max = $argv[4];
				$this->y_scl = $argv[5];
				break;
			case 8:
				$this->width = $argv[0];
				$this->height = $argv[1];
				$this->x_min = $argv[2];
				$this->x_max = $argv[3];
				$this->x_scl = $argv[4];
				$this->y_min = $argv[5];
				$this->y_max = $argv[6];
				$this->y_scl = $argv[7];
				break;
			case 2:
				$this->width	= $argv[0];
				$this->height	= $argv[1];
				break;
			}
		}

		function add_expr($expr) {
			$funcs = array("abs", "acos", "asin", "atan", "atan2", "base_convert",
			    "ceil", "cos", "exp", "floor", "log", "log10", "pi", "pow", "round",
			    "sin", "sqrt", "tan");
			if (preg_match("!^([-+*/^0-9x (),]|" . join("|", $funcs) . ")+$!", $expr))
				$this->expr[] = preg_replace("/x/i",'$x',$expr);
			else
				return (0);
			return (1);
		}

		function build($connect_points = 0) {
			if ($this->x_min >= $this->x_max ||
			    $this->y_min >= $this->y_max)
				return;

			$this->img = imageCreate($this->width, $this->height);

			# Sets background to white.
			$this->colors["white"] = imageColorAllocate($this->img, 255, 255, 255);
			$this->colors["black"].= imageColorAllocate($this->img, 0, 0, 0);

			$graph_width  = $this->x_max - $this->x_min;
			$graph_height = $this->y_max - $this->y_min;

			$graph_x_mid = $graph_width  / 2;
			$graph_y_mid = $graph_height / 2;

			$x_ratio = $this->width  / $graph_width;
			$y_ratio = $this->height / $graph_height;

			$points = array();

			imageRectangle($this->img, 0, 0, $this->width - 1,
			    $this->height - 1, $this->colors["black"]);

			# If y-axis is present, show it.
			if ($this->x_min < 0 && $this->x_max > 0) {
				imageLine($this->img, abs($this->x_min) * $x_ratio, 0,
				    abs($this->x_min) * $x_ratio, $this->height,
				    $this->colors["black"]);
				for ($i = $this->y_min; $i < $this->y_max;
				    $i += $this->y_scl)
					imageLine($this->img,
					    abs($this->x_min) * $x_ratio - 2,
					    ($i + abs($this->y_min)) * $y_ratio,
					    abs($this->x_min) * $x_ratio + 2,
					    ($i + abs($this->y_min)) * $y_ratio,
					    $this->colors["black"]);
			}

			# If x-axis is present, show it.
			if ($this->y_min < 0 && $this->y_max > 0) {
				imageLine($this->img, 0,
				    $this->height - abs($this->y_min) * $y_ratio,
				    $this->width,
				    $this->height - abs($this->y_min) * $y_ratio,
				    $this->colors["black"]);

				for ($i = $this->x_min; $i < $this->x_max;
				    $i += $this->x_scl)
					imageLine($this->img,
					    ($i + abs($this->x_min)) * $x_ratio,
					    $this->height - abs($this->y_min) * $y_ratio - 2,
					    ($i + abs($this->x_min)) * $x_ratio,
					    $this->height - abs($this->y_min) * $y_ratio + 2,
					    $this->colors["black"]);
			}
/*
			for ($x = $this->x_min; $x < $this->x_max;
			    $x += $this->x_scl) {
				foreach ($this->expr as $expr) {
					@eval("\$y = $expr;");
					if ($y < $this->y_max && $y > $this->y_min) {
						if ($connect_points)
							array_push($points,
							    array(($x + abs($this->x_min)) * $x_ratio,
							    $this->height - ($y + abs($this->y_min)) * $y_ratio));
						else
							imageSetPixel($this->img,
							    ($x + abs($this->x_min)) * $x_ratio,
							    $this->height - ($y + abs($this->y_min)) * $y_ratio,
							    $this->colors["black"]);
					}
				}
			}
*/
			for ($i = 0; $i < $this->width; $i++) {
				foreach ($this->expr as $expr) {
					$x = ($i / $x_ratio) - abs($this->x_min);

					@eval("\$y = $expr;");

					if ($y < $this->y_max &&
					    $y > $this->y_min)
						imageSetPixel($this->img, $i,
						    $this->height - ($y + abs($this->y_min)) * $y_ratio,
						    $this->colors["black"]);
				}
			}

			if ($connect_points) {
				$count = -1 + count($points);
				for ($i = 0; $i < $count; $i++)
					imageLine($this->img, $points[$i][0], $points[$i][1],
					    $points[$i + 1][0], $points[$i + 1][1],
					    $this->colors["black"]);
			}
			$this->built = 1;
		}

		function save($filename, $type) {
			if (!$this->built)
				return;
			switch ($type) {
			case IMG_JPG:
				$image_type = "jpeg";
				break;
			case IMG_PNG:
				$image_type = "png";
				break;
			case IMG_GIF:
				$image_type = "gif";
				break;
			default:
				return;
			}

			eval("image$image_type(\$this->img,\"$filename\")");
		}

		function output($type, $send_headers = 1) {
			if (!$this->built)
				return;
			switch ($type) {
			case IMG_JPG:
				$image_type = "jpeg";
				break;
			case IMG_PNG:
				$image_type = "png";
				break;
			case IMG_GIF:
				$image_type = "gif";
				break;
			default:
				return;
			}

			if ($send_headers && !headers_sent())
				header("Content-type: image/$image_type");
			eval("image$image_type(\$this->img);");
		}

		function free() {
			if (!$this->built)
				return;

			foreach ($this->colors as $color)
				imageColorDeAllocate($this->img, $color);
			imageDestroy($this->img);
		}
	}
?>
