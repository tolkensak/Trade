
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_user_edit` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_user_edit`(in user_id smallint unsigned)
BEGIN



select login, disabled
from `user`
where id = user_id;




END $$


DELIMITER ;
