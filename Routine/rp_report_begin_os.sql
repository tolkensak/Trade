
DELIMITER $$


DROP PROCEDURE IF EXISTS `rp_report_begin` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `rp_report_begin` (
	  in report_id smallint unsigned
	, in lang_id smallint unsigned
	, base_url varchar(255)
	, inout xml longtext)
BEGIN



set xml = concat(xml
, '<?xml version="1.0" encoding="utf-8"?>\n'
, '<?xml-stylesheet type="text/xsl" href="', base_url, '/report', cast(report_id as char), '.xsl"?>\n'
, '<report id="', cast(report_id as char), '" lang="', cast(lang_id as char), '" base-url="', base_url, '">\n'
);




END $$


DELIMITER ;
