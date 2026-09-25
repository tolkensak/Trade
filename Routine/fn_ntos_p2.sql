
DELIMITER $$


DROP FUNCTION IF EXISTS `fn_ntos_p2` $$
CREATE DEFINER=`sawda`@`%` FUNCTION `fn_ntos_p2`(num char(1)) RETURNS varchar(10) CHARSET utf8
BEGIN



case num
	when '1' then return 'он';
	when '2' then return 'жирма';
	when '3' then return 'отыз';
	when '4' then return 'қырық';
	when '5' then return 'елу';
	when '6' then return 'алпыс';
	when '7' then return 'жетпіс';
	when '8' then return 'сексен';
	when '9' then return 'тоқсан';
	else return '';
end case;




END $$


DELIMITER ;
