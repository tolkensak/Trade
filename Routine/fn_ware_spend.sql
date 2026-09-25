
DELIMITER $$


DROP FUNCTION IF EXISTS `fn_ware_spend` $$
CREATE DEFINER=`sawda`@`%` FUNCTION `fn_ware_spend`(ware_id smallint unsigned, moment_to datetime) RETURNS decimal(17,2)
BEGIN



return
(
	select spend
	from price
	where wid = ware_id  && moment < moment_to
	order by moment desc
	limit 1
);




END $$


DELIMITER ;