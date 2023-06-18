-- script dat de profa
USE master
GO
IF(EXISTS(SELECT * FROM sys.databases WHERE name='S32023'))
	DROP DATABASE S32023;
GO
CREATE DATABASE S32023;
GO
USE S32023;
GO
CREATE TABLE Tari
(cod_t INT PRIMARY KEY IDENTITY,
nume_tara VARCHAR(100)
);
CREATE TABLE Destinatii
(cod_d INT PRIMARY KEY IDENTITY,
nume_destinatie VARCHAR(100),
descriere_destinatie VARCHAR(200),
cod_t INT FOREIGN KEY REFERENCES Tari(cod_t)
ON UPDATE CASCADE ON DELETE CASCADE
);
CREATE TABLE Sejururi
(cod_s INT PRIMARY KEY IDENTITY,
nume_sejur VARCHAR(100),
detalii_sejur VARCHAR(300),
data_inceput DATE,
data_sfarsit DATE,
cod_d INT FOREIGN KEY REFERENCES Destinatii(cod_d)
ON UPDATE CASCADE ON DELETE CASCADE
);
CREATE TABLE Participanti
(cod_p INT PRIMARY KEY IDENTITY,
nume_participant VARCHAR(200),
email VARCHAR(100),
data_nasterii DATE,
adresa VARCHAR(200)
);
CREATE TABLE Achizitii
(cod_s INT FOREIGN KEY REFERENCES Sejururi(cod_s)
ON UPDATE CASCADE ON DELETE CASCADE,
cod_p INT FOREIGN KEY REFERENCES Participanti(cod_p)
ON UPDATE CASCADE ON DELETE CASCADE,
cost_sejur INT CHECK(cost_sejur>0),
CONSTRAINT pk_Achizitii PRIMARY KEY (cod_s,cod_p)
);
--Tari
INSERT INTO Tari (nume_tara) VALUES ('Spania');
INSERT INTO Tari (nume_tara) VALUES ('Portugalia');
INSERT INTO Tari (nume_tara) VALUES ('Grecia');
--Destinatii
INSERT INTO Destinatii (nume_destinatie,descriere_destinatie,cod_t) VALUES
('Gran Canaria','descriere Gran Canaria',1);
INSERT INTO Destinatii (nume_destinatie,descriere_destinatie,cod_t) VALUES
('Tenerife','descriere Tenerife',1);
INSERT INTO Destinatii (nume_destinatie,descriere_destinatie,cod_t) VALUES
('Madeira','descriere Madeira',2);
--Sejururi Gran Canaria
INSERT INTO Sejururi (nume_sejur,detalii_sejur,data_inceput,data_sfarsit,cod_d)
VALUES ('sejur1 Gran Canaria','detalii sejur1','2023-06-10','2023-06-17',1);
INSERT INTO Sejururi (nume_sejur,detalii_sejur,data_inceput,data_sfarsit,cod_d)
VALUES ('sejur2 Gran Canaria','detalii sejur2','2023-07-10','2023-07-17',1);
INSERT INTO Sejururi (nume_sejur,detalii_sejur,data_inceput,data_sfarsit,cod_d)
VALUES ('sejur3 Gran Canaria','detalii sejur3','2023-05-20','2023-05-27',1);
--Sejururi Tenerife
INSERT INTO Sejururi (nume_sejur,detalii_sejur,data_inceput,data_sfarsit,cod_d)
VALUES ('sejur4 Tenerife','detalii sejur4','2023-06-11','2023-06-18',2);
INSERT INTO Sejururi (nume_sejur,detalii_sejur,data_inceput,data_sfarsit,cod_d)
VALUES ('sejur5 Tenerife','detalii sejur5','2023-07-18','2023-07-22',2);
INSERT INTO Sejururi (nume_sejur,detalii_sejur,data_inceput,data_sfarsit,cod_d)
VALUES ('sejur6 Tenerife','detalii sejur6','2023-09-20','2023-09-27',2);
--Sejururi Madeira
INSERT INTO Sejururi (nume_sejur,detalii_sejur,data_inceput,data_sfarsit,cod_d)
VALUES ('sejur7 Madeira','detalii sejur7','2023-04-23','2023-04-30',3);
INSERT INTO Sejururi (nume_sejur,detalii_sejur,data_inceput,data_sfarsit,cod_d)
VALUES ('sejur8 Madeira','detalii sejur8','2023-05-20','2023-05-30',3);
INSERT INTO Sejururi (nume_sejur,detalii_sejur,data_inceput,data_sfarsit,cod_d)
VALUES ('sejur9 Madeira','detalii sejur9','2023-07-14','2023-07-31',3);
--Participanti 
INSERT INTO Participanti (nume_participant,email,data_nasterii,adresa) VALUES
('participant1','participant1@gmail.com','2000-03-04','adresa participant1');
INSERT INTO Participanti (nume_participant,email,data_nasterii,adresa) VALUES
('participant2','participant2@yahoo.com','1980-07-08','adresa participant2');
INSERT INTO Participanti (nume_participant,email,data_nasterii,adresa) VALUES
('participant3','participant3@gmail.com','2000-09-07','adresa participant3');
--Achizitii
INSERT INTO Achizitii (cod_s,cod_p,cost_sejur) VALUES (1,1,1000);
INSERT INTO Achizitii (cod_s,cod_p,cost_sejur) VALUES (4,2,2400);
INSERT INTO Achizitii (cod_s,cod_p,cost_sejur) VALUES (7,3,1250);