
DELIMITER $$


DROP PROCEDURE IF EXISTS `rp_4` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `rp_4`(
	  in moment_from datetime
	, in moment_to datetime
	, in cat_id smallint unsigned
	, in firm_id smallint unsigned
	, in ware_id smallint unsigned
	, inout xml longtext)
BEGIN


declare v_from datetime default ifnull(moment_from, '1000-01-01 00:00:00');
declare v_to datetime default ifnull(moment_to, '9999-12-31 23:59:59');

declare v_wid smallint unsigned;
declare v_ware varchar(255);
declare v_cat varchar(255);
declare v_firm varchar(255);
declare v_times int unsigned;

declare done int default 0;
declare cur cursor for
	select w.id
		, w.name 'ware'
		, ifnull(( select count(*)
			from sell s
			where s.wid = w.id && s.debt is null && s.moment between v_from and v_to
		), 0) 'times'
		, wc.name 'category'
		, f.name 'firm'
	from ware w
		inner join ware_cat wc on wc.id = w.wcid
		inner join firm f on f.id = w.fid
	where (cat_id is null ||  w.wcid = cat_id)
		&& (firm_id is null ||  w.fid = firm_id)
		&& (ware_id is null || w.id = ware_id)
	order by 3 desc, 2;
declare continue handler for not found set done = 1;



open cur;

repeat
	fetch cur into v_wid, v_ware, v_times, v_cat, v_firm;
	if not done then
		set xml = concat(xml
					, '\t\t<i>\n'
					, '\t\t\t<wid>', v_wid, '</wid>\n'
					, '\t\t\t<ware>', v_ware, '</ware>\n'
					, '\t\t\t<times>', v_times, '</times>\n'
					, '\t\t\t<cat>', v_cat, '</cat>\n'
					, '\t\t\t<firm>', v_firm, '</firm>\n'
					, '\t\t</i>\n');
	end if;
until done end repeat;

close cur;





END $$


DELIMITER ;