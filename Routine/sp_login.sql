
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_login` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_login`(in user_login varchar(255), in user_pass varbinary(128))
BEGIN



select u.id
	, u.permit
	, us.desk
from `user` u
	inner join user_set us on us.uid = u.id
where u.disabled is false
	&& u.login = user_login
	&& u.pass = user_pass;




END $$


DELIMITER ;
