
DELIMITER $$

DROP PROCEDURE IF EXISTS `sp__erase` $$
CREATE DEFINER=`sawda`@`%` PROCEDURE `sp__erase`()
BEGIN


declare test_uid smallint unsigned default 4;


delete from `indent` where uid = test_uid;
if row_count() != 0 then
alter table `indent` auto_increment=1;
end if;

delete from `client` where uid = test_uid;
if row_count() != 0 then
alter table `client` auto_increment=1;
end if;


delete from `sell` where uid = test_uid;

delete from `sell_lot` where uid = test_uid;
if row_count() != 0 then
alter table `sell_lot` auto_increment=1;
end if;

delete from `lot_sell` where uid = test_uid;
if row_count() != 0 then
alter table `lot_sell` auto_increment=1;
end if;


delete from `buy` where uid = test_uid;

delete from `buy_lot` where uid = test_uid;
if row_count() != 0 then
alter table `buy_lot` auto_increment=1;
end if;

delete from `lot_buy` where uid = test_uid;
if row_count() != 0 then
alter table `lot_buy` auto_increment=1;
end if;


delete from `price` where uid = test_uid;


delete from `ware` where uid = test_uid;
if row_count() != 0 then
alter table `ware` auto_increment=1;
end if;

delete from `ware_cat` where uid = test_uid;
if row_count() != 0 then
alter table `ware_cat` auto_increment=1;
end if;


delete from `firm` where uid = test_uid;
if row_count() != 0 then
alter table `firm` auto_increment=1;
end if;


delete from `unit` where uid = test_uid;
if row_count() != 0 then
alter table `unit` auto_increment=1;
end if;

delete from `unit_cat` where uid = test_uid;
if row_count() != 0 then
alter table `unit_cat` auto_increment=1;
end if;


delete from `user` where uid = test_uid;
if row_count() != 0 then
alter table `user` auto_increment=1;
end if;

delete from `contact` where uid = test_uid;
if row_count() != 0 then
alter table `contact` auto_increment=1;
end if;




END $$


DELIMITER ;
