
DELIMITER $$


DROP FUNCTION IF EXISTS `fn__permit_name`$$
CREATE DEFINER=`sawda`@`%` FUNCTION  `fn__permit_name`(permit_flags int unsigned) RETURNS varchar(1020) CHARSET utf8
BEGIN



declare permit_names varchar(1020) default '';

declare permit_flag int unsigned;
declare permit_name varchar(1020);

declare done int default 0;
declare cur cursor for select flag, name from permit;
declare continue handler for not found set done = 1;

if permit_flags is null then
	return null;
end if;

if permit_flags = 0 then
	return '';
end if;

open cur;

repeat
	fetch cur into permit_flag, permit_name;
	if not done then

		if permit_flag & permit_flags then

			set permit_names = concat_ws('\n', permit_names, permit_name);

		end if;

	end if;
until done end repeat;

close cur;

return permit_names;




END $$


DELIMITER ;
