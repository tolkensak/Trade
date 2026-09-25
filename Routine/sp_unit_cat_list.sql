
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_unit_cat_list` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_unit_cat_list`(in unit_cat_id smallint unsigned)
BEGIN



select uc.id, uc.name, u.name 'main unit'
from unit_cat uc
	left join unit u on u.ucid = uc.id && u.main is true
where unit_cat_id is null || uc.id = unit_cat_id
order by uc.name;




END $$


DELIMITER ;
