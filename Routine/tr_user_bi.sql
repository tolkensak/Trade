
DELIMITER $$

DROP TRIGGER IF EXISTS `tr_user_bi` $$
CREATE DEFINER=`sawda`@`%` TRIGGER `tr_user_bi`
BEFORE INSERT ON `user` FOR EACH ROW
BEGIN



set new.coid = fn_new_contact();




END $$

DELIMITER ;
