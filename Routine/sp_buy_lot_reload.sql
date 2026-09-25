
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_buy_lot_reload` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_buy_lot_reload`(in ware_id smallint unsigned)
BEGIN



select w.name
	, ifnull(p1.spend, 0)
	, w.ucid
from ware w
	left join price p1 on p1.wid = w.id
	left join price p2 on p2.wid = p1.wid && p2.moment > p1.moment
where p2.wid is null && w.id = ware_id;




END $$


DELIMITER ;
