
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_report_list` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_report_list`()
BEGIN



select id, name, fid
from report
order by sort;





END $$


DELIMITER ;