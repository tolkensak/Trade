
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_return_ware` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_return_ware`(in ware_id smallint unsigned)
BEGIN



select w.name 'ware'
from ware w
  inner join ware_cat wc on wc.id = w.wcid
  inner join firm f on f.id = w.fid
where w.id = ware_id;





END $$


DELIMITER ;
