
DELIMITER $$


DROP PROCEDURE IF EXISTS `rp_report_form1` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `rp_report_form1` (
	  in moment_from datetime
	, in moment_to datetime
	, in cat_id smallint unsigned
	, in firm_id smallint unsigned
	, in ware_id smallint unsigned
	, in report_id smallint unsigned
	, in lang_id smallint unsigned
	, base_url varchar(255))
BEGIN


declare moment_format varchar(255) default fn_report_format('moment');


set @xml = '';

call rp_report_begin(report_id, lang_id, base_url, @xml);

set @xml = concat(@xml
, '\t<question>\n'
, '\t\t<moment-from>', if(moment_from, date_format(moment_from, moment_format), ''), '</moment-from>\n'
, '\t\t<moment-to>', if(moment_to, date_format(moment_to, moment_format), ''), '</moment-to>\n'
, '\t\t<cat>', if(cat_id, (select name from ware_cat where id = cat_id), ''), '</cat>\n'
, '\t\t<firm>', if(firm_id, (select name from firm where id = firm_id), ''), '</firm>\n'
, '\t\t<ware>', if(ware_id, (select name from ware where id = ware_id), ''), '</ware>\n'
, '\t</question>\n'
, '\t<answer>\n');


set @mf = moment_from;
set @mt = moment_to;
set @ci = cat_id;
set @fi = firm_id;
set @wi = ware_id;
set @sql = concat('call rp_', cast(report_id as char), '(@mf, @mt, @ci, @fi, @wi, @xml)');
prepare stmt from @sql;
execute stmt;
deallocate prepare stmt;



set @xml = concat(@xml, '\t</answer>\n');

call rp_report_end(@xml);


select @xml;




END $$


DELIMITER ;
