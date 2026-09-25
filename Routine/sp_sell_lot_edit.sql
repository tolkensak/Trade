
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_sell_lot_edit` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_sell_lot_edit`(in sell_id int unsigned)
BEGIN



select w.name
	, s.wid
	, s.amount
	, s.unid
	, s.price
	, s.total
	, s.debt
	, w.ucid
	, w.price
from sell_lot s
	inner join ware w on w.id = s.wid
where s.id = sell_id;




END $$


DELIMITER ;
