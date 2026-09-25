
DELIMITER $$


DROP FUNCTION IF EXISTS `fn_ntos` $$
CREATE DEFINER=`sawda`@`%` FUNCTION `fn_ntos`(num bigint unsigned) RETURNS varchar(255) CHARSET utf8
BEGIN


declare ret varchar(255) default '';
declare str varchar(255);
declare pos varchar(255);
declare added bool default false;
declare len int;
declare c char(1);
declare i int default 0;


if num is null then
	return '(null)';
end if;

if num = 0 then
	return 'нөл';
end if;


set str = cast(num as char);
set len = length(str);

while i < len do
	set c = substr(str, -(i + 1), 1);

	case i mod 3 
		when 0 then set pos = fn_ntos_p1(c);
		when 1 then set pos = fn_ntos_p2(c);
		when 2 then set pos = fn_ntos_p3(c);
	end case;

	if pos != '' then
		if added is false then
			set added = true;
			
			if i >= 3 then
				case i div 3
					when 1 then set pos = concat(pos, ' мың');
					when 2 then set pos = concat(pos, ' милион');
					when 3 then set pos = concat(pos, ' билион');
					when 4 then set pos = concat(pos, ' трилион');
					#when 5 then set pos = concat(pos, '');
					#when 6 then set pos = concat(pos, '');
					#when 7 then set pos = concat(pos, '');
					else set pos = concat(pos, ' ШЕКСІЗ');
				end case;
			end if;
		end if;

		set ret = concat(pos, ' ', ret);
	end if;

	if i mod 3 = 2 then
		set added = false;
	end if;

	set i = i + 1;
end while;


return ret;




END $$


DELIMITER ;
