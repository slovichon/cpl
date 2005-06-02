<?xml version="1.0" ?>
<!-- $Id$ -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output indent="yes" method="text" />

<xsl:template match="lib">
	<xsl:text>
<![CDATA[
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
 "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xml:lang="en-US" xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<title>CPL - ]]></xsl:text>
	<xsl:value-of select="name" />
	<xsl:text><![CDATA[</title>
		<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
		<meta http-equiv="Content-Style-Type" content="text/css" />
		<style type="text/css">
			body {
				font-family: Tahoma, sans-serif;
			}

			h2 {
				color: #336699;
				border: 1px solid #336699;
				background-color: #FFFFCC;
				padding: 3px;
			}

			.tbl {
				background-color: #336699;
				width: 100%;
			}

			td {
				background-color: #FFFFFF;
			}

			th {
				color: #FFFFFF;
			}

			.desc {
				text-align: right;
				font-weight: bold;
				background-color: #FFFFCC;
			}

			.th4 {
				color: #336699;
				font-weight: bold;
			}

			.data1 {
				background-color: #EEEEEE;
			}

			.data2 {
				background-color: #EEEEFF;
			}
		</style>
	</head>
	<body>
		<h1>CPL - ]]></xsl:text>
	<xsl:value-of select="name" />
	<xsl:text><![CDATA[</h1>
			<p>]]></xsl:text>
	<xsl:value-of select="desc" />
	<xsl:text><![CDATA[</p>]]></xsl:text>
			<xsl:apply-templates select="constants|functions|classes" />
	<xsl:text><![CDATA[
		</div>
	</body>
</html>]]></xsl:text>
</xsl:template>

<xsl:template match="constants">
	<xsl:text><![CDATA[
	<h2>Constants</h2>
	<p>This library defines the following constants.</p>
	<table cellspacing="1" cellpadding="3" border="0" class="tbl">
		<tr>
			<th>Name</th>
			<th>Description</th>
		</tr>]]></xsl:text>
	<xsl:for-each select="constant">
		<xsl:text><![CDATA[
		<tr>
			<td class="data]]></xsl:text>
		<xsl:value-of select="((position() - 1) mod 2) + 1" />
		<xsl:text><![CDATA["><tt>]]></xsl:text>
		<xsl:value-of select="name" />
		<xsl:text><![CDATA[</tt></td>
			<td class="data]]></xsl:text>
		<xsl:value-of select="((position() - 1) mod 2) + 1" />
		<xsl:text><![CDATA[">]]></xsl:text>
		<xsl:value-of select="desc" />
		<xsl:text><![CDATA[</td>
		</tr>]]></xsl:text>
	</xsl:for-each>
	<xsl:text><![CDATA[</table>]]></xsl:text>
</xsl:template>

<xsl:template match="functions">
	<xsl:text><![CDATA[
	<h2>Functions</h2>
	<p>This library defines the following functions.</p>]]></xsl:text>
	<xsl:for-each select="function">
		<xsl:text><![CDATA[
	<table cellspacing="1" cellpadding="3" border="0" class="tbl">
		<tr>
			<th colspan="2">]]></xsl:text>
		<xsl:value-of select="name" />
		<xsl:text><![CDATA[</th>
		</tr>
		<tr>
			<td class="desc" width="10%">Prototype:</td>
			<td class="data]]></xsl:text>
		<xsl:value-of select="((position() - 1) mod 2) + 1" />
		<xsl:text><![CDATA[">
				<tt>]]></xsl:text>
		<xsl:value-of select="retval/type" />
		<xsl:text> </xsl:text>
		<xsl:value-of select="name" />
		<xsl:text>(</xsl:text>
		<xsl:for-each select="args/arg">
			<xsl:value-of select="type" />
			<xsl:text>$</xsl:text>
			<xsl:value-of select="name" />
			<xsl:if test="position() != last()">, </xsl:if>
		</xsl:for-each>
		<xsl:text><![CDATA[)</tt></td>
		</tr>]]></xsl:text>
		<xsl:if test="count(args/arg)">
			<xsl:text><![CDATA[
		<tr>
			<td class="desc" rowspan="]]></xsl:text>
			<xsl:value-of select="count(args/arg)" />
			<xsl:text><![CDATA[">Arguments</td>]]></xsl:text>
			<xsl:choose>
				<xsl:when test="(position() - 1) mod 2">
					<xsl:call-template name="t_secondrow" />
				</xsl:when>
				<xsl:otherwise>
					<xsl:call-template name="t_firstrow" />
				</xsl:otherwise>
			</xsl:choose>
			<xsl:text><![CDATA[</tr>]]></xsl:text>
		</xsl:if>
		<xsl:text><![CDATA[
		<tr>
			<td class="desc">Description:</td>
			<td class="data]]></xsl:text>
		<xsl:value-of select="((position() - 1) mod 2) + 1" />
		<xsl:text><![CDATA[">]]></xsl:text>
		<xsl:value-of select="desc" />
		<xsl:text><![CDATA[</td>
		</tr>
		<tr>
			<td class="desc">Returns:</td>
			<td class="data]]></xsl:text>
		<xsl:value-of select="((position() - 1) mod 2) + 1" />
		<xsl:text><![CDATA[">]]></xsl:text>
		<xsl:value-of select="retval/desc" />
		<xsl:text><![CDATA[</td>
		</tr>
	</table>
	<br />]]></xsl:text>
	</xsl:for-each>
</xsl:template>

<xsl:template name="t_firstrow">
	<xsl:for-each select="args/arg">
		<xsl:text><![CDATA[
			<td class="data1">
				<tt>$]]></xsl:text>
		<xsl:value-of select="name" />
		<xsl:text><![CDATA[</tt> - ]]></xsl:text>
		<xsl:value-of select="desc" />
		<xsl:text><![CDATA[</td>]]></xsl:text>
		<xsl:if test="position() != last()">
			<xsl:text><![CDATA[</tr>
		<tr>]]></xsl:text>
		</xsl:if>
	</xsl:for-each>
</xsl:template>

<xsl:template name="t_secondrow">
	<xsl:for-each select="args/arg">
		<xsl:text><![CDATA[
			<td class="data2">
				<tt>$]]></xsl:text>
		<xsl:value-of select="name" />
		<xsl:text><![CDATA[</tt> - ]]></xsl:text>
		<xsl:value-of select="desc" />
		<xsl:text><![CDATA[</td>]]></xsl:text>
		<xsl:if test="position() != last()">
			<xsl:text><![CDATA[</tr>]]></xsl:text>
			<xsl:text><![CDATA[<tr>]]></xsl:text>
		</xsl:if>
	</xsl:for-each>
</xsl:template>

<xsl:template match="classes">
	<xsl:text><![CDATA[
	<h2>Classes</h2>
	<p>This library defines the following classes.</p>]]></xsl:text>
	<xsl:for-each select="class">
		<xsl:text><![CDATA[<h3>]]></xsl:text>
		<xsl:value-of select="name" />
		<xsl:text><![CDATA[</h3>
	<div style="margin-left: 10px">
	<p>]]></xsl:text>
		<xsl:value-of select="desc" />
		<xsl:text><![CDATA[</p>]]></xsl:text>
		<xsl:if test="count(prop/prop)">
			<xsl:text><![CDATA[<br />
	<table cellspacing="1" cellpadding="3" border="0" class="tbl">
		<tr>
			<th colspan="2">Properties</th>
		</tr>]]></xsl:text>
			<xsl:for-each select="props/prop">
				<xsl:text><![CDATA[
		<tr>
			<td class="data]]></xsl:text>
				<xsl:value-of select="((position() - 1) mod 2) + 1" />
				<xsl:text><![CDATA[">
				<tt>]]></xsl:text>
				<xsl:value-of select="type" />
				<xsl:text>$obj-&gt;</xsl:text>
				<xsl:value-of select="name" />
				<xsl:text><![CDATA[</tt> - ]]></xsl:text>
				<xsl:value-of select="desc" />
				<xsl:text><![CDATA[</td>
		</tr>]]></xsl:text>
			</xsl:for-each>
		<xsl:text><![CDATA[
	</table>]]></xsl:text>
	</xsl:if>
	<xsl:if test="count(methods/method)">
		<xsl:text><![CDATA[
	<br/>
	<table cellspacing="1" cellpadding="3" border="0" class="tbl">
		<tr>
			<th colspan="2">Methods</th>
		</tr>]]></xsl:text>
			<xsl:for-each select="methods/method|methods/ctor">
				<xsl:text><![CDATA[
		<tr>
			<td class="th4" colspan="2">]]></xsl:text>
				<xsl:choose>
					<xsl:when test="name() = 'ctor'">
						<xsl:text>(Constructor)</xsl:text>
					</xsl:when>
					<xsl:otherwise>
						<xsl:value-of select="name" />
					</xsl:otherwise>
				</xsl:choose>
				<xsl:text><![CDATA[</td>
		</tr>
		<tr>
			<td class="desc" width="10%">Prototype:</td>
			<td class="data]]></xsl:text>
				<xsl:value-of select="((position() - 1) mod 2) + 1" />
				<xsl:text><![CDATA[">
				<tt>]]></xsl:text>
				<xsl:choose>
					<xsl:when test="name() = 'ctor'">
						<xsl:text>new </xsl:text>
						<xsl:value-of select="../../name" />
					</xsl:when>
					<xsl:otherwise>
						<xsl:choose>
							<xsl:when test="retval">
								<xsl:value-of select="retval/type" />
							</xsl:when>
							<xsl:otherwise>
								<xsl:text>void</xsl:text>
							</xsl:otherwise>
						</xsl:choose>
						<xsl:text> $obj-&gt;</xsl:text>
						<xsl:value-of select="name" />
					</xsl:otherwise>
				</xsl:choose>
				<xsl:text>(</xsl:text>
				<xsl:for-each select="args/arg">
					<xsl:value-of select="type" />
					<xsl:text> $</xsl:text>
					<xsl:value-of select="name" />
					<xsl:if test="position() != last()">
						<xsl:text>, </xsl:text>
					</xsl:if>
				</xsl:for-each>
				<xsl:text>)</xsl:text>
				<xsl:text><![CDATA[
				</tt>
			</td>
		</tr>]]></xsl:text>
				<xsl:if test="count(args/arg)">
					<xsl:text><![CDATA[
		<tr>
			<td class="desc" rowspan="]]></xsl:text>
					<xsl:value-of select="count(args/arg)" />
					<xsl:text><![CDATA[">Arguments:</td>]]></xsl:text>
					<xsl:choose>
						<xsl:when test="(position() - 1) mod 2">
							<xsl:call-template name="t_secondrow" />
						</xsl:when>
						<xsl:otherwise>
							<xsl:call-template name="t_firstrow" />
						</xsl:otherwise>
					</xsl:choose>
					<xsl:text><![CDATA[
		</tr>]]></xsl:text>
				</xsl:if>
				<xsl:text><![CDATA[
		<tr>
			<td class="desc">Description:</td>
			<td class="data]]></xsl:text>
				<xsl:value-of select="((position() - 1) mod 2) + 1" />
				<xsl:text><![CDATA[">]]></xsl:text>
				<xsl:value-of select="desc" />
				<xsl:text><![CDATA[</td>
		</tr>]]></xsl:text>
				<xsl:if test="retval">
					<xsl:text><![CDATA[
		<tr>
			<td class="desc">Returns:</td>
			<td class="data]]></xsl:text>
					<xsl:value-of select="((position() - 1) mod 2) + 1" />
					<xsl:text><![CDATA[">]]></xsl:text>
					<xsl:value-of select="retval/desc" />
					<xsl:text><![CDATA[</td>
		</tr>]]></xsl:text>
				</xsl:if>
			</xsl:for-each>
			<xsl:text><![CDATA[</table>]]></xsl:text>
		</xsl:if>
	</xsl:for-each>
</xsl:template>

</xsl:stylesheet>
