<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet xmlns="http://www.w3.org/1999/xhtml"
				xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
				version="1.0">

	<xsl:import href="func.xsl"/>

	<xsl:output method="html"
				doctype-public="-//W3C//DTD XHTML 1.0 Transitional//EN"
				doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd"
				media-type="text/html"
				encoding="utf-8"
				version="1.0"/>

	<xsl:variable name="report-id" select="report/@id"/>
	<xsl:variable name="report-lang" select="report/@lang"/>
	<xsl:variable name="report-name" select="document('report.xml')/reports/lang[@id=$report-lang]/report[@id=$report-id]"/>
	<xsl:variable name="params" select="document('param.xml')/params/lang[@id=$report-lang]"/>
	<xsl:variable name="texts" select="document('text.xml')/texts/lang[@id=$report-lang]"/>

	<xsl:template match="report">
		<html>
			<head>
				<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
				<title>Sawda - <xsl:value-of select="$report-name"/></title>
				<link rel="stylesheet" type="text/css" media="all" href="{@base-url}/report.css"/>
				<link rel="stylesheet" type="text/css" media="all" href="{@base-url}/report{$report-id}.css"/>
			</head>
			<body>
				<div class="board">
					<div class="heading1"><xsl:value-of select="$report-name"/></div>
					<div class="heading2"><xsl:value-of select="$texts/text[@id='question']"/></div>
					<xsl:apply-templates select="question"/>
					<div class="heading2"><xsl:value-of select="$texts/text[@id='answer']"/></div>
					<xsl:apply-templates select="answer"/>
				</div>
			</body>
		</html>
	</xsl:template>

</xsl:stylesheet>
