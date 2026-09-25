
DELIMITER $$


DROP FUNCTION IF EXISTS `fn_report_format` $$
CREATE DEFINER=`sawda`@`%` FUNCTION  `fn_report_format`(format_name varchar(255)) RETURNS varchar(255) CHARSET utf8
BEGIN



case format_name
	when 'moment' then return '%Y-%m-%d %H:%i:%s';
end case;

return '';




END $$


DELIMITER ;
