
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_contact_edit` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_contact_edit`(in contact_id smallint unsigned)
BEGIN



select first_name
	, last_name
	, phone
	, mobile
	, address
	, `comment`
from contact
where id = contact_id;




END $$


DELIMITER ;
