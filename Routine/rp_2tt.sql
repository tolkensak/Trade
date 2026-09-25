
DELIMITER $$


DROP PROCEDURE IF EXISTS `rp_2` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `rp_2`(
	  in moment_from datetime
	, in moment_to datetime
	, in cat_id smallint unsigned
	, in firm_id smallint unsigned)
BEGIN


declare moment_format varchar(255) default fn_report_format('moment');
declare v_from datetime default ifnull(moment_from, '1000-01-01 00:00:00');
declare v_to datetime default ifnull(moment_to, '9999-12-31 23:59:59');


insert into tmp (xml)
select concat('\t\t<i>\n'
	, '\t\t\t<lid>', cast(s.lid as char), '</lid>\n'
	, '\t\t\t<wid>', cast(s.wid as char), '</wid>\n'
	, '\t\t\t<ware>', w.name, '</ware>\n'
	, '\t\t\t<amount>', cast(s.amount as char), '</amount>\n'
	, '\t\t\t<unit>', un.name, '</unit>\n'
	, '\t\t\t<sold-price>', ifnull(cast(s.price as char), ''), '</sold-price>\n'
	, '\t\t\t<price>', cast(fn_ware_price(s.wid, s.moment) as char), '</price>\n'
	, '\t\t\t<main-unit>', unm.name, '</main-unit>\n'
	, '\t\t\t<spend>', cast(fn_ware_spend(s.wid, s.moment) as char), '</spend>\n'
	, '\t\t\t<total>', cast(s.total as char), '</total>\n'
	, '\t\t\t<moment>', date_format(s.moment, moment_format), '</moment>\n'
	, '\t\t\t<operator>', concat_ws(' ', co.first_name, co.last_name), '</operator>\n'
	, '\t\t</i>\n')
from sell s
	inner join ware w on w.id = s.wid
		&& (cat_id is null ||  w.wcid = cat_id)
		&& (firm_id is null ||  w.fid = firm_id)
	inner join unit un on un.id = s.unid
	inner join unit unm on unm.ucid = w.ucid && unm.main is true
	inner join `user` u on u.id = s.uid
	inner join contact co on co.id = u.coid
where s.debt is null && s.moment between v_from and v_to
order by s.lid, s.moment;




END $$
