
DELIMITER $$


DROP FUNCTION IF EXISTS `fn_ntos_p1` $$
CREATE DEFINER=`sawda`@`%` FUNCTION `fn_ntos_p1`(num char(1)) RETURNS varchar(10) CHARSET utf8
BEGIN



case num
	#when '0' then return 'нөл';
	when '1' then return 'бір';
	when '2' then return 'екі';
	when '3' then return 'үш';
	when '4' then return 'төрт';
	when '5' then return 'бес';
	when '6' then return 'алты';
	when '7' then return 'жеті';
	when '8' then return 'сегіз';
	when '9' then return 'тоғыз';
	else return '';
end case;




END $$


DELIMITER ;
