<?php
	/* $Id$ */
	require_once 'CPL.inc';

	class Benchmark {
		var $ts;

		function time($code, $loops = 1) {
			if (function_exists($code))
				$code .= "()";

			$i = 0;
			while ($i++ < $loops)
				$code .= ";$code";

			$this->start();
			eval($code);
			$diff = $this->end();
			return ($diff);
		}

		function start() {
			$this->ts = new TimeStamp();
		}

		function end() {
			$end = new TimeStamp();

			if (!$this->ts())
				CPL::handle_error("Benchmark::end() called before Benchmark::start()");

			$start = $this->ts;
			$this->ts = NULL;
			return ($end->subtract($start));
		}
	}
?>
