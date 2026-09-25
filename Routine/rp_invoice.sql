
DELIMITER $$


DROP PROCEDURE IF EXISTS `rp_invoice` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `rp_invoice`(
	  in lot_id int unsigned
	, in lang_id smallint unsigned
	, base_url varchar(255))
BEGIN



declare moment_format varchar(255) default fn_report_format('moment');

declare v_id varchar(255);
declare v_client varchar(255);
declare v_address varchar(255);
declare v_deliver date;
declare v_operator varchar(255);

declare v_ware varchar(255);
declare v_price decimal(17,2);
declare v_main_unit varchar(255);
declare v_amount double;
declare v_unit varchar(255);
declare v_total decimal(17,2);

declare v_sell_num int unsigned default 0;
declare v_sell_sum decimal(17,2) default 0;
declare v_sells mediumtext default '';


declare done int default 0;
declare cur cursor for
	select w.name, s.price, unm.name, s.amount, un.name, s.total
	from sell_lot s
	  inner join ware w on w.id = s.wid
	  inner join unit unm on unm.ucid = w.ucid && unm.main is true
	  inner join unit un on un.id = s.unid
	where s.lid = lot_id;
declare continue handler for not found set done = 1;

open cur;

repeat
	fetch cur into v_ware, v_price, v_main_unit, v_amount, v_unit, v_total;
	if not done then
		set v_sell_num = v_sell_num + 1;
		set v_sell_sum = v_sell_sum + v_total;
		set v_sells = concat(v_sells
					, '\t\t<sell>\n'
					, '\t\t\t<order>', cast(v_sell_num as char), '</order>\n'
					, '\t\t\t<ware>', v_ware, '</ware>\n'
					, '\t\t\t<price>', cast(v_price as char), '</price>\n'
					, '\t\t\t<main_unit>', v_main_unit, '</main_unit>\n'
					, '\t\t\t<amount>', cast(v_amount as char), '</amount>\n'
					, '\t\t\t<unit>', v_unit, '</unit>\n'
					, '\t\t\t<total>', cast(v_total as char), '</total>\n'
					, '\t\t</sell>\n');
	end if;
until done end repeat;

close cur;


select i.id, c.name, coc.address, i.deliver, concat_ws(' ', cou.first_name, cou.last_name)
into v_id, v_client, v_address, v_deliver, v_operator
from indent i
	inner join `client` c on c.id = i.cid
	inner join `user` u on u.id = i.uid
	inner join contact coc on coc.id = c.coid
	inner join contact cou on cou.id = u.coid
where i.lid = lot_id;



select concat(
  '<?xml version="1.0" encoding="utf-8"?>\n'
, '<?xml-stylesheet type="text/xsl" href="', base_url, '/invoice.xsl"?>\n'
, '<invoice id="', cast(v_id as char), '" lang="', cast(lang_id as char), '" base-url="', base_url, '">\n'
, '\t<client>', v_client, '</client>\n'
, '\t<address>', v_address, '</address>\n'
, '\t<deliver>', date_format(v_deliver, moment_format), '</deliver>\n'
, '\t<operator>', v_operator, '</operator>\n'
, '\t<sells>\n', v_sells, '\t</sells>\n'
, '\t<sell_num>', cast(v_sell_num as char), '</sell_num>\n'
, '\t<sell_sum>', cast(v_sell_sum as char), '</sell_sum>\n'
, '\t<sell_sum_text>', fn_mtos(v_sell_sum), '</sell_sum_text>\n'
, '</invoice>\n'
) 'xml';






END $$


DELIMITER ;