<?php
	/*
	 * By Jared Yanovich <jaredy@closeedge.net>
	 * Friday, March 14, 2003 03:56:10 AM
	 * OFPR-HTML - Pref repository for OF-HTML
	 *
	 * This class just defines which preferences are valid
	 * for OF-HTML
	 */

	require_once 'OFPR/OFPR.inc';
	require_once 'CPL/CPL.inc';

	class OFPR_HTML extends OFPR
	{
		function OFPR_HTML($prefs)
		{
			$this->dec =	array
					(
					);

			return $this;
		}
	}
?>
