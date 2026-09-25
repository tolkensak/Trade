
DELIMITER $$


DROP PROCEDURE IF EXISTS `rp_summary` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `rp_summary`(
	in moment_from datetime
	, in moment_to datetime
	, in cat_id smallint unsigned
	, in firm_id smallint unsigned
	, in ware_id smallint unsigned)
BEGIN



declare v_from datetime default ifnull(moment_from, '1000-01-01 00:00:00');
declare v_to datetime default ifnull(moment_to, '9999-12-31 23:59:59');

declare v_sell_num int unsigned;
declare v_ware_num int unsigned;
declare v_total decimal(17,2);
declare v_spend decimal(17,2);


select count(distinct s.lid)
	, count(*)
	, ifnull(sum(total), 0)
	, ifnull(sum((select fn_ware_spend(s.wid, s.moment) * s.amount * un.ratio)), 0)
into v_sell_num, v_ware_num, v_total, v_spend
from sell s
	inner join unit un on un.id = s.unid
	inner join ware w on w.id = s.wid
		&& (cat_id is null ||  w.wcid = cat_id)
		&& (firm_id is null ||  w.fid = firm_id)
		&& (ware_id is null || w.id = ware_id)
where s.debt is null
	&& s.moment between v_from and v_to;


select v_sell_num 'sell_num'
	, v_ware_num 'ware_num'
	, v_total 'total'
	, v_spend 'spend'
	, v_total - v_spend 'append';




END $$


DELIMITER ;