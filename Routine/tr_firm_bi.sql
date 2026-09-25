
DELIMITER $$

DROP TRIGGER IF EXISTS `tr_firm_bi` $$
CREATE DEFINER=`sawda`@`%` TRIGGER `tr_firm_bi`
BEFORE INSERT ON `firm` FOR EACH ROW
BEGIN



set new.coid = fn_new_contact();




END $$

DELIMITER ;
