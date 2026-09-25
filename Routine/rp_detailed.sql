
DELIMITER $$


DROP PROCEDURE IF EXISTS `rp_detailed` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `rp_detailed`(
	in moment_from datetime
	, in moment_to datetime
	, in cat_id smallint unsigned
	, in firm_id smallint unsigned
	, in ware_id smallint unsigned)
BEGIN



declare v_from datetime default ifnull(moment_from, '1000-01-01 00:00:00');
declare v_to datetime default ifnull(moment_to, '9999-12-31 23:59:59');

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




END $$


DELIMITER ;
