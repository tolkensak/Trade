
DELIMITER $$


DROP PROCEDURE IF EXISTS `rp_report_form1` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `rp_report_form1` (
	  in moment_from datetime
	, in moment_to datetime
	, in cat_id smallint unsigned
	, in firm_id smallint unsigned
	, in report_id smallint unsigned
	, in lang_id smallint unsigned)
BEGIN


declare moment_format varchar(255) default fn_report_format('moment');


drop temporary table if exists tmp;

create temporary table tmp (
  id smallint(5) unsigned not null auto_increment,
  xml text not null,
  primary key (`id`)
) engine=innodb auto_increment=1 default charset=utf8;


call rp_report_begin(report_id, lang_id);


insert into tmp (xml) values
  ('\t<question>\n')
, (concat('\t\t<moment-from>', if(moment_from, date_format(moment_from, moment_format), ''), '</moment-from>\n'))
, (concat('\t\t<moment-to>', if(moment_to, date_format(moment_to, moment_format), ''), '</moment-to>\n'))
, (concat('\t\t<cat>', if(cat_id, (select name from ware_cat where id = cat_id), ''), '</cat>\n'))
, (concat('\t\t<firm>', if(firm_id, (select name from firm where id = firm_id), ''), '</firm>\n'))
, ('\t</question>\n')
;

insert into tmp (xml) values ('\t<answer>\n');

set @mf = moment_from;
set @mt = moment_to;
set @ci = cat_id;
set @fi = firm_id;
set @sql = concat('call rp_', cast(report_id as char), '(@mf, @mt, @ci, @fi)');
prepare stmt from @sql;
execute stmt;
deallocate prepare stmt;


insert into tmp (xml) values ('\t</answer>\n');

call rp_report_end();



select xml from tmp order by id;






END $$


DELIMITER ;
