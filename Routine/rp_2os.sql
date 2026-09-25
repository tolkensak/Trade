
DELIMITER $$


DROP PROCEDURE IF EXISTS `rp_2` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `rp_2`(
	  in moment_from datetime
	, in moment_to datetime
	, in cat_id smallint unsigned
	, in firm_id smallint unsigned
	, in ware_id smallint unsigned
	, inout xml longtext)
BEGIN


declare moment_format varchar(255) default fn_report_format('moment');
declare v_from datetime default ifnull(moment_from, '1000-01-01 00:00:00');
declare v_to datetime default ifnull(moment_to, '9999-12-31 23:59:59');


declare v_lid int unsigned;
declare v_wid smallint unsigned;
declare v_ware varchar(255);
declare v_amount double;
declare v_unit varchar(255);
declare v_sold_price decimal(17,2);
declare v_price decimal(17,2);
declare v_main_unit varchar(255);
declare v_spend decimal(17,2);
declare v_total decimal(17,2);
declare v_moment datetime;
declare v_operator varchar(255);

declare done int default 0;
declare cur cursor for
	select s.lid
		, s.wid
		, w.name 'ware'
		, s.amount
		, un.name 'unit'
		, s.price 'sold_price'
		, fn_ware_price(s.wid, s.moment) 'price'
		, unm.name 'main_unit'
		, fn_ware_spend(s.wid, s.moment) 'spend'
		, s.total
		, s.moment
		, concat_ws(' ', co.first_name, co.last_name) 'operator'
	from sell s
		inner join ware w on w.id = s.wid
			&& (cat_id is null ||  w.wcid = cat_id)
			&& (firm_id is null ||  w.fid = firm_id)
			&& (ware_id is null || w.id = ware_id)
		inner join unit un on un.id = s.unid
		inner join unit unm on unm.ucid = w.ucid && unm.main is true
		inner join `user` u on u.id = s.uid
		inner join contact co on co.id = u.coid
	where s.debt is null
		&& s.moment between v_from and v_to
	order by s.lid, s.moment;
declare continue handler for not found set done = 1;



open cur;

repeat
	fetch cur into v_lid, v_wid, v_ware, v_amount, v_unit, v_sold_price, v_price, v_main_unit, v_spend, v_total, v_moment, v_operator;
	if not done then
		set xml = concat(xml
					, '\t\t<i>\n'
					, '\t\t\t<lid>', v_lid, '</lid>\n'
					, '\t\t\t<wid>', v_wid, '</wid>\n'
					, '\t\t\t<ware>', v_ware, '</ware>\n'
					, '\t\t\t<amount>', v_amount, '</amount>\n'
					, '\t\t\t<unit>', v_unit, '</unit>\n'
					, '\t\t\t<sold-price>', ifnull(v_sold_price, ''), '</sold-price>\n'
					, '\t\t\t<price>', v_price, '</price>\n'
					, '\t\t\t<main-unit>', v_main_unit, '</main-unit>\n'
					, '\t\t\t<spend>', v_spend, '</spend>\n'
					, '\t\t\t<total>', v_total, '</total>\n'
					, '\t\t\t<moment>', date_format(v_moment, moment_format), '</moment>\n'
					, '\t\t\t<operator>', v_operator, '</operator>\n'
					, '\t\t</i>\n');
	end if;
until done end repeat;

close cur;





END $$


DELIMITER ;