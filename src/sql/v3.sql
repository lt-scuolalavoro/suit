USE suit;

ALTER TABLE Contacts CHANGE `contactName` `name` VARCHAR(32);

UPDATE suit.version SET db_version = 3;
