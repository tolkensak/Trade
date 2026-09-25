
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_sell_return_list` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_sell_return_list`(in ware_id smallint unsigned, in moment_from datetime, in moment_to datetime)
BEGIN



select w.name 'ware'
	, s.amount
	, un.name 'unit'
	, s.total
	, s.debt
	, s.moment
	, concat_ws(' ', co.first_name, co.last_name) 'operator'
	, s.uid
	, 0 + s.moment
from sell s
	inner join ware w on w.id = s.wid
	inner join unit un on un.id = s.unid
	inner join `user` u on u.id = s.uid
	inner join contact co on co.id = u.coid
where s.wid = ware_id && s.moment between moment_from and moment_to
order by s.moment;




END $$


DELIMITER ;
