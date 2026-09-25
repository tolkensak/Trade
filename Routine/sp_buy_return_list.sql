
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_buy_return_list` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_buy_return_list`(in ware_id smallint unsigned, in moment_from datetime, in moment_to datetime)
BEGIN



select w.name 'ware'
	, b.amount
	, un.name 'unit'
	, b.total
	, b.debt
	, b.moment
	, concat_ws(' ', co.first_name, co.last_name) 'operator'
	, b.uid
	, 0 + b.moment
from buy b
	inner join ware w on w.id = b.wid
	inner join unit un on un.id = b.unid
	inner join `user` u on u.id = b.uid
	inner join contact co on co.id = u.coid
where b.wid = ware_id && b.moment between moment_from and moment_to
order by b.moment;




END $$


DELIMITER ;
