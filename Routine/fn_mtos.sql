
DELIMITER $$


DROP FUNCTION IF EXISTS `fn_mtos` $$
CREATE DEFINER=`sawda`@`%` FUNCTION `fn_mtos`(mon decimal(17,2)) RETURNS varchar(255) CHARSET utf8
BEGIN



declare int_part bigint unsigned;

if mon is null then
	return '(null)';
end if;

if mon = 0 then
	return 'нөл теңге нөл тиын';
end if;


set int_part = floor(mon);

return concat(fn_ntos(int_part), ' теңге ', fn_ntos((mon - int_part) * 100), ' тиын');




END $$


DELIMITER ;