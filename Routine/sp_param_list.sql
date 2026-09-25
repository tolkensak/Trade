
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_param_list` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_param_list`(in form_id smallint unsigned)
BEGIN



select p.id
	, p.name
	, p.tid
	, p.style
	, p.source
	, p.`default`
from param p
	inner join form_param fp on fp.fid = form_id && fp.pid = p.id
order by fp.sort;





END $$


DELIMITER ;