
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_role_list` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_role_list`()
BEGIN



select id, permit
from role
order by sort;




END $$


DELIMITER ;
