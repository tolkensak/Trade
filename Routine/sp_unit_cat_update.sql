
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_unit_cat_update` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_unit_cat_update`(in unit_cat_id smallint unsigned, in unit_cat_name varchar(255), in main_unit_name varchar(255))
BEGIN



start transaction;

update unit_cat
set name = unit_cat_name
where id = unit_cat_id;

if @@error_count then
	rollback;
else

	update unit
	set name = main_unit_name
	where ucid = unit_cat_id && main is true;

	if @@error_count then
		rollback;
	else
		commit;
	end if;

end if;

select unit_cat_id;




END $$


DELIMITER ;
