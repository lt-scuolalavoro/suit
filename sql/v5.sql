ALTER TABLE suit.version ENGINE = InnoDB;
ALTER TABLE Candidate ENGINE = InnoDB;
ALTER TABLE Contacts ENGINE = InnoDB;

UPDATE suit.version SET `version` = `version`+1 WHERE `version` = `version` LIMIT 1;