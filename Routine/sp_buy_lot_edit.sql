
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_buy_lot_edit` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_buy_lot_edit`(in buy_id int unsigned)
BEGIN



select w.name
	, b.wid
	, b.amount
	, b.unid
	, b.price
	, b.total
	, b.debt
	, w.ucid
from buy_lot b
	inner join ware w on w.id = b.wid
where b.id = buy_id;




END $$


DELIMITER ;
