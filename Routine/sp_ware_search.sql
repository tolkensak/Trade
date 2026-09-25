
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_ware_search` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_ware_search`(in name_pattern varchar(255))
BEGIN



select w.id
	, w.name
	, wc.name
	, f.name
from ware w
  inner join ware_cat wc on wc.id=w.wcid
  inner join firm f on f.id=w.fid
where w.name like name_pattern
order by w.name;



END $$


DELIMITER ;