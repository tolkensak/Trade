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
	
	<xsl:variable name="invoice-id" select="invoice/@id"/>
	<xsl:variable name="invoice-lang" select="invoice/@lang"/>
	<xsl:variable name="invoice_texts" select="document('invoice.xml')/texts/lang[@id=$invoice-lang]"/>
	<xsl:variable name="texts" select="document('text.xml')/texts/lang[@id=$invoice-lang]"/>

	<xsl:template match="invoice">
		<html>
			<head>
				<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
				<title><xsl:value-of select="$invoice_texts/text[@id='1']"/><xsl:text xml:space="preserve"> </xsl:text><xsl:value-of select="$invoice-id"/></title>
				<link rel="stylesheet" type="text/css" media="all" href="{@base-url}/report.css"/>
				<link rel="stylesheet" type="text/css" media="all" href="{@base-url}/invoice.css"/>
			</head>
			<body>
				<div class="board">
					<div class="heading1"><xsl:value-of select="$invoice_texts/text[@id='1']"/> 01000<xsl:value-of select="$invoice-id"/></div>
					<table class="info">
						<tbody>
							<tr>
								<th><xsl:value-of select="$invoice_texts/text[@id='2']"/>:</th>
								<td><xsl:value-of select="client"/></td>
							</tr>
							<tr>
								<th><xsl:value-of select="$invoice_texts/text[@id='3']"/>:</th>
								<td><xsl:value-of select="operator"/></td>
							</tr>
							<tr>
								<th><xsl:value-of select="$invoice_texts/text[@id='4']"/>:</th>
								<td><xsl:value-of select="address"/></td>
							</tr>
							<tr>
								<th><xsl:value-of select="$invoice_texts/text[@id='5']"/>:</th>
								<td><xsl:value-of select="$invoice_texts/text[@id='6']"/></td>
							</tr>
							<tr>
								<th><xsl:value-of select="$invoice_texts/text[@id='7']"/>:</th>
								<td>
									<xsl:call-template name="format-date">
										<xsl:with-param name="lang" select="$invoice-lang"/>
										<xsl:with-param name="date" select="deliver"/>
									</xsl:call-template>
								</td>
							</tr>
						</tbody>
					</table>
					<xsl:apply-templates select="sells"/>
					<table class="info">
						<tbody>
							<tr>
								<th><xsl:value-of select="$invoice_texts/text[@id='8']"/>:</th>
								<td><xsl:value-of select="sell_num"/><xsl:text xml:space="preserve"> </xsl:text><xsl:value-of select="$invoice_texts/text[@id='9']"/></td>
							</tr>
							<tr>
								<th><xsl:value-of select="$invoice_texts/text[@id='10']"/>:</th>
								<td><xsl:value-of select="format-number(sell_sum, $fmt-money-long)"/></td>
							</tr>
							<tr>
								<th></th>
								<td class="hand-write">(<xsl:value-of select="sell_sum_text"/>)</td>
							</tr>
						</tbody>
					</table>
					<div class="note"><xsl:value-of select="$invoice_texts/text[@id='11']"/></div>
					<div><xsl:value-of select="$invoice_texts/text[@id='2']"/>:</div>
					<div><xsl:value-of select="$invoice_texts/text[@id='3']"/>:</div>
				</div>
			</body>
		</html>
	</xsl:template>


	<xsl:template match="sells">
		<table class="{name()}">
			<thead>
				<tr>
					<th></th>
					<th><xsl:value-of select="$texts/text[@id='ware']"/></th>
					<th><xsl:value-of select="$texts/text[@id='price']"/></th>
					<th><xsl:value-of select="$texts/text[@id='amount']"/></th>
					<th><xsl:value-of select="$texts/text[@id='unit']"/></th>
					<th><xsl:value-of select="$texts/text[@id='total']"/></th>
				</tr>
			</thead>
			<tbody>
				<xsl:apply-templates select="sell"/>
			</tbody>
		</table>
	</xsl:template>


	<xsl:template match="sell">
		<tr>
			<td class="ndx"><xsl:value-of select="position()"/></td>
			<td class="txt"><xsl:value-of select="ware"/></td>
			<td class="mny"><xsl:value-of select="format-number(price, $fmt-money)"/>/<xsl:value-of select="main_unit"/></td>
			<td class="flt"><xsl:value-of select="amount"/></td>
			<td class="sym"><xsl:value-of select="unit"/></td>
			<td class="mny"><xsl:value-of select="format-number(total, $fmt-money)"/></td>
		</tr>
	</xsl:template>

</xsl:stylesheet>
