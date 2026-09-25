
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp_sell_lot_submit` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp_sell_lot_submit`(in lot_id int unsigned)
BEGIN



declare old_foreign_key_checks boolean default @@foreign_key_checks;
set @@foreign_key_checks = 0;


start transaction;

insert into sell(lid, wid, amount, unid, price, total, debt, moment, uid)
select s.lid, s.wid, s.amount, s.unid, if(s.price = fn_ware_price(s.wid, s.moment), NULL, s.price), s.total, s.debt, s.moment, s.uid
from sell_lot s
where s.lid = lot_id
order by s.id;

if @@error_count then
	rollback;
else
	delete from sell_lot where lid = lot_id;

	if @@error_count then
		rollback;
	else
		commit;
	end if;
end if;


set @@foreign_key_checks = old_foreign_key_checks;




END $$


DELIMITER ;
