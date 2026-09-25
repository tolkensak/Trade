<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet xmlns="http://www.w3.org/1999/xhtml"
				xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
				version="1.0">

	<xsl:include href="form1.xsl"/>

	<xsl:template match="answer">
		<table class="{name()}">
			<tbody>
				<tr>
					<th><xsl:value-of select="$texts/text[@id='sell_num']"/>:</th>
					<td><xsl:value-of select="sell_num"/></td>
				</tr>
				<tr>
					<th><xsl:value-of select="$texts/text[@id='ware_num']"/>:</th>
					<td><xsl:value-of select="ware_num"/></td>
				</tr>
				<tr>
					<th><xsl:value-of select="$texts/text[@id='total']"/>:</th>
					<td><xsl:value-of select="format-number(total, $fmt-money)"/></td>
				</tr>
				<tr>
					<th><xsl:value-of select="$texts/text[@id='spend']"/>:</th>
					<td><xsl:value-of select="format-number(spend, $fmt-money)"/></td>
				</tr>
				<tr>
					<th><xsl:value-of select="$texts/text[@id='append']"/>:</th>
					<td><xsl:value-of select="format-number(append, $fmt-money)"/></td>
				</tr>
			</tbody>
		</table>
	</xsl:template>

</xsl:stylesheet>
