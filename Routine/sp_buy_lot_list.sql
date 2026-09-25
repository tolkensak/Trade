
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_buy_lot_list` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_buy_lot_list`(in lot_id int unsigned, in buy_id int unsigned)
BEGIN



select b.id
	, w.name 'ware'
	, wc.name 'ware_cat'
	, b.amount
	, un.name 'unit'
	, b.price
	, b.total
	, b.debt
	, b.moment
from buy_lot b
	inner join ware w on w.id = b.wid
	inner join ware_cat wc on wc.id = w.wcid
	inner join unit un on un.id = b.unid
where b.lid = lot_id && (buy_id is null || b.id = buy_id)
order by b.id;




END $$


DELIMITER ;
