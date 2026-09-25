
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_ware_edit` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_ware_edit`(in ware_id smallint unsigned)
BEGIN



select name, wcid, ucid, fid
from ware
where id = ware_id;




END $$


DELIMITER ;
