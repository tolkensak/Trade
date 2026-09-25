
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_sell_lot_present` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_sell_lot_present`(in sell_id int unsigned, in user_id smallint unsigned)
BEGIN



select ifnull(s.lid, 0)
from sell_lot s
where (sell_id != 0 && id = sell_id)
	|| (s.uid = user_id
		&& not exists (select *
                      from indent i
                      where i.submitted is false && i.lid = s.lid));




END $$


DELIMITER ;
