
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp__permits` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp__permits`()
BEGIN



select id
	, name
	, flag 'flag (10)'
	, 0 + hex(flag) 'flag (16)'
from permit
order by id;




END $$


DELIMITER ;
