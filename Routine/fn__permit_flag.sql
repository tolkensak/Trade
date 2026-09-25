
DELIMITER $$


DROP FUNCTION IF EXISTS `fn__permit_flag`$$
CREATE DEFINER=`sawda`@`%` FUNCTION  `fn__permit_flag`(permit_names varchar(1020)) RETURNS int(10) unsigned
BEGIN



declare permit_flags int unsigned default 0;

declare permit_flag int unsigned;
declare permit_name varchar(1020);

declare done int default 0;
declare cur cursor for select flag, name from permit;
declare continue handler for not found set done=1;

if permit_names is null then
	return null;
end if;

if permit_names = '' then
	return 0;
end if;

open cur;

repeat
	fetch cur into permit_flag, permit_name;
	if not done then
		if locate(permit_name, permit_names) then
			set permit_flags = permit_flags | permit_flag;
		end if;
	end if;
until done end repeat;

close cur;

return permit_flags;




END $$


DELIMITER ;
