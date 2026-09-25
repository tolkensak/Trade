
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_unit_cat_insert` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_unit_cat_insert`(in unit_cat_name varchar(255), in main_unit_name varchar(255))
BEGIN



declare unit_cat_id smallint unsigned default 0;


start transaction;

insert into unit_cat(name) values(unit_cat_name);

if @@error_count then
	rollback;
else

	set unit_cat_id = last_insert_id();
	insert into unit(name, ucid, ratio, main) values(main_unit_name, unit_cat_id, 1, 1);

	if @@error_count then
		set unit_cat_id = 0;
		rollback;
	else
		commit;
	end if;

end if;

select unit_cat_id;




END $$


DELIMITER ;
