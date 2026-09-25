
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp__triggers` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp__triggers`()
BEGIN



select trigger_name
	, action_statement
	, event_manipulation
	, event_object_table
	, action_orientation
	, action_timing
	, `definer`
from information_schema.TRIGGERS
where trigger_schema='sawda1';




END $$


DELIMITER ;
