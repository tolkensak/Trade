
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_permit_reload` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_permit_reload`(in user_id smallint unsigned)
BEGIN



select permit
from `user`
where id = user_id;




END $$


DELIMITER ;
