USE suit;

ALTER TABLE Candidate CHANGE `removed` `deleted` TINYINT(1);

CREATE TABLE IF NOT EXISTS Contacts (
        id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
        candidateId int,
        FOREIGN KEY (candidateId) REFERENCES Candidate(id),
        contactName VARCHAR(100),
        link VARCHAR(255)
);

UPDATE suit.version set db_version = 2;
