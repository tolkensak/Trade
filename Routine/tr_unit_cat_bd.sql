
DELIMITER $$

DROP TRIGGER IF EXISTS `tr_unit_cat_bd` $$
CREATE DEFINER=`dba`@`%` TRIGGER `tr_unit_cat_bd`
BEFORE DELETE ON `unit_cat` FOR EACH ROW
BEGIN



insert into tmp(name) values('de');





END $$

DELIMITER ;
