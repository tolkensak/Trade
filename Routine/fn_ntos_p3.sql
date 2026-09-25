
DELIMITER $$


DROP FUNCTION IF EXISTS `fn_ntos_p3` $$
CREATE DEFINER=`sawda`@`%` FUNCTION `fn_ntos_p3`(num char(1)) RETURNS varchar(20) CHARSET utf8
BEGIN



declare ret varchar(20) default fn_ntos_p1(num);

if ret != '' then
	set ret = concat(ret, ' жүз');
end if;

return ret;




END $$


DELIMITER ;
