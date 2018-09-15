<?php
	/* $Id$ */
	/*
	 * CPL - CPL
	 *
	 * Various notes
	 *
	 * (*)	We can't use $this anywhere in this class
	 *	as a particular instance may not have been
	 *	initialized. In fact, it *shouldn't* have
	 *	been initialized, as they methods should
	 *	be more procedural as opposed to object-
	 *	oriented. For example,
	 *
	 *		CPL::define()
	 *
	 *	as opposed to
	 *
	 *		$cpl = new CPL();
	 *		$cpl->define();
	 */
	/*@
<library>
	<name>CPL</name>
	<version>1.1</version>
	<description>
		This library contains API functions common to all Common
		PHP Libraries.
	</description>
	<classes>
		<class>
			<name>CPL</name>
			<description>
				This class contains methods of all common
				functionality required by CPL libraries.
			</description>
			<methods>
	@*/
	class CPL
	{
		/*@
		<method>
			<name>define</name>
			<description>
				This method defines a constant. If the constant
				is already defined with a value different from
				that of the argued one, an error is thrown,
				see <method-ref>handle_error</method-ref>. If
				the constant has already been initialized to
				the argued value, then all is well.
			</description>
			<arguments>
				<argument>
					<name>constant</name>
					<type>string</type>
					<description>
						The identifier to which make
						a constant
					</description>
				</argument>
				<argument>
					<name>value</name>
					<type>mixed</type>
					<description>
						The value the new constant
						should uphold
					</description>
				</argument>
			</arguments>
		</method>
		@*/
		function define($var,$val) {
			if (defined($var)) {
				if (constant($var) != $val)
					CPL::handle_error("CPL constant already defined " .
					    "with inconsistent value; constant: $var; " .
					    "bad value: " . constant($var) . "; original value: $val");
			} else {
				if (!@define($var, $val, TRUE))
					CPL::handle_error("Could not define() constant; constant: $var");
			}
		}

		/*@
		<method>
			<name>nice_define</name>
			<description>
				This method &quot;nicely&quot; tries to define
				a constant, in honor of the Unix nice(1)
				utility. If the value has already been defined,
				this method does nothing; else it will try
				and define the constant with the argued value.
			</description>
			<arguments>
				<argument>
					<name>constant</name>
					<type>string</type>
					<description>
						The identifier to which make
						a constant
					</description>
				</argument>
				<argument>
					<name>value</name>
					<type>mixed</type>
					<description>
						The value the new constant
						should uphold
					</description>
				</argument>
			</arguments>
			<return-value>
				<type>boolean</type>
				<description>
					If the constant could be defined TRUE
					is returned, else FALSE is returned
				</description>
			</return-value>
		</method>
		@*/
		function nice_define($var, $val) {
			if (!defined($var)) {
				define($var, $val, TRUE);
				return (TRUE);
			}
			return (FALSE);
		}

		/*@
		<method>
			<name>error_log</name>
			<description>
				Get the current path and filename to which
				errors will be logged
			</description>
			<return-value>
				<type>string</type>
				<description>
					The path and filename to the current
					error log
				</description>
			</return-value>
		</method>
		<method>
			<name>error_log</name>
			<arguments>
				<argument>
					<name>error_log</name>
					<type>string</type>
					<description>
						The new path and filename to become the
						desired error log file. In the case of
						an error, an attempt will be made to open
						this file in append mode and write error
						information to it.
					</description>
				</argument>
			</arguments>
			<description>
				Set the path and filename of the
				error log
			</description>
			<return-value>
				<type>string</type>
				<description>
					The path and filename of the
					new error log
				</description>
			</return-value>
		</method>
		@*/
		function error_log() {
			static $error_log = NULL;

			$args = func_get_args();
			if (count($args) == 1) {
				if (is_writable($args[0]))
					$error_log = $args[0];
				else
					CPL::handle_error("Error log set to " .
					    "unwritable file; file: $args[0]");
			}
			return ($error_log);
		}

		/*@
		<method>
			<name>display_errors</name>
			<description>
				Find out if whether or not to display
				errors to standard output
			</description>
			<return-value>
				<type>boolean</type>
				<description>
					The value of determining whether
					or not to display error output to
					standard output
				</description>
			</return-value>
		</method>
		<method>
			<name>display_errors</name>
			<arguments>
				<argument>
					<name>display_errors</name>
					<type>boolean</type>
					<description>
						The value of whether or not
						to display error output to
						standard output
					</description>
				</argument>
			</arguments>
			<description>
				Set whether or not to display
				error output to standard output
			</description>
			<return-value>
				<type>boolean</type>
				<description>
					The new value to determine whether
					or not to display error output to
					standard output
				</description>
			</return-value>
		</method>
		@*/
		function display_errors() {
			static $display_errors = FALSE;

			if (func_num_args() == 1) {
				$args = func_get_args();
				$display_errors = $args[0];
			}
			return ($display_errors);
		}

		/*@
		<method>
			<name>error_handler</name>
			<description>
				Get the current function to which
				error-handling is delegated
			</description>
			<return-value>
				<type>string</type>
				<description>
					The name of the function
					that will be called to
					handle errors
				</description>
			</return-value>
		</method>
		<method>
			<name>error_handler</name>
			<arguments>
				<argument>
					<name>error_handler</name>
					<type>string</type>
					<description>
						A function name. Note that this
						function will be invoked with
						a single argument containing the
						error message of the problem
					</description>
				</argument>
			</arguments>
			<description>
				Set the function to which
				error-handling is to be delegated
			</description>
			<return-value>
				<type>boolean</type>
				<description>
					The new name of a function to
					which error-handling has been
					delegated
				</description>
			</return-value>
		</method>
		@*/
		function error_handler() {
			static $error_handler = NULL;

			if (func_num_args() == 1) {
				$args = func_get_args();

				if (function_exists($args[0]))
					$error_handler = $args[0];
				else
					CPL::handle_error("Error handler set to undefined " .
					    "function; function: $args[0]");
			}

			return ($error_handler);
		}
	
		/*@
		<method>
			<name>trigger_errors</name>
			<description>
				Determine when errors will be triggered
				to PHP's error-handling level
			</description>
			<return-value>
				<type>boolean</type>
				<description>
					A value of TRUE that suggests
					that errors will be triggered
					or FALSE indicating that they
					will not
				</description>
			</return-value>
		</method>
		<method>
			<name>trigger_errors</name>
			<arguments>
				<argument>
					<name>trigger_errors</name>
					<type>boolean</type>
					<description>
						A value indicating
						whether or not to
						trigger errors at
						PHP's level
					</description>
				</argument>
			</arguments>
			<description>
				Set whether or not errors should be
				triggered to PHP's error-handling
				level
			</description>
			<return-value>
				<type>boolean</type>
				<description>
					The new value indicating
					whether errors should be
					triggered at PHP's level
				</description>
			</return-value>
		</method>
		@*/
		function trigger_errors() {
			static $trigger_errors = FALSE;

			if (func_num_args() == 1) {
				$args = func_get_args();
				$trigger_errors = $args[0];
			}
			return ($trigger_errors);
		}

		/*@
		<method>
			<name>handle_error</name>
			<arguments>
				<argument>
					<name>msg</name>
					<type>string</type>
					<description>
						A descriptive error message
					</description>
				</argument>
			</arguments>
			<description>
				Handle an error with a error message.
				Error-handling shall be performed according
				to the values set by the other methods of
				this class relating to error-handling.
			</description>
		</method>
		@*/
		function handle_error($msg) {
			global $php_errormsg;

			if (CPL::trigger_errors()) {
				trigger_error($msg, E_USER_ERROR);
			} elseif ($f = CPL::error_handler()) {
				$f($msg);
			} elseif (CPL::display_errors()) {
				echo $msg;
			} elseif ($f = CPL::error_log()) {
				if ($fp = @fopen($f, "a")) {
					fputs($fp, "CPL Error: $msg; " .
					    "PHP Error Message: $php_errormsg; " .
					    "Date: " . date("l F a, Y h:i:s A") . "\n");
					fclose($fp);
				}
			}
		}
		/*@
		</methods>
		@*/
	}
	/*@
		</class>
	</classes>
</library>
	@*/
?>
