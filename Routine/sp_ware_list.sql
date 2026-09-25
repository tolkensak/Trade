
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_ware_list` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_ware_list`(in ware_id smallint unsigned)
BEGIN



select w.id
  , w.name
  , w.price
  , wc.name 'ware_cat'
  , f.name 'firm'
  , uc.name 'unit_cat'
from ware w
  inner join ware_cat wc on wc.id = w.wcid
  inner join unit_cat uc on uc.id = w.ucid
  inner join firm f on f.id = w.fid
where ware_id is null || w.id = ware_id
order by wc.name, w.name;




END $$


DELIMITER ;
