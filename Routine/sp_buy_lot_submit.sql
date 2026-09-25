
DELIMITER $$


DROP PROCEDURE IF EXISTS `sp_buy_lot_submit` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_buy_lot_submit`(in lot_id int unsigned)
BEGIN



declare old_foreign_key_checks boolean default @@foreign_key_checks;
set @@foreign_key_checks = 0;


start transaction;

insert into buy(lid, wid, amount, unid, total, debt, moment, uid)
select b.lid, b.wid, b.amount, b.unid, b.total, b.debt, b.moment, b.uid
from buy_lot b
where b.lid = lot_id
order by b.id;

if @@error_count then
	rollback;
else
	delete from buy_lot where lid = lot_id;

	if @@error_count then
		rollback;
	else
		commit;
	end if;
end if;


set @@foreign_key_checks = old_foreign_key_checks;




END $$


DELIMITER ;
