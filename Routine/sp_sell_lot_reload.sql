
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_sell_lot_reload` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_sell_lot_reload`(in ware_id smallint unsigned)
BEGIN



select w.name
	, w.price
	, w.ucid
from ware w
where w.id = ware_id;




END $$


DELIMITER ;
