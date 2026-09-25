
DELIMITER $$


DROP PROCEDURE IF EXISTS `rp_report_end` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `rp_report_end` ()
BEGIN



insert into tmp (xml) values ('</report>\n');




END $$


DELIMITER ;
