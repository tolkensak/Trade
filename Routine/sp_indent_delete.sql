
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_indent_delete` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_indent_delete`(in lot_id int unsigned)
BEGIN



start transaction;

delete from sell_lot where lid = lot_id;

if @@error_count then
	rollback;
else

	delete from indent where lid = lot_id;

	if @@error_count then
		rollback;
	else
		commit;
	end if;

end if;




END $$


DELIMITER ;
