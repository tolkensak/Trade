
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_indent_list` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_indent_list`(in lot_id int unsigned)
BEGIN



select i.lid
	, i.id
	, c.name 'client'
	, i.deliver
	, i.moment
from indent i
	inner join `client` c on c.id = i.cid
where submitted is false && (lot_id is null || i.lid = lot_id)
order by i.id;




END $$


DELIMITER ;
