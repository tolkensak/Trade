
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_user_list` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_user_list`(in user_id smallint unsigned)
BEGIN



select id, login, disabled
from `user`
where user_id is null || id = user_id
order by login;




END $$


DELIMITER ;
