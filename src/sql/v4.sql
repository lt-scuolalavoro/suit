USE suit;

ALTER TABLE suit.version CHANGE `db_version` `version` TINYINT(1);

UPDATE suit.version set `version` = 4;