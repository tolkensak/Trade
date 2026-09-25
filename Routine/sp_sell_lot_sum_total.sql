
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_sell_lot_sum_total` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_sell_lot_sum_total`(in lot_id int unsigned)
BEGIN



select ifnull(sum(total), 0) from sell_lot where lid = lot_id;




END $$


DELIMITER ;
