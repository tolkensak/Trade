
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_firm_edit` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_firm_edit`(in firm_id smallint unsigned)
BEGIN



select name, disabled
from firm
where id = firm_id;




END $$


DELIMITER ;
