<?php
	/* $Id$ */
	class TimeStamp {
		var $year;
		var $month;
		var $day;
		var $hour;
		var $minute;
		var $second;
		var $timezone;

		function valid_timezone($timezone) {
			return in_array(strToUpper($timezone),$this->_timezones());
		}

		function _timezones() {
			return array("CET", "CST", "CDT", "EET", "EST", "EDT",
			    "GB", "GMT", "HST", "MET", "MST", "MDT",
			    "NZ", "PRC", "PST", "PDT", "ROC", "ROK",
			    "UCT", "US", "UTC", "W-SU", "WET");
		}

		function Timestamp($year = 0, $month = 0, $day = 0, $hour = 0,
		    $min = 0, $sec = 0, $timezone = "") {
			if (is_array($year)) {
				/* Array of value pairs */
				$this->load_array($year);
			} elseif (strlen($year) == 14) { # YYYYMMDDHHMMSS
				/* String timestamp */
				$this->load_string($year);
			} elseif ($year || $month || $day || $hour || $min || $sec) {
				/* Individual arguments */
				$this->year	= $year;
				$this->month	= $month;
				$this->day	= $day;
				$this->hour	= $hour;
				$this->minute	= $min;
				$this->second	= $sec;

				$this->set_timezone($timezone);

			/* UNIX timestamp */
			} elseif (is_int($year)) {
				$this->load_unix($year);
			}
		}

		function get_unix() {
			$this->fix();

			return mktime($this->hour, $this->minute, $this->second,
			    $this->month, $this->day, $this->year);
		}

		function get_string() {
			$this->fix();

			return sprintf("%04d%02d%02d%02d%02d%02d", $this->year,
			    $this->month, $this->day, $this->hour, $this->minute,
			    $this->second);
		}

		function load_unix($ts) {
			list($this->year, $this->month, $this->day,
			    $this->hour, $this->minute, $this->second) =
			    explode(" ",date("Y m d H i s",$ts));
		}

		function format($format = "m-d-y H:i:s") {
			return date($format, mktime(
			    $this->hour, $this->minute, $this->second,
			    $this->month, $this->day, $this->year));
		}

		/* Deprecated -- for backwards compatilibility only!! */
		function set_string($ts) {
			return $this->load_string($ts);
		}

		function load_string($ts) {
			if (preg_match("/^(\d{4})(\d\d)(\d\d)(\d\d)(\d\d)(\d\d)$/",
			    $ts, $matches)) {
				list(, $this->year, $this->month, $this->day,
				    $this->hour, $this->minute, $this->second) =
				    $matches;
				return TRUE;
			}
			return FALSE;
		}

		function add($ts) {
			return new TimeStamp(array(
				'year'		=> $this->year		+ $ts->year,
				'month'		=> $this->month		+ $ts->month,
				'day'		=> $this->day		+ $ts->day,
				'hour'		=> $this->hour		+ $ts->hour,
				'minute'	=> $this->minute	+ $ts->minute,
				'second'	=> $this->second	+ $ts->second
			));
		}

		function subtract($ts) {
			return new	TimeStamp
					(
						array
						(
							'year'		=> $this->year		- $ts->year,
							'month'		=> $this->month		- $ts->month,
							'day'		=> $this->day		- $ts->day,
							'hour'		=> $this->hour		- $ts->hour,
							'minute'	=> $this->minute	- $ts->minute,
							'second'	=> $this->second	- $ts->second
						)
					);
		}

		function fix()
		{
			$days_per_month	= array(31,28,31,30,31,30,31,31,30,31,30,31);

			$this->year	= (int) $this->year;
			$this->month	= (int) $this->month;
			$this->day	= (int) $this->day;
			$this->hour	= (int) $this->hour;
			$this->minute	= (int) $this->minute;
			$this->second	= (int) $this->second;

			$this->minute	+= (int) $this->second / 60;
			$this->second	%= 60;

			$this->hour	+= (int) $this->minute / 60;
			$this->minute	%= 60;

			$this->day	+= (int) $this->hour / 24;
			$this->hour	%= 24;

			while ($this->day > $days_per_month[$this->month - 1])
				$this->day -= $days_per_month[$this->month++ - 1];

			$this->year	+= (int) $this->month / 12;
			$this->month	%= 12;

			return;
		}

		function get_utc()
		{
			return $this->format("r");
		}

		function get_gmt()
		{
			return $this->get_utc();
		}

		function load_utc($utc)
		{
			$months	=	array
					(
						"Jan" => 1,
						"Feb" => 2,
						"Mar" => 3,
						"Apr" => 4,
						"May" => 5,
						"Jun" => 6,
						"Jul" => 7,
						"Aug" => 8,
						"Sep" => 9,
						"Oct" => 10,
						"Nov" => 11,
						"Dec" => 12
					);

			# Thu, 21 Dec 2000 16:01:07 +0200
			preg_match
			(
				"{
					^
					\s*
					(Sun|Mon|Tue|Wed|Thu|Fri|Sat),
					\s+
					(\d{1,2})
					\s+
					()
					\s+
					(\d+)
					\s+
					(\d{1,2}):
					(\d{1,2}):
					(\d{1,2})
					(?:\s+([+-]?\d{4}))?
					\s*
					$
				}x",
				$utc,
				$matches
			);

			list
			(
				,
				$weekday,
				$this->day,
				$mon_abbr,
				$this->year,
				$this->hour,
				$this->minute,
				$this->second,
				$offset

			) = $matches;

			$this->month = $months[$mon_abbr];

			return;
		}

		function load_gmt($utc)
		{
			return $this->load_utc($utc);
		}

		function load_now()
		{
			return $this->load_current();
		}

		function load_current()
		{
			$date = explode(" ",date("Y m d H i s"));

			list
			(
				$this->year,
				$this->month,
				$this->day,
				$this->hour,
				$this->minute,
				$this->second

			) = $date;

			return;
		}

		function get_weekday($string = TRUE)
		{
			return $string ? $this->format("l") : $this->format("w");
		}

		function set_timezone($tz)
		{
			if ($tz && is_valid_timezone($tz))
			{
				$this->timezone = $tz;
			} else {
				$this->timezone = date("T");
			}

			setlocale("tz",$this->timezone);

			return;
		}

		function change_timezone($tz)
		{
			if (!timezone_is_valid($tz))
				return FALSE;

			$this->hour += ((int)date("O",$tz) - (int)$date("O",$this->timezone)) / 100;

			$this->set_timezone($tz);

			return TRUE;
		}

		function is_set()
		{
			return	$this->year	!= NULL &&
				$this->month	!= NULL &&
				$this->day	!= NULL &&
				$this->hour	!= NULL &&
				$this->minute	!= NULL &&
				$this->second	!= NULL;
		}

		function clear()
		{
			$this->year	= NULL;
			$this->month	= NULL;
			$this->day	= NULL;
			$this->hour	= NULL;
			$this->minute	= NULL;
			$this->second	= NULL;

			$this->timezone	= "";

			return;
		}
	}
?>
