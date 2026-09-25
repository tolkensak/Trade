
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_indent_edit` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_indent_edit`(in lot_id int unsigned)
BEGIN



select cid, deliver
from indent
where lid = lot_id;




END $$


DELIMITER ;
