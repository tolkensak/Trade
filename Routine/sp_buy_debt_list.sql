
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_buy_debt_list` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_buy_debt_list`()
BEGIN



select b.debt
	, w.name 'ware'
	, wc.name 'ware_cat'
	, f.name 'firm'
	, b.amount
	, un.name 'unit'
	, b.total
	, b.moment
	, concat_ws(' ', co.first_name, co.last_name) 'operator'
	, b.uid
	, 0 + b.moment
from buy b
	inner join ware w on w.id = b.wid
	inner join ware_cat wc on wc.id = w.wcid
	inner join firm f on f.id = w.fid
	inner join unit un on un.id = b.unid
	inner join `user` u on u.id = b.uid
	inner join contact co on co.id = u.coid
where b.debt is not null
order by b.moment;




END $$


DELIMITER ;
