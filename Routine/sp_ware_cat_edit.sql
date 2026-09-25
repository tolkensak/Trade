
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_ware_cat_edit` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_ware_cat_edit`(in ware_cat_id smallint unsigned)
BEGIN



select name
from ware_cat
where id = ware_cat_id;




END $$


DELIMITER ;
