
DELIMITER $$


DROP FUNCTION IF EXISTS `fn_crypt_enc` $$
CREATE DEFINER=`sawda`@`%` FUNCTION `fn_crypt_enc`(txt VARCHAR(255)) RETURNS varbinary(255)
BEGIN



return aes_encrypt(txt, fn_crypt_key());




END $$


DELIMITER ;
