
DELIMITER $$

DROP TRIGGER IF EXISTS `tr_indent_bi` $$
CREATE DEFINER=`sawda`@`%` TRIGGER `tr_indent_bi`
BEFORE INSERT ON indent FOR EACH ROW
BEGIN



set new.lid = fn_new_sell_lot();




END $$

DELIMITER ;
