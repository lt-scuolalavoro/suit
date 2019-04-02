ALTER TABLE Contacts CHANGE `contactName` `name` VARCHAR(32);

UPDATE suit.version SET `db_version` = `db_version`+1 WHERE `db_version` = `db_version` LIMIT 1;
