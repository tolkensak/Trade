
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_unit_cat_delete` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_unit_cat_delete`(in unit_cat_id smallint unsigned)
BEGIN



start transaction;

delete from unit where ucid = unit_cat_id;

if @@error_count then
	rollback;
else

	delete from unit_cat where id = unit_cat_id;

	if @@error_count then
		rollback;
	else
		commit;
	end if;

end if;




END $$


DELIMITER ;
