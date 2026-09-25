
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_client_list` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_client_list`(in client_id smallint unsigned)
BEGIN



select id, name, disabled
from `client`
where client_id is null || id = client_id
order by name;




END $$


DELIMITER ;
