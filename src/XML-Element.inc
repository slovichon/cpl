<?php
	/*
	 * By Jared Yanovich <jaredy@closeedge.net>
	 * Wednesday, February 26, 2003 01:55:23 PM
	 * CPL - XMLElement
	 */

	/*@
<library>
	<name>XMLElement</name>
	<version>1.0</version>
	<description>
		Contains an object-oriented interface to
		XML element creation and handling
	</description>
	<classes>
		<class>
			<name>XMLElement</name>
			<description>
				This main class contains methods
				for creating and manipulating
				objects representing XML elements
			</description>
	@*/
	class XML_Element
	{
		# These properties should be private
		var $tagname;
		var $value;
		var $attrs;

		/*@
		<methods>
			<constructor>
				<arguments>
					<argument>
						<name>tagname</name>
						<type>string</type>
						<description>
							The tagname of the XML
							element
						</description>
					</argument>
				</arguments>
				<description>
					Create a new XML element of the
					argued tagname
				</description>
			</constructor>
			<constructor>
				<arguments>
					<argument>
						<name>tagname</name>
						<type>string</type>
						<description>
							The tagname of the XML
							element
						</description>
					</argument>
					<argument>
						<name>value</name>
						<type>string</type>
						<description>
							The value of the XML
							element node
						</description>
					</argument>
				</arguments>
				<description>
					Create a new XML element node of
					the argued tagname containing
					the argued value
				</description>
			</constructor>
		@*/
		function XML_Element($tag,$value = NULL)
		{
#			$this->tagname	= strToLower($tag);
			$this->tagname	= $tag;
			$this->attrs	= array();
			$this->value	= $value;

			return $this;
		}

		# Since this isn't a valid character, we shouldn't expect to see it
		function set_attribute($name,$value = NULL)
		{
			$this->attrs[$name] = $value;
			return;
		}

		function set_value($value)
		{
			$this->value = $value;
			return;
		}

		function get_attribute($name)
		{
			return $this->attrs[$name];
		}

		function get_value()
		{
			return $this->value;
		}

		function get_xhtml()
		{
			$attrs = "";

			foreach ($this->attrs as $name => $value)
			{
				#				    yes
				$attrs .= $value == NULL ? " $name=\"$name\"" : " $name=\"$value\"";
			}

			return $this->value ? "<$this->tagname$attrs>$this->value</$this->tagname>" : "<$this->tagname$attrs />";
		}

		function get()
		{
			return $this->get_xhtml();
		}

		function get_html()
		{
			$attrs = "";

			foreach ($this->attrs as $name => $value)
			{
				$attrs .= $value == "<" ? " $name" :  " $name=\"$value\"";
			}

			return $this->value ? "<$this->tagname$attrs>$this->value</$this->tagname>" : "<$this->tagname$attrs>";
		}
	}
?>
