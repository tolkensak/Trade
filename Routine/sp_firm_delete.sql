
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_firm_delete` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_firm_delete`(in firm_id smallint unsigned)
BEGIN



start transaction;

delete from ware where fid = firm_id;

if @@error_count then
	rollback;
else

	delete from firm where id = firm_id;

	if @@error_count then
		rollback;
	else
		commit;
	end if;

end if;




END $$


DELIMITER ;
