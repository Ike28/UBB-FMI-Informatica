USE DiebmannImobiliare
GO

CREATE OR ALTER PROCEDURE InsertSedii
@NoOfRows INT
AS 
BEGIN
	DBCC CHECKIDENT ('Sedii', RESEED, 0);
	DECLARE @cnt INT = 0;
	WHILE @cnt < @NoOfRows
	BEGIN
		INSERT INTO Sedii(oras, adresa, telefon)
		VALUES('Cluj','Str. Alverna nr. 21','0760330010')
		SET @cnt = @cnt + 1;
	END
END

GO

CREATE OR ALTER PROCEDURE InsertAgenti
@NoOfRows INT
AS
BEGIN
	EXEC InsertSedii 2000
	DBCC CHECKIDENT ('Agenti', RESEED, 0);
	DECLARE @cnt INT = 0;
	WHILE @cnt < @NoOfRows
	BEGIN
		INSERT INTO Agenti(idSediuAsignat, nume, telefon, email)
		VALUES (@cnt + 1, 'Claudiu Dubas', '0123456789', 'dieb1@gmail.com');
		SET @cnt = @cnt + 1;
	END
END

GO

CREATE OR ALTER PROCEDURE InsertMasiniAngajati
@NoOfRows INT
AS
BEGIN
	DECLARE @cnt INT = 0;
	WHILE @cnt < @NoOfRows
	BEGIN
		INSERT INTO MasiniAngajati(idMasina, idAngajat)
		VALUES (@cnt + 1, @cnt + 2);
		SET @cnt = @cnt + 1;
	END
END

GO

CREATE OR ALTER PROCEDURE InsertClienti
@NoOfRows INT
AS
BEGIN
	DBCC CHECKIDENT ('Clienti', RESEED, 0);
	DECLARE @cnt INT = 0;
	WHILE @cnt < @NoOfRows
	BEGIN
		INSERT INTO Clienti(nume, telefon, email)
		VALUES ('Popea Protopopescu', '0123456789', 'dieb1@gmail.com');
		SET @cnt = @cnt + 1;
	END
END

GO

CREATE OR ALTER PROCEDURE InsertProprietari
@NoOfRows INT
AS
BEGIN
	DBCC CHECKIDENT ('Proprietari', RESEED, 0);
	DECLARE @cnt INT = 0;
	WHILE @cnt < @NoOfRows
	BEGIN
		INSERT INTO Proprietari(nume, telefon, email)
		VALUES ('Popea Protopopescu', '0123456789', 'dieb1@gmail.com');
		SET @cnt = @cnt + 1;
	END
END

GO

CREATE OR ALTER PROCEDURE InsertProprietateGeneral
@NoOfRows INT
AS
BEGIN
	DBCC CHECKIDENT ('ProprietateGeneral', RESEED, 0);
	DECLARE @cnt INT = 0;
	WHILE @cnt < @NoOfRows
	BEGIN
		INSERT INTO ProprietateGeneral(idProprietar, idAgentAsignat, tip, oras, zona, adresa, suprafata)
		VALUES (@cnt + 1, @cnt + 1, 'locuinta', 'Prundu Bargaului', 'Cascade', 'Str. Iluminatiei nr. 28h', 1);
		SET @cnt = @cnt + 1;
	END
END

GO

CREATE OR ALTER PROCEDURE InsertLocuinte
@NoOfRows INT
AS
BEGIN
	DECLARE @cnt INT = 0;
	WHILE @cnt < @NoOfRows
	BEGIN
		INSERT INTO Locuinte(idLocuinta, tipLoc, compartimentare, camere)
		VALUES (@cnt + 1, 'apartament', 'decomandat', 90);
		SET @cnt = @cnt + 1;
	END
END

GO

CREATE OR ALTER PROCEDURE InsertSpatii
@NoOfRows INT
AS
BEGIN
	DECLARE @cnt INT = 0;
	WHILE @cnt < @NoOfRows
	BEGIN
		INSERT INTO Spatii(idSpatiu, tipSpatiu, camere)
		VALUES (@cnt + 1, 'industrial', 1);
		SET @cnt = @cnt + 1;
	END
END

GO

CREATE OR ALTER PROCEDURE InsertTerenuri
@NoOfRows INT
AS
BEGIN
	DECLARE @cnt INT = 0;
	WHILE @cnt < @NoOfRows
	BEGIN
		INSERT INTO Terenuri(idTeren, tipTeren)
		VALUES (@cnt + 1, 'intravilan');
		SET @cnt = @cnt + 1;
	END
END

GO

CREATE OR ALTER PROCEDURE InsertAnunturi
@NoOfRows INT
AS
BEGIN
	DBCC CHECKIDENT ('Anunturi', RESEED, 0);
	DECLARE @cnt INT = 0;
	WHILE @cnt < @NoOfRows
	BEGIN
		INSERT INTO Anunturi(idProprietateAnunt, tip, pret)
		VALUES (@cnt + 1, 'inchiriere', 1);
		SET @cnt = @cnt + 1;
	END
END

GO

CREATE OR ALTER PROCEDURE InsertVizionari
@NoOfRows INT
AS
BEGIN
	DBCC CHECKIDENT ('Vizionari', RESEED, 0);
	DECLARE @cnt INT = 0;
	WHILE @cnt < @NoOfRows
	BEGIN
		INSERT INTO Vizionari(idClientSolicitant, idAnuntReferent, dataProgramarii)
		VALUES (@cnt + 1, @cnt + 1, '20120618 10:34:09 AM');
		SET @cnt = @cnt + 1;
	END
END

GO

CREATE OR ALTER PROCEDURE InsertContracte
@NoOfRows INT
AS
BEGIN
	DBCC CHECKIDENT ('Contracte', RESEED, 0);
	DECLARE @cnt INT = 0;
	WHILE @cnt < @NoOfRows
	BEGIN
		INSERT INTO Contracte(idProprietateContract, idClientContract, valoare, lunaTranz, anTranz, tip, perioada)
		VALUES (@cnt + 1, @cnt + 1, 1, 1, 1, 1971, 'inchiriere', 2000);
		SET @cnt = @cnt + 1;
	END
END

GO

CREATE OR ALTER PROCEDURE ResetDB
AS
BEGIN

	SELECT * FROM Contracte
	DELETE FROM Contracte WHERE idContract > 0

	SELECT * FROM Vizionari
	DELETE FROM Vizionari WHERE idVizionare > 0

	SELECT * FROM Anunturi
	DELETE FROM Anunturi WHERE idAnunt > 0

	SELECT * FROM Locuinte
	DELETE FROM Locuinte WHERE idLocuinta > 0

	SELECT * FROM Spatii
	DELETE FROM Spatii WHERE idSpatiu > 0

	SELECT * FROM Terenuri
	DELETE FROM Terenuri WHERE idTeren > 0

	SELECT * FROM ProprietateGeneral
	DELETE FROM ProprietateGeneral WHERE idProprietate > 0

	SELECT * FROM Clienti
	DELETE FROM Clienti WHERE idClient > 0

	SELECT * FROM Proprietari
	DELETE FROM Proprietari WHERE idProprietar > 0

	SELECT * FROM MasiniAngajati
	DELETE FROM MasiniAngajati WHERE idMasina > 0

	SELECT * FROM Agenti
	DELETE FROM Agenti WHERE idAgent > 0

	SELECT * FROM Sedii
	DELETE FROM Sedii WHERE idSediu > 0 

END

GO

DELETE FROM TestRuns
DELETE FROM TestRunViews
DELETE FROM TestRunTables

INSERT INTO Tables(Name)
VALUES
('Sedii'),
('Agenti'),
('MasiniAngajati'),
('Clienti'),
('Proprietari'),
('ProprietateGeneral'),
('Locuinte'),
('Spatii'),
('Terenuri'),
('Anunturi'),
('Vizionari'),
('Contracte')


INSERT INTO Tests(Name)
VALUES('test_MasiniAngajati'),
('test_Agenti'),
('test_Sedii')

INSERT INTO TestTables(TestID, TableID, NoOfRows, Position)
VALUES(1, 3, 2000, 1),
(2, 1, 2000, 2),
(3, 2, 2000, 3)


INSERT INTO Views(Name)
VALUES('view_MasiniAngajati'),
('view_Agenti'),
('view_Sedii')

INSERT INTO TestViews(TestID, ViewID)
VALUES(1, 1),
(2, 2),
(3, 3)


CREATE VIEW view_Sedii AS
SELECT * FROM Sedii;

CREATE VIEW view_Agenti AS
SELECT * FROM Agenti;

CREATE VIEW view_MasiniAngajati AS
SELECT * FROM MasiniAngajati;

CREATE OR ALTER PROCEDURE TestBD
AS
BEGIN
DECLARE @id_test INT, @descriere NVARCHAR(2000), @nume_tabel NVARCHAR(50), @noOfRows INT;
DECLARE @id_view INT, @nume_view NVARCHAR(50), @id_tabel INT;
DECLARE @sqlDELETE VARCHAR(50), @sqlINSERT VARCHAR(50), @sqlView VARCHAR(50);
DECLARE @testRunId INT;

	SET NOCOUNT ON;

	DECLARE testCursor CURSOR FOR
	SELECT TestID, Name FROM Tests

	OPEN testCursor
	FETCH NEXT FROM testCursor INTO @id_test, @descriere;
	--pentru fiecare test, sterg date din tabele, inserez si testez view urile

	WHILE @@FETCH_STATUS = 0
	BEGIN
		--salvez timpul initial inainte de executia operatiilor
		INSERT INTO TestRuns (Description, StartAt)
		VALUES (@descriere, GETDATE())
		SET @testRunId = @@IDENTITY;
		
		--Tabele
		--voi parcurge fiecare tabel din test
		DECLARE tableCursor CURSOR SCROLL FOR
		SELECT Name, T.TableID, NoOfRows
		FROM TestTables TT INNER JOIN Tables T
		ON TT.TableID = T.TableID
		WHERE TT.TestID = @id_test
		ORDER BY Position

		OPEN tableCursor;
		--DELETE-urile
		FETCH NEXT FROM tableCursor INTO @nume_tabel, @id_tabel, @noOfRows;

		WHILE @@FETCH_STATUS = 0
		BEGIN
			SET @sqlDELETE = 'DELETE FROM ' + @nume_tabel;
			PRINT @sqlDELETE
			EXEC (@sqlDELETE);

			FETCH NEXT FROM tableCursor INTO @nume_tabel, @id_tabel, @noOfRows;
		END

		--INSERT-urile

		FETCH PRIOR FROM tableCursor INTO @nume_tabel, @id_tabel, @noOfRows;
		WHILE @@FETCH_STATUS=0
		BEGIN
			--salvez timpul inainte de executie
			
			INSERT INTO TestRunTables (TestRunID, TableID, StartAt, ENDAt)
			VALUES (@testRunId, @id_tabel, GETDATE(), GETDATE());

			SET @sqlINSERT = 'Insert' + @nume_tabel;
			PRINT @sqlINSERT
			EXEC @sqlINSERT @noOfRows;
			
			
			--salvez timpul dupa executie
			UPDATE TestRunTables
			SET ENDAt = GETDATE()
			WHERE TestRunID = @testRunId AND TableID = @id_tabel;

			FETCH PRIOR FROM tableCursor INTO @nume_tabel, @id_tabel, @noOfRows;
		END

		CLOSE tableCursor;
		DEALLOCATE tableCursor;

		--view-uri
		--iau fiecare view din fiecare test
		DECLARE viewCursor CURSOR for
		SELECT TV.ViewID, Name
		FROM TestViews TV INNER JOIN Views V
		ON TV.ViewID = V.ViewID
		WHERE TV.TestID = @id_test

		OPEN viewCursor;
		FETCH NEXT FROM viewCursor INTO @id_view, @nume_view;

		WHILE @@FETCH_STATUS=0
		BEGIN
			--salvez timpul inainte de executie

			INSERT INTO TestRunViews (TestRunID, ViewID, StartAt, ENDAt)
			VALUES (@testRunId, @id_view, GETDATE(), GETDATE());

			SET @sqlView = 'SELECT * FROM ' + @nume_view;
			PRINT @sqlView
			EXEC (@sqlView);
			
			EXEC ResetDB
			--salvez timpul dupa executie
			UPDATE TestRunViews
			SET ENDAt = GETDATE() 
			WHERE TestRunID = @testRunId AND ViewID = @id_view;

			FETCH NEXT FROM viewCursor INTO @id_view, @nume_view;
		END

		CLOSE viewCursor;
		DEALLOCATE viewCursor;
		--salvez timpul final/test (dupa stergere, inserare, executie view-uri)
		UPDATE TestRuns
		SET ENDAt = GETDATE()
		WHERE TestRunID = @testRunId;

		FETCH NEXT FROM testCursor INTO @id_test, @descriere;
	END
	

	CLOSE testCursor;
	DEALLOCATE testCursor;

	SET NOCOUNT OFF;

END 
GO

EXEC TestBD

SELECT * FROM TestRuns
SELECT * FROM TestRunTables
SELECT * FROM TestRunViews
