
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_buy_lot_present` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_buy_lot_present`(in buy_id int unsigned, in user_id smallint unsigned)
BEGIN



select ifnull(lid, 0)
from buy_lot
where (buy_id != 0 && id = buy_id) || uid = user_id;




END $$


DELIMITER ;
