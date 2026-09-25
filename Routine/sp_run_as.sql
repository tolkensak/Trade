
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_run_as` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_run_as`(in user_login varchar(255), in user_pass varbinary(128))
BEGIN



select permit
from `user`
where disabled is false
	&& login = user_login
	&& pass = user_pass;




END $$


DELIMITER ;
