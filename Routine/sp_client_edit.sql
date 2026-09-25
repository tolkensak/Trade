
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_client_edit` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_client_edit`(in client_id smallint unsigned)
BEGIN



select name
	, disabled
from `client`
where id = client_id;




END $$


DELIMITER ;
