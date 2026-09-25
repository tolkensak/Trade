
DELIMITER $$

DROP TRIGGER IF EXISTS `tr_sell_lot_bi` $$
CREATE DEFINER=`sawda`@`%` TRIGGER `tr_sell_lot_bi`
BEFORE INSERT ON sell_lot FOR EACH ROW
BEGIN



if new.lid = 0 then
	set new.lid = fn_new_sell_lot();
end if;




END $$

DELIMITER ;
