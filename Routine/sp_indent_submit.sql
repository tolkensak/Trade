
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_indent_submit` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_indent_submit`(in lot_id int unsigned)
BEGIN


start transaction;

call sp_sell_lot_submit(lot_id);

if @@error_count then
	rollback;
else
	update indent set submitted = true where lid = lot_id;

	if @@error_count then
		rollback;
	else
		commit;
	end if;
end if;




END $$


DELIMITER ;
