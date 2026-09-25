
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_unit_list` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_unit_list`(in unit_id smallint unsigned)
BEGIN



select u.id
	, u.name
	, u.ratio
	, um.name 'main unit'
	, uc.name 'unit_cat'
from unit u
	inner join unit_cat uc on uc.id = u.ucid
	inner join unit um on um.ucid = u.ucid && um.main is true
where u.main is false && (unit_id is null || u.id = unit_id)
order by uc.name
	, u.main desc
	, u.ratio;




END $$


DELIMITER ;
