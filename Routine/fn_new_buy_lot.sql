
DELIMITER $$


DROP FUNCTION IF EXISTS `fn_new_buy_lot` $$
CREATE DEFINER=`sawda`@`%` FUNCTION `fn_new_buy_lot`() RETURNS int(10) unsigned
BEGIN



insert into lot_buy(id) values(default);
return last_insert_id();




END $$


DELIMITER ;
