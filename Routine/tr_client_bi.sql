
DELIMITER $$

DROP TRIGGER IF EXISTS `tr_client_bi` $$
CREATE DEFINER=`sawda`@`%` TRIGGER `tr_client_bi`
BEFORE INSERT ON `client` FOR EACH ROW
BEGIN



set new.coid = fn_new_contact();




END $$

DELIMITER ;
