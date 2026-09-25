<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet xmlns="http://www.w3.org/1999/xhtml"
				xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
				version="1.0">

	<xsl:include href="report.xsl"/>

	<xsl:template match="question">
		<table class="{name()}">
			<tbody>
				<tr>
					<th><xsl:value-of select="$texts/text[@id='interval']"/>:</th>
					<td><xsl:choose>
							<xsl:when test="moment-from!=''">
								<xsl:call-template name="format-datetime">
									<xsl:with-param name="lang" select="$report-lang"/>
									<xsl:with-param name="datetime" select="moment-from"/>
								</xsl:call-template>
							</xsl:when>
							<xsl:otherwise><xsl:value-of select="$texts/text[@id='begin']"/></xsl:otherwise>
						</xsl:choose>
						<xsl:text xml:space="preserve"> — </xsl:text>
						<xsl:choose>
							<xsl:when test="moment-to!=''">
								<xsl:call-template name="format-datetime">
									<xsl:with-param name="lang" select="$report-lang"/>
									<xsl:with-param name="datetime" select="moment-to"/>
								</xsl:call-template>
							</xsl:when>
							<xsl:otherwise><xsl:value-of select="$texts/text[@id='now']"/></xsl:otherwise>
						</xsl:choose></td>
				</tr>
				<tr>
					<th><xsl:call-template name="param_name">
							<xsl:with-param name="param" select="$params/param[@id=3]"/>
						</xsl:call-template>:</th>
					<td><xsl:choose>
							<xsl:when test="cat!=''"><xsl:value-of select="cat"/></xsl:when>
							<xsl:otherwise><xsl:value-of select="$texts/text[@id='all']"/></xsl:otherwise>
						</xsl:choose></td>
				</tr>
				<tr>
					<th><xsl:call-template name="param_name">
							<xsl:with-param name="param" select="$params/param[@id=4]"/>
						</xsl:call-template>:</th>
					<td><xsl:choose>
							<xsl:when test="firm!=''"><xsl:value-of select="firm"/></xsl:when>
							<xsl:otherwise><xsl:value-of select="$texts/text[@id='all']"/></xsl:otherwise>
						</xsl:choose></td>
				</tr>
				<tr>
					<th><xsl:call-template name="param_name">
							<xsl:with-param name="param" select="$params/param[@id=5]"/>
						</xsl:call-template>:</th>
					<td><xsl:choose>
							<xsl:when test="ware!=''"><xsl:value-of select="ware"/></xsl:when>
							<xsl:otherwise><xsl:value-of select="$texts/text[@id='all']"/></xsl:otherwise>
						</xsl:choose></td>
				</tr>
			</tbody>
		</table>
	</xsl:template>

</xsl:stylesheet>
