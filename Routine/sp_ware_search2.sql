
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_ware_search2` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_ware_search2`(in name_en varchar(255), in name_kz varchar(255))
BEGIN



select w.id
	, w.name
	, wc.name
	, f.name
from ware w
  inner join ware_cat wc on wc.id=w.wcid
  inner join firm f on f.id=w.fid
where w.name like name_en
	|| w.name like name_kz
order by w.name;



END $$


DELIMITER ;