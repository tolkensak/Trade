
DELIMITER $$


DROP PROCEDURE IF EXISTS `rp_report_begin` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `rp_report_begin` (
	  in report_id smallint unsigned
	, in lang_id smallint unsigned)
BEGIN



insert into tmp (xml) values
  ('<?xml version="1.0" encoding="utf-8"?>\n')
, (concat('<?xml-stylesheet type="text/xsl" href="report', cast(report_id as char), '.xsl"?>\n'))
, (concat('<report id="', cast(report_id as char), '" lang="', cast(lang_id as char), '">\n'));




END $$


DELIMITER ;
