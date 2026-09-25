
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp__prices` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp__prices`()
BEGIN



select p1.*
from price p1
	left join price p2 on p2.wid = p1.wid and p2.moment > p1.moment
where p2.wid is null;




END $$


DELIMITER ;
