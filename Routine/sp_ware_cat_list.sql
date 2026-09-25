
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_ware_cat_list` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_ware_cat_list`(in ware_cat_id smallint unsigned)
BEGIN



select wc.id
	, wc.name
	, (select count(*) from ware w where w.wcid = wc.id) 'member_num'
from ware_cat wc
where ware_cat_id is null || wc.id = ware_cat_id
order by wc.name;




END $$


DELIMITER ;
