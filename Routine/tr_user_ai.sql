
DELIMITER $$

DROP TRIGGER IF EXISTS `tr_user_ai` $$
CREATE DEFINER=`sawda`@`%` TRIGGER `tr_user_ai`
AFTER INSERT ON `user` FOR EACH ROW
BEGIN



insert into user_set(uid) values(new.id);




END $$

DELIMITER ;
