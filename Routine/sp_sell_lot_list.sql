
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_sell_lot_list` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_sell_lot_list`(in lot_id int unsigned, in sell_id int unsigned)
BEGIN



select s.id
	, w.name 'ware'
	, wc.name 'ware_cat'
	, s.amount
	, un.name 'unit'
	, s.price
	, s.total
	, s.debt
	, s.moment
from sell_lot s
	inner join ware w on w.id = s.wid
	inner join ware_cat wc on wc.id = w.wcid
	inner join unit un on un.id = s.unid
where s.lid = lot_id && (sell_id is null || s.id = sell_id)
order by s.id;




END $$


DELIMITER ;
