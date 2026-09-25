
DELIMITER $$

DROP TRIGGER IF EXISTS `tr_price_ai` $$
CREATE DEFINER=`sawda`@`%` TRIGGER `tr_price_ai`
AFTER INSERT ON price FOR EACH ROW
BEGIN



declare sell_price decimal(17,2);

if new.percent then
  set sell_price = new.spend * (1 + new.append / 100);
else
  set sell_price = new.spend + new.append;
end if;

update ware
set price = sell_price
where id = new.wid;




END $$

DELIMITER ;
