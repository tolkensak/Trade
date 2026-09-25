
DELIMITER $$

DROP TRIGGER IF EXISTS `tr_user_bd` $$
CREATE DEFINER=`sawda`@`%` TRIGGER `tr_user_bd`
BEFORE DELETE ON `user` FOR EACH ROW
BEGIN



delete from user_set where uid = old.id;





END $$

DELIMITER ;
