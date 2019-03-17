CREATE DATABASE IF NOT EXISTS suit;

USE suit;

CREATE TABLE IF NOT EXISTS Candidate (
        id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
        firstName VARCHAR(20),
        lastName VARCHAR(20),
        birthDate DATE,
        employed TINYINT,
        salary FLOAT DEFAULT 0,
        removed TINYINT DEFAULT 0
);

CREATE TABLE suit.version (db_version TINYINT);
INSERT INTO suit.version VALUE (1);
