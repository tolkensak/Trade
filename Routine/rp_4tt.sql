
DELIMITER $$


DROP PROCEDURE IF EXISTS `rp_4` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `rp_4`(
	  in moment_from datetime
	, in moment_to datetime
	, in cat_id smallint unsigned
	, in firm_id smallint unsigned)
BEGIN



declare v_from datetime default ifnull(moment_from, '1000-01-01 00:00:00');
declare v_to datetime default ifnull(moment_to, '9999-12-31 23:59:59');


insert into tmp (xml)
select concat('\t\t<i>\n'
	, '\t\t\t<wid>', cast(w.id as char), '</wid>\n'
	, '\t\t\t<ware>', w.name, '</ware>\n'
	, '\t\t\t<times>', cast(ifnull(( select count(*)
								from sell s
								where s.wid = w.id && s.debt is null && s.moment between v_from and v_to
							), 0) as char), '</times>\n'
	, '\t\t\t<cat>', wc.name, '</cat>\n'
	, '\t\t\t<firm>', f.name, '</firm>\n'
	, '\t\t</i>\n')
from ware w
	inner join ware_cat wc on wc.id = w.wcid && (cat_id is null ||  wc.id = cat_id)
	inner join firm f on f.id = w.fid && (firm_id is null ||  f.id = firm_id);





END $$


DELIMITER ;