<?php
	/*
	 * By Jared Yanovich <jaredy@closeedge.net>
	 * Friday, March 14, 2003 05:12:18 AM
	 * QParse-ini - Quick .ini file type parser
	 */
	
/*@
<library>
	<name>QParse_ini</name>
	<version>0.1</version>
	<description>
	</description>
	<classes>
		<class>
			<name>QParse_init</name>
			<description>
			</description>
			<methods>
@*/
	class QParse_ini
	{
		/*@
		<constructor>
			<description>
				Creates a new QParse_ini parser
			</description>
		</constructor>
		@*/
		function QParse_ini()
		{
			return $this;
		}

		/*@
		<method>
			<name>parse</name>
			<arguments>
				<argument>
					<name>inidata</name>
					<type>string</string>
					<description>
						A string containing data
						in .ini file format
					</description>
				</argument>
			</arguments>
			<description>
				Parses init data
			</description>
			<return-value>
				<type>array</type>
				<description>
					Returns an array of the values
					specified in the ini data
				</description>
			</return-value>
		</method>
		@*/
		function parse($str)
		{
			# Strip comments
#			preg_replace("/(?:.*?);.*/","",$lines);

			# Skip blank lines
#			preg_replace("/\n\n/",		"\n",	$lines);
#			preg_replace("/\r\n\r\n/",	"\r\n",	$lines);
#			preg_replace("/\r\r/",		"\r",	$lines);

			$lines	= preg_split("/\n|\r\n|\r/",$str);
			$data	= array();
			$group	= NULL;
			$len	= count($lines);

			for ($i = 0; $i < $len; $i++)
			{
				$line = $lines[$i];

				# Skip blank lines
				if
				(
					preg_match
					(
						"/
							^		# beginning
							(		# save in \\1
								\n	# (unix newline)blank(unix newline)
								|	# or
								\r\n	# (win newline)blank(win newline)
								|	# or
								\r	# (mac newline)blank(mac newline)
							)
							\s*		# whitespace
							(?:
								;.*	# comment
								\s*	# whitespace
							)
							?		# comment is optional
							\\1		# consecutive newline
							$		# end-of-line
						/x",
						$line
					)
				)
					continue;

				if
				(
					preg_match
					(
						"/
							^		# beginning
							\s*		# whitespace
							\[		# literal '['
							\w+		# word chars (identifier)
							\]		# literal ']'
							\s*		# word chars
							(?:
								;.*	# comment
								\s*	# whitespace
							)
							?		# comment is optional
							$		# end-of-line
						/x",
						$line,
						$matches
					)
				)
				{
					$group		= $matches[1];
					$data[$group]	= array();
					
				} else if
				(
					preg_match
					(
						"/
							^		# beginning
							\s*		# whitespace
							\w+		# word chars (identifier)
							(\s*)		# whitespace ($1)
							=		# literal '='
							\s*		# whitespace
							(		# value ($2)
								\".*?\"	# double-quoted value
								|	# or
								'.*?'	# single-quoted value
								|	# or
								.*?	# value
							)
							\s*		# whitespace
							(?:
								;.*	# comment
								\s*	# whitespace
							)
							?		# comment is optional
							$		# end-of-line
						/x",
						$line,
						$matches
					)
				)
				{
					if (!$group)
						CPL::handle_error("QParse: value found outside of any group; line: $i");

					$matches[2] = preg_replace("/^'(.*)'$/",	"$1",$matches[2]);
					$matches[2] = preg_replace("/^\"(.*)\"$/",	"$1",$matches[2]);

					$data[$group][$matches[1]] = $matches[2];
				}
			}

			return $data;
		}

		/*@
		<method>
			<name>parse_file</name>
			<arguments>
				<argument>
					<name>file</name>
					<type>string</type>
					<description>
						A file in .ini file format
					</description>
				</argument>
			</arguments>
			<description>
				Parses an ini file
			</description>
			<return-value>
				<type>array</type>
				<description>
					Returns an array containing values
					as specified as from the ini data
				</description>
			</return-value>
		</method>
		@*/
		function parse_file($file)
		{
			$fp = @fopen($file,"r");

			if (!$fp)
				CPL::handle_error("QParse: unable to parse ini file: file: $file");

			$size		= @filesize($file);
			$contents	= @fread($fp,$size);

			fclose($fp);
			
			return $this->parse($contents);
		}
	/*@
	</methods>
	@*/
	}
	/*@
	</class>
</library>
	@*/
?>
