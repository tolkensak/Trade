
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_sell_price` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_sell_price`(in ware_id smallint unsigned)
BEGIN



select w.price
from ware w
where w.id = ware_id;




END $$


DELIMITER ;
