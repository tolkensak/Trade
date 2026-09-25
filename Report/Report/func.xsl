<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

	<!--<xsl:variable name="fmt-float" select="'###,###'"/>-->
	<xsl:variable name="fmt-money" select="'###,###.00Ŧ'"/>
	<xsl:variable name="fmt-money-long" select="'###,###.00 теңге'"/>
	
	<xsl:template name="format-date">
		<xsl:param name="lang"/>
		<xsl:param name="date"/>
		<xsl:choose>
			<xsl:when test="$lang=1087">
				<xsl:value-of select="concat(substring($date, 1, 4), '.', substring($date, 6, 2), '.', substring($date, 9, 2))"/>
			</xsl:when>
			<xsl:when test="$lang=1049">
				<xsl:value-of select="concat(substring($date, 9, 2), '.', substring($date, 6, 2), '.', substring($date, 1, 4))"/>
			</xsl:when>
			<xsl:when test="$lang=1033">
				<xsl:value-of select="concat(substring($date, 6, 2), '/', substring($date, 9, 2), '/', substring($date, 1, 4))"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="$date"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template name="format-time">
		<xsl:param name="lang"/>
		<xsl:param name="time"/>
		<xsl:value-of select="$time"/>
	</xsl:template>

	<xsl:template name="format-time-part">
		<xsl:param name="lang"/>
		<xsl:param name="time"/>
		<xsl:call-template name="format-time">
			<xsl:with-param name="lang" select="$lang"/>
			<xsl:with-param name="time" select="substring($time, 12, 8)"/>
		</xsl:call-template>
	</xsl:template>

	<xsl:template name="format-datetime">
		<xsl:param name="lang"/>
		<xsl:param name="datetime"/>
		<xsl:call-template name="format-date">
			<xsl:with-param name="lang" select="$lang"/>
			<xsl:with-param name="date" select="$datetime"/>
		</xsl:call-template>
		<xsl:text xml:space="preserve"> </xsl:text>
		<xsl:call-template name="format-time">
			<xsl:with-param name="lang" select="$lang"/>
			<xsl:with-param name="time" select="substring($datetime, 12, 8)"/>
		</xsl:call-template>
	</xsl:template>

	<xsl:template name="param_name">
		<xsl:param name="param"/>
		<xsl:value-of select="substring-before($param, '&amp;')"/>
		<xsl:value-of select="substring-after($param, '&amp;')"/>
	</xsl:template>

</xsl:stylesheet>
