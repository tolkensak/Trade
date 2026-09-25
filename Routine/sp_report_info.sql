
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_report_info` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_report_info`(in report_id smallint unsigned)
BEGIN



select fid, proc
from report
where id = report_id;





END $$


DELIMITER ;