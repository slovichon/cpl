<?php
	/*
	 * By Jared Yanovich <jaredy@closeedge.net>
	 * Sunday, March 16, 2003 02:53:45 AM
	 * QParse-ini - Quick .ini file type parser
	 */
	
/*@
<library>
	<name>QParse-XML</name>
	<version>0.1</version>
	<description>
	</description>
	<classes>
		<class>
			<name>QParse-XML</name>
			<description>
			</description>
			<methods>
@*/
	class QParse_XML
	{
		/*@
		<constructor>
			<description>
				Creates a new QParse_ini parser
			</description>
		</constructor>
		@*/
		function QParse_XML()
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
