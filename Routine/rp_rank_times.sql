
DELIMITER $$


DROP PROCEDURE IF EXISTS `rp_rank_times` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `rp_rank_times`(
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
	, ifnull(( select count(*)
		from sell s
		where s.wid = w.id && s.debt is null && s.moment between v_from and v_to
	), 0) 'times'
	, wc.name 'category'
	, f.name 'firm'
from ware w
	inner join ware_cat wc on wc.id = w.wcid
	inner join firm f on f.id = w.fid
where (cat_id is null ||  w.wcid = cat_id)
	&& (firm_id is null ||  w.fid = firm_id)
	&& (ware_id is null || w.id = ware_id)
order by 3 desc, 2;




END $$


DELIMITER ;