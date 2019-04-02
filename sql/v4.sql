ALTER TABLE suit.version CHANGE `db_version` `version` TINYINT(1);

UPDATE suit.version SET `version` = `version`+1 WHERE `version` = `version` LIMIT 1;