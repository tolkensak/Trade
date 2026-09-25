
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_ware_cat_delete` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_ware_cat_delete`(in ware_cat_id smallint unsigned)
BEGIN



start transaction;

delete from ware where wcid = ware_cat_id;

if @@error_count then
	rollback;
else

	delete from ware_cat where id = ware_cat_id;

	if @@error_count then
		rollback;
	else
		commit;
	end if;

end if;




END $$


DELIMITER ;
