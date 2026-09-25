
DELIMITER $$


DROP FUNCTION IF EXISTS `fn_new_sell_lot` $$
CREATE DEFINER=`sawda`@`%` FUNCTION `fn_new_sell_lot`() RETURNS int(10) unsigned
BEGIN



insert into lot_sell(id) values(default);
return last_insert_id();




END $$


DELIMITER ;
