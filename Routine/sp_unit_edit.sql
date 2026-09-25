
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_unit_edit` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_unit_edit`(in unit_id smallint unsigned)
BEGIN



select name, ucid, ratio
from unit
where id = unit_id;




END $$


DELIMITER ;
