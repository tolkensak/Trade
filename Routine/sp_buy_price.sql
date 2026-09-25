
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_buy_price` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_buy_price`(in ware_id smallint unsigned)
BEGIN



select p1.spend
from price p1
	left join price p2 on p2.wid = p1.wid && p2.moment > p1.moment
where p2.wid is null && p1.wid = ware_id;




END $$


DELIMITER ;
