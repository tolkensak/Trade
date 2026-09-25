
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_firm_list` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_firm_list`(in firm_id smallint unsigned)
BEGIN



select f.id
	, f.name
	, (select count(*) from ware w where w.fid = f.id) 'member_num'
	, disabled
from firm f
where firm_id is null || f.id = firm_id
order by f.name;




END $$


DELIMITER ;
