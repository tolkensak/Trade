
DELIMITER $$


DROP FUNCTION IF EXISTS `fn_new_contact` $$
CREATE DEFINER=`sawda`@`%` FUNCTION `fn_new_contact`() RETURNS smallint(10) unsigned
BEGIN



insert into contact(system) values(true);
return last_insert_id();




END $$


DELIMITER ;
