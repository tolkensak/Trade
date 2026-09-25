
DELIMITER $$


DROP PROCEDURE IF EXISTS `rp_remain!!!`$$
CREATE DEFINER=`sawda`@`%` PROCEDURE `rp_remain!!!`(in moment_from datetime, in moment_to datetime)
BEGIN



if moment_from is null then
	set moment_from = '1000-01-01 00:00:00';
end if;

if moment_to is null then
	set moment_to = '9999-12-31 23:59:59';
end if;


select w.id
	, w.name 'ware'
	, sum(b.amount * unb.ratio) 'bought'
	, sum(s.amount * uns.ratio) 'sold'
	, sum(b.amount * unb.ratio) - sum(s.amount * uns.ratio) 'remain'
	, un.name 'unit'
	, wc.name 'category'
	, f.name 'firm'
from ware w
	left join (buy b inner join unit unb on unb.id = b.unid)
		on b.wid = w.id && b.debt is null && b.moment between moment_from and moment_to
	left join (sell s inner join unit uns on uns.id = s.unid)
		on s.wid = w.id && s.debt is null && s.moment between moment_from and moment_to
	inner join unit un on un.ucid = w.ucid && un.main is true
	inner join ware_cat wc on wc.id = w.wcid
	inner join firm f on f.id = w.fid
group by w.id
order by 5, 2;




END $$


DELIMITER ;