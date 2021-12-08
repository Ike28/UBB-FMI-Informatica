USE DiebmannImobiliare
GO

-- Tabela ce tine versiunea curenta a bazei de date

CREATE TABLE Versiuni (
	idVersiune INT PRIMARY KEY DEFAULT 0
);
GO

INSERT INTO Versiuni(idVersiune)
VALUES(0);

-- Procedura 1. Modifica tipul de date al unei coloane

CREATE PROCEDURE Procedura_1 AS
BEGIN
	ALTER TABLE Vizionari
	ALTER COLUMN dataProgramarii TIME
	UPDATE Versiuni SET idVersiune = 1
	PRINT 'Tabela VIZIONARI: Coloana DATAPROGRAMARII este acum TIME'
END
GO

-- Inversa Procedura 1. Anuleaza modificarea tipului coloanei

CREATE PROCEDURE Undo_Procedura_1 AS
BEGIN
	ALTER TABLE Vizionari
	ALTER COLUMN dataProgramarii DATETIME
	UPDATE Versiuni SET idVersiune = 0
	PRINT 'Tabela VIZIONARI: Coloana DATAPROGRAMARII este acum DATETIME (original)'
END
GO

-- Procedura 2. Adauga o constrangere de valoare implicita pentru o coloana

CREATE PROCEDURE Procedura_2 AS
BEGIN
	ALTER TABLE Spatii
	ADD CONSTRAINT def_camere DEFAULT 1 FOR camere
	UPDATE Versiuni SET idVersiune = 2
	PRINT 'Tabela SPATII: Coloana CAMERE are acum valoare implicita la 1'
END
GO

-- Inversa Procedura 2. Elimina constrangerea de valoare implicita adaugata

CREATE PROCEDURE Undo_Procedura_2 AS
BEGIN
	ALTER TABLE Spatii
	DROP CONSTRAINT def_camere
	UPDATE Versiuni SET idVersiune = 1
	PRINT 'Tabela SPATII: Coloana CAMERE acum nu are valoare implicita (original)'
END
GO

-- Procedura 3. Creeaza o noua tabela

CREATE PROCEDURE Procedura_3 AS
BEGIN
	CREATE TABLE ContracteAngajati (
		idContract INT PRIMARY KEY IDENTITY(90210, 1),
		idAngajat INT NOT NULL,
		dataContract DATETIME NOT NULL,
		salariu INT NOT NULL
	)
	UPDATE Versiuni SET idVersiune = 3
	PRINT 'Tabela CONTRACTEANGAJATI a fost creata'

END
GO

-- Inversa Procedura 3. Sterge tabela nou-creata

CREATE PROCEDURE Undo_Procedura_3 AS
BEGIN
	DROP TABLE ContracteAngajati
	UPDATE Versiuni SET idVersiune = 2
	PRINT 'Tabela CONTRACTEANGAJATI a fost stearsa (original)'
END
GO


-- Procedura 4. Adauga o coloana la o tabela existenta

CREATE PROCEDURE Procedura_4 AS
BEGIN
	ALTER TABLE Proprietari
	ADD adresa VARCHAR(100)
	UPDATE Versiuni SET idVersiune = 4
	PRINT 'Tabela PROPRIETARI: Coloana ADRESA a fost adaugata'
END
GO

-- Inversa Procedura 4. Sterge coloana nou-adaugata

CREATE PROCEDURE Undo_Procedura_4 AS
BEGIN
	ALTER TABLE Proprietari
	DROP COLUMN adresa
	UPDATE Versiuni SET idVersiune = 3
	PRINT 'Tabela PROPRIETARI: Coloana ADRESA a fost stearsa (original)'
END
GO

-- Procedura 5. Adauga o constrangere de cheie straina unei coloane

CREATE PROCEDURE Procedura_5 AS
BEGIN
	ALTER TABLE ContracteAngajati
	ADD CONSTRAINT fk_idAngajat FOREIGN KEY(idAngajat) 
	REFERENCES Agenti(idAgent)

	UPDATE Versiuni SET idVersiune = 5
	PRINT 'Tabela CONTRACTEANGAJATI: A fost adaugata o constrangere de cheie straina pentru coloana IDANGAJAT'
END
GO

-- Inversa Procedura 5. Elimina constrangerea nou-adaugata

CREATE PROCEDURE Undo_Procedura_5 AS
BEGIN
	ALTER TABLE ContracteAngajati
	DROP CONSTRAINT fk_idAngajat
	UPDATE Versiuni SET idVersiune = 4
	PRINT 'Tabela CONTRACTEANGAJATI: A fost stearsa constrangerea de cheie straina pentru coloana IDANGAJAT (original)'
END
GO

-- Driver code

CREATE PROCEDURE Diebmann_VCS @updateVersion INT
AS
BEGIN
	DECLARE @currentVersion INT 
	DECLARE @versionCounter INT
	SELECT TOP 1 @currentVersion = idVersiune
	FROM Versiuni

	SET @versionCounter = @currentVersion

	DECLARE @procedure VARCHAR(30)

	IF @versionCounter < @updateVersion
		BEGIN
			SET @versionCounter = @versionCounter + 1
			WHILE @versionCounter <= @updateVersion
			BEGIN
				
				SET @procedure = 'Procedura_' + CONVERT(VARCHAR(2), @versionCounter)
				EXEC @procedure
				SET @versionCounter = @versionCounter + 1
			END
		END

	ELSE
		BEGIN
			
			IF @versionCounter > @updateVersion
			BEGIN
				WHILE @versionCounter > @updateVersion
				BEGIN
					
					SET @procedure = 'Undo_Procedura_' + CONVERT(VARCHAR(2), @versionCounter)
					EXEC @procedure
					SET @versionCounter = @versionCounter - 1
				END
			END
		END
		PRINT 'VERSIUNE VECHE: ' + CONVERT(VARCHAR(2), @currentVersion) +
		' | VERSIUNE NOUA: ' + CONVERT(VARCHAR(2), @updateVersion)
END

EXEC Diebmann_VCS 5
EXEC Diebmann_VCS 0
