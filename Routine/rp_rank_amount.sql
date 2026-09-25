
DELIMITER $$


DROP PROCEDURE IF EXISTS `rp_rank_amount` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `rp_rank_amount`(
	in moment_from datetime
	, in moment_to datetime
	, in cat_id smallint unsigned
	, in firm_id smallint unsigned
	, in ware_id smallint unsigned)
BEGIN



declare v_from datetime default ifnull(moment_from, '1000-01-01 00:00:00');
declare v_to datetime default ifnull(moment_to, '9999-12-31 23:59:59');

select w.id
	, w.name 'ware'
	, ifnull((
		select sum(s.amount * uns.ratio)
		from sell s
			inner join unit uns on uns.id = s.unid
		where s.wid = w.id && s.debt is null && s.moment between v_from and v_to
	), 0) 'amount'
	, un.name 'unit'
	, wc.name 'category'
	, f.name 'firm'
from ware w
	inner join unit un on un.ucid = w.ucid && un.main is true
	inner join ware_cat wc on wc.id = w.wcid
	inner join firm f on f.id = w.fid
where (cat_id is null ||  w.wcid = cat_id)
	&& (firm_id is null ||  w.fid = firm_id)
	&& (ware_id is null || w.id = ware_id)
order by 3 desc, 2;




END $$


DELIMITER ;