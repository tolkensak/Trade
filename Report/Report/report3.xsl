<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet xmlns="http://www.w3.org/1999/xhtml"
				xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
				version="1.0">

	<xsl:include href="form1.xsl"/>

	<xsl:template match="answer">
		<table class="{name()}">
			<thead>
				<tr>
					<th></th>
					<th><xsl:value-of select="$texts/text[@id='id']"/></th>
					<th><xsl:value-of select="$texts/text[@id='ware']"/></th>
					<th><xsl:value-of select="$texts/text[@id='bought']"/></th>
					<th><xsl:value-of select="$texts/text[@id='sold']"/></th>
					<th><xsl:value-of select="$texts/text[@id='remain']"/></th>
					<th><xsl:value-of select="$texts/text[@id='unit']"/></th>
					<th><xsl:value-of select="$texts/text[@id='cat']"/></th>
					<th><xsl:value-of select="$texts/text[@id='firm']"/></th>
				</tr>
			</thead>
			<tbody>
				<xsl:apply-templates select="i"/>
			</tbody>
		</table>
	</xsl:template>

	<xsl:template match="i">
		<tr class="{position() mod 2 = 0}">
			<td class="ndx"><xsl:value-of select="position()"/></td>
			<td class="int"><xsl:value-of select="wid"/></td>
			<td class="txt"><xsl:value-of select="ware"/></td>
			<td class="flt"><xsl:value-of select="bought"/></td>
			<td class="flt"><xsl:value-of select="sold"/></td>
			<td class="flt"><xsl:value-of select="remain"/></td>
			<td class="sym"><xsl:value-of select="unit"/></td>
			<td class="txt"><xsl:value-of select="cat"/></td>
			<td class="txt"><xsl:value-of select="firm"/></td>
		</tr>
	</xsl:template>

</xsl:stylesheet>
