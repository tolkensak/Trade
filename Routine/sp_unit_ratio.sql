
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_unit_ratio` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_unit_ratio`(in unit_id smallint unsigned)
BEGIN



select ifnull(ratio, 0) from unit where id = unit_id;




END $$


DELIMITER ;
