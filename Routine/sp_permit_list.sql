
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_permit_list` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_permit_list`()
BEGIN



select id, flag
from permit
order by sort;




END $$


DELIMITER ;
