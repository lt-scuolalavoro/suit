ALTER TABLE Candidate CHANGE `removed` `deleted` TINYINT(1);
ALTER TABLE Candidate ALTER `deleted` SET DEFAULT 0;
ALTER TABLE Candidate ALTER `salary` SET DEFAULT 0;
ALTER TABLE Candidate ADD `notes` VARCHAR(255) AFTER `salary`;

CREATE TABLE IF NOT EXISTS Contacts (
        id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
        candidateId int,
        FOREIGN KEY (candidateId) REFERENCES Candidate(id),
        contactName VARCHAR(100),
        link VARCHAR(255)
);

UPDATE suit.version SET `db_version`=`db_version` + 1 WHERE `db_version`= `db_version` LIMIT 1;
