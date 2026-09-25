
DELIMITER $$


DROP FUNCTION IF EXISTS `fn_crypt_dec` $$
CREATE DEFINER=`sawda`@`%` FUNCTION `fn_crypt_dec`(pwd VARBINARY(255)) RETURNS varchar(255) CHARSET utf8
BEGIN



return aes_decrypt(pwd, fn_crypt_key());




END $$


DELIMITER ;
