
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_buy_lot_sum_total` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_buy_lot_sum_total`(in lot_id int unsigned)
BEGIN



select ifnull(sum(total), 0) from buy_lot where lid = lot_id;




END $$


DELIMITER ;
