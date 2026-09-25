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
					<th><xsl:value-of select="$texts/text[@id='sell_id']"/></th>
					<th><xsl:value-of select="$texts/text[@id='ware_id']"/></th>
					<th><xsl:value-of select="$texts/text[@id='ware']"/></th>
					<th><xsl:value-of select="$texts/text[@id='amount']"/></th>
					<th><xsl:value-of select="$texts/text[@id='unit']"/></th>
					<th><xsl:value-of select="$texts/text[@id='sold_price']"/></th>
					<th><xsl:value-of select="$texts/text[@id='price']"/></th>
					<th><xsl:value-of select="$texts/text[@id='spend']"/></th>
					<th><xsl:value-of select="$texts/text[@id='total']"/></th>
					<th><xsl:value-of select="$texts/text[@id='moment']"/></th>
					<th><xsl:value-of select="$texts/text[@id='operator']"/></th>
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
			<td class="int"><xsl:value-of select="lid"/></td>
			<td class="int"><xsl:value-of select="wid"/></td>
			<td class="txt"><xsl:value-of select="ware"/></td>
			<td class="flt"><xsl:value-of select="amount"/></td>
			<td class="sym"><xsl:value-of select="unit"/></td>
			<td class="mny"><xsl:if test="sold-price!=''">
					<xsl:value-of select="format-number(sold-price, $fmt-money)"/>/<xsl:value-of select="main-unit"/>
				</xsl:if></td>
			<td class="mny"><xsl:value-of select="format-number(price, $fmt-money)"/>/<xsl:value-of select="main-unit"/></td>
			<td class="mny"><xsl:value-of select="format-number(spend, $fmt-money)"/></td>
			<td class="mny"><xsl:value-of select="format-number(total, $fmt-money)"/></td>
			<td class="dtm"><xsl:call-template name="format-datetime">
					<xsl:with-param name="lang" select="$report-lang"/>
					<xsl:with-param name="datetime" select="moment"/>
				</xsl:call-template></td>
			<td class="txt"><xsl:value-of select="operator"/></td>
		</tr>
	</xsl:template>

</xsl:stylesheet>
