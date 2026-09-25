
DELIMITER $$


DROP FUNCTION IF EXISTS `fn_crypt_key` $$
CREATE DEFINER=`sawda`@`%` FUNCTION `fn_crypt_key`() RETURNS varchar(255) CHARSET utf8
BEGIN



return "Tolken's AES Key";




END $$


DELIMITER ;
