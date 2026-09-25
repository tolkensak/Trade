
DELIMITER $$


DROP PROCEDURE IF EXISTS `rp_report_end` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `rp_report_end` (inout xml longtext)
BEGIN



set xml = concat(xml, '</report>\n');



END $$


DELIMITER ;
