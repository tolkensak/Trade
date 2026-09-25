
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp__users` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp__users`()
BEGIN



select u.id
	, u.login
	, fn_crypt_dec(u.pass) 'pass'
	, us.desk
	, u.permit 'permit_flag (10)'
	, 0 + hex(u.permit) 'permit_flag (16)'
	, fn__permit_name(u.permit) 'permit_name'
from `user` u
	inner join user_set us on us.uid = u.id;




END $$


DELIMITER ;
