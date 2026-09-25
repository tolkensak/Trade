
DELIMITER $$

DROP TRIGGER IF EXISTS `tr_buy_lot_bi` $$
CREATE DEFINER=`sawda`@`%` TRIGGER `tr_buy_lot_bi`
BEFORE INSERT ON buy_lot FOR EACH ROW
BEGIN



if new.lid = 0 then
	set new.lid = fn_new_buy_lot();
end if;




END $$

DELIMITER ;
