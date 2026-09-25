
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_sell_debt_list` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_sell_debt_list`()
BEGIN



select s.debt
	, w.name 'ware'
	, wc.name 'ware_cat'
	, f.name 'firm'
	, s.amount
	, un.name 'unit'
	, s.total
	, s.moment
	, concat_ws(' ', co.first_name, co.last_name) 'operator'
	, s.uid
	, 0 + s.moment
from sell s
	inner join ware w on w.id = s.wid
	inner join ware_cat wc on wc.id = w.wcid
	inner join firm f on f.id = w.fid
	inner join unit un on un.id = s.unid
	inner join `user` u on u.id = s.uid
	inner join contact co on co.id = u.coid
where s.debt is not null
order by s.moment;




END $$


DELIMITER ;
