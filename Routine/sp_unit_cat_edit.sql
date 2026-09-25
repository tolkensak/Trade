
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_unit_cat_edit` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_unit_cat_edit`(in unit_cat_id smallint unsigned)
BEGIN



select uc.name, u.name
from unit_cat uc
	inner join unit u on u.ucid = uc.id && u.main is true
where uc.id = unit_cat_id;




END $$


DELIMITER ;
