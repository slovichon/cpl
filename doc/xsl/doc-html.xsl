<?xml version="1.0" ?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output indent="yes" />

<xsl:template match="library">
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
        "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xml:lang="en-US" xmlns="http://www.w3.org/1999/xhtml">
        <head>
                <title>EasyPHP - <?php echo $PAGE["title"]; ?></title>
                <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
                <meta http-equiv="Content-Style-Type" content="text/css" />
                <link rel="stylesheet" type="text/css" href="/home/jaredy/sites/easyphp.net/htdocs/styles.css" media="screen" />
        </head>
        <body>
                <div class="layoutSection" style="width:808px; margin:8px; ">
			<div class="header1">
				<xsl:value-of select="name" /> - <xsl:value-of select="version" /></div>
			<p><xsl:value-of select="description" /></p>
			<xsl:apply-templates select="constants|functions|classes" />
		</div>
	</body>
</html>
</xsl:template>

<xsl:template match="constants">
	<div class="header2">Constants</div>
	<p>This library defines the following constants.</p>
	<table cellspacing="1" cellpadding="3" border="0" bgcolor="#000033" width="95%" align="center">
		<tr>
			<th width="10%">Name</th>
			<th>Description</th>
		</tr>
	<xsl:for-each select="constant">
		<tr>
			<td class="data{((position() - 1) mod 2) + 1}"><tt><xsl:value-of select="name" /></tt></td>
			<td class="data{((position() - 1) mod 2) + 1}"><xsl:value-of select="description" /></td>
		</tr>
	</xsl:for-each>
	</table>
</xsl:template>

<xsl:template match="functions">
	<div class="header2">Functions</div>
	<p>This library defines the following functions.</p>
	<xsl:for-each select="function">
	<table cellspacing="1" cellpadding="3" border="0" bgcolor="#000033" width="95%" align="center">
		<tr>
			<th colspan="2"><xsl:value-of select="name" /></th>
		</tr>
		<tr>
			<td class="desc" width="10%">Prototype:</td>
			<td class="data{((position() - 1) mod 2) + 1}">
				<tt>
				<xsl:value-of select="return-value/type" />
				<xsl:text> </xsl:text>
				<xsl:value-of select="name" />(
		<xsl:for-each select="arguments/argument">
				<xsl:value-of select="type" />
				$<xsl:value-of select="name" />
			<xsl:if test="position() != last()">,</xsl:if>
		</xsl:for-each>
				)</tt></td>
		</tr>
		<xsl:if test="count(arguments/argument)">
		<tr>
			<td class="desc" rowspan="{count(arguments/argument)}">Arguments</td>
			<xsl:choose>
				<xsl:when test="(position() - 1) mod 2">
					<xsl:call-template name="t_secondrow" />
				</xsl:when>
				<xsl:otherwise>
					<xsl:call-template name="t_firstrow" />
				</xsl:otherwise>
			</xsl:choose>
		</tr>
		</xsl:if>
		<tr>
			<td class="desc">Description:</td>
			<td class="data{((position() - 1) mod 2) + 1}"><xsl:value-of select="description" /></td>
		</tr>
		<tr>
			<td class="desc">Returns:</td>
			<td class="data{((position() - 1) mod 2) + 1}"><xsl:value-of select="return-value/description" /></td>
		</tr>
	</table>
	<br />
	</xsl:for-each>
</xsl:template>

<xsl:template name="t_firstrow">
			<xsl:for-each select="arguments/argument">
			<td class="data1">
				<tt>$<xsl:value-of select="name" /></tt> -
				<xsl:value-of select="description" />
			</td>
				<xsl:if test="position() != last()">
		<xsl:text disable-output-escaping="yes">&lt;/tr&gt;</xsl:text>
		<xsl:text disable-output-escaping="yes">&lt;tr&gt;</xsl:text>
				</xsl:if>
			</xsl:for-each>
</xsl:template>

<xsl:template name="t_secondrow">
			<xsl:for-each select="arguments/argument">
			<td class="data2">
				<tt>$<xsl:value-of select="name" /></tt> -
				<xsl:value-of select="description" />
			</td>
				<xsl:if test="position() != last()">
		<xsl:text disable-output-escaping="yes">&lt;/tr&gt;</xsl:text>
		<xsl:text disable-output-escaping="yes">&lt;tr&gt;</xsl:text>
				</xsl:if>
			</xsl:for-each>
</xsl:template>

<xsl:template match="classes">
	<div class="header2">Classes</div>
	<p>This library defines the following classes.</p>
	<xsl:for-each select="class">
	<div style="width:98%;" class="header3"><xsl:value-of select="name" /></div>
	<p><xsl:value-of select="description" /></p>
		<xsl:if test="count(properties/property)">
	<br/>
	<table cellspacing="1" cellpadding="3" border="0" bgcolor="#000033" width="95%" align="center">
		<tr>
			<th colspan="2">Properties</th>
		</tr>
			<xsl:for-each select="properties/property">
		<tr>
			<td class="data{((position() - 1) mod 2) + 1}">
				<tt><xsl:value-of select="type" />
				$obj-&gt;<xsl:value-of select="name" /></tt> - 
				<xsl:value-of select="description" />
			</td>
		</tr>
			</xsl:for-each>
	</table>
		</xsl:if>
		<xsl:if test="count(methods/method)">
	<br/>
	<table cellspacing="1" cellpadding="3" border="0" bgcolor="#000033" width="95%" align="center">
		<tr>
			<th colspan="2">Methods</th>
		</tr>
			<xsl:for-each select="methods/method|methods/constructor">
		<tr>
			<td class="th4" colspan="2">
				<xsl:choose>
					<xsl:when test="name() = 'constructor'">
						(Constructor)
					</xsl:when>
					<xsl:otherwise>
						<xsl:value-of select="name" />
					</xsl:otherwise>
				</xsl:choose>
			</td>
		</tr>
		<tr>
			<td class="desc" width="10%">Prototype:</td>
			<td class="data{((position() - 1) mod 2) + 1}">
				<tt>
				<xsl:choose>
					<xsl:when test="name() = 'constructor'">
						new <xsl:value-of select="../../name" />(
						<xsl:for-each select="arguments/argument">
							<xsl:value-of select="type" />
							$<xsl:value-of select="name" />
							<xsl:if test="position() != last()">,</xsl:if>
						</xsl:for-each>
						)
					</xsl:when>
					<xsl:otherwise>
						<xsl:choose>
							<xsl:when test="return-value">
								<xsl:value-of select="return-value/type" />
							</xsl:when>
							<xsl:otherwise>
								void
							</xsl:otherwise>
						</xsl:choose>
						$obj-&gt;<xsl:value-of select="name" />(
						<xsl:for-each select="arguments/argument">
							<xsl:value-of select="type" />
							$<xsl:value-of select="name" />
							<xsl:if test="position() != last()">,</xsl:if>
						</xsl:for-each>
						)
					</xsl:otherwise>
				</xsl:choose>
				</tt>
			</td>
		</tr>
				<xsl:if test="count(arguments/argument)">
		<tr>
			<td class="desc" rowspan="{count(arguments/argument)}">Arguments:</td>
					<xsl:choose>
						<xsl:when test="(position() - 1) mod 2">
							<xsl:call-template name="t_secondrow" />
						</xsl:when>
						<xsl:otherwise>
							<xsl:call-template name="t_firstrow" />
						</xsl:otherwise>
					</xsl:choose>
		</tr>
				</xsl:if>
		<tr>
			<td class="desc">Description:</td>
			<td class="data{((position() - 1) mod 2) + 1}"><xsl:value-of select="description" /></td>
		</tr>
				<xsl:if test="return-value">
		<tr>
			<td class="desc">Returns:</td>
			<td class="data{((position() - 1) mod 2) + 1}"><xsl:value-of select="return-value/description" /></td>
		</tr>
				</xsl:if>
			</xsl:for-each>
	</table>
		</xsl:if>
	</xsl:for-each>
</xsl:template>

</xsl:stylesheet>
