-- clienti - contracte - proprietati

USE DiebmannImobiliare
GO

ALTER TABLE Clienti
ADD CONSTRAINT ck_clientNume CHECK( LEN(nume) > 2 )

ALTER TABLE Clienti
ADD CONSTRAINT ck_clientTelefon CHECK( LEN(telefon) BETWEEN 10 AND 13 )

ALTER TABLE Contracte
ADD CONSTRAINT ck_contractLuna CHECK( lunaTranz BETWEEN 1 AND 12 )

ALTER TABLE Contracte
ADD CONSTRAINT ck_contractAn CHECK( anTranz > 2020 )

ALTER TABLE ProprietateGeneral
ADD CONSTRAINT ck_propOras CHECK( LEN(oras) > 2 )

ALTER TABLE ProprietateGeneral
ADD CONSTRAINT ck_propZona CHECK( LEN(zona) > 2 )

GO

CREATE FUNCTION dbo.ValidareClient(
	@nume VARCHAR(100),
	@telefon VARCHAR(15),
	@email VARCHAR(100)
)
RETURNS BIT
AS
BEGIN
	IF( LEN(@nume) > 2 )
	AND ( LEN(@telefon) BETWEEN 10 AND 13 )
		RETURN 1;
	RETURN 0;
END

GO

CREATE FUNCTION dbo.ValidareContract(
	@idProprietate INT,
	@idClient INT,
	@valoare INT,
	@lunaTranz INT,
	@anTranz INT,
	@tip VARCHAR(10),
	@perioada INT
)
RETURNS BIT
AS
BEGIN
	IF EXISTS( SELECT * FROM ProprietateGeneral WHERE idProprietate = @idProprietate ) 
	AND EXISTS( SELECT * FROM Clienti WHERE idClient = @idClient )
	AND ( @lunaTranz BETWEEN 1 AND 12 )
	AND ( @anTranz > 2020 )
	AND ( @tip IN ('vanzare', 'inchiriere') )
	AND ( @perioada > 5 ) 
		RETURN 1;
	RETURN 0;
END

GO

CREATE FUNCTION dbo.ValidareProprietate(
	@idProprietar INT,
	@idAgentAsignat INT,
	@tip VARCHAR(10),
	@oras VARCHAR(50),
	@zona VARCHAR(59),
	@adresa VARCHAR(200),
	@suprafata INT
)
RETURNS BIT
AS
BEGIN
	IF EXISTS( SELECT * FROM Proprietari WHERE idProprietar = @idProprietar )
	AND EXISTS( SELECT * FROM Agenti WHERE idAgent = @idAgent )
	AND ( @tip IN ('locuinta', 'spatiu', 'teren') )
	AND ( LEN(@oras) > 2 )
	AND ( LEN(@zona) > 2 )
	AND ( @suprafata > 0 )
		RETURN 1;
	RETURN 0;
END

GO

CREATE PROCEDURE ClientiCRUD(
	@option VARCHAR,
	@executionSuccess BIT OUTPUT,
	@idClientUpdateDelete INT = NULL,
	@nume VARCHAR(100) = NULL,
	@telefon VARCHAR(15) = NULL,
	@email VARCHAR(100) = NULL
)
AS
BEGIN
	IF( @option = 'CREATE' )
	BEGIN
		IF( dbo.ValidareClient(@nume, @telefon, @email) = 1)
		BEGIN
			INSERT INTO Clienti(nume, telefon, email) VALUES(@nume, @telefon, @email);
			SET @executionSuccess = 1;
		END
		ELSE BEGIN
			PRINT 'Eroare in validarea datelor clientului la creare. Reincercati!';
			SET @executionSuccess = 0;
		END
	END
	ELSE BEGIN
		IF( @option = 'READ' )
		BEGIN
			SELECT * FROM Clienti;
			SET @executionSuccess = 1;
		END
		ELSE BEGIN
			IF( @option = 'UPDATE' )
			BEGIN
				IF EXISTS( SELECT * FROM Clienti WHERE idClient = @idClientUpdateDelete )
				AND( dbo.ValidareClient(@nume, @telefon, @email) = 1 )
				BEGIN
					UPDATE Clienti 
						SET nume = @nume, telefon = @telefon, email = @email 
					WHERE idClient = @idClientUpdateDelete;
					SET @executionSuccess = 1;
				END
				ELSE BEGIN
					PRINT 'Eroare in validarea datelor clientului la update. Reincercati!';
					SET @executionSuccess = 0;
				END
			END
			ELSE BEGIN
				IF( @option = 'DELETE' )
				BEGIN
					IF EXISTS( SELECT * FROM Clienti WHERE idClient = @idClientUpdateDelete )
					BEGIN
						DELETE FROM Clienti WHERE idClient = @idClientUpdateDelete;
						SET @executionSuccess = 1;
					END
					ELSE BEGIN
						PRINT 'Clientul cu ID-ul furnizat nu exista!';
						SET @executionSuccess = 0;
					END
				END
				ELSE BEGIN
					PRINT 'Optiune invalida!';
					SET @executionSuccess = 0;
				END
			END
		END
	END
END

GO

CREATE PROCEDURE ContracteCRUD(
	@option VARCHAR,
	@executionSuccess BIT OUTPUT,
	@idContractUpdateDelete INT = NULL,
	@idProprietate INT = NULL,
	@idClient INT = NULL,
	@valoare INT = NULL,
	@lunaTranz INT = NULL,
	@anTranz INT = NULL,
	@tip VARCHAR(10) = NULL,
	@perioada INT = NULL
)
AS
BEGIN
	IF( @option = 'CREATE' )
	BEGIN
		IF( dbo.ValidareContract(@idProprietate, @idClient, @valoare, @lunaTranz, @anTranz, @tip, @perioada) = 1)
		BEGIN
			INSERT INTO Contracte(idProprietateContract, idClientContract, valoare, lunaTranz, anTranz, tip, perioada) 
				VALUES(@idProprietate, @idClient, @valoare, @lunaTranz, @anTranz, @tip, @perioada);
			SET @executionSuccess = 1;
		END
		ELSE BEGIN
			PRINT 'Eroare in validarea datelor contractului la creare. Reincercati!';
			SET @executionSuccess = 0;
		END
	END
	ELSE BEGIN
		IF( @option = 'READ' )
		BEGIN
			SELECT * FROM Contracte;
			SET @executionSuccess = 1;
		END
		ELSE BEGIN
			IF( @option = 'UPDATE' )
			BEGIN
				IF EXISTS( SELECT * FROM Contracte WHERE idContract = @idContractUpdateDelete )
				AND( dbo.ValidareContract(@idProprietate, @idClient, @valoare, @lunaTranz, @anTranz, @tip, @perioada) = 1 )
				BEGIN
					UPDATE Contracte 
						SET idProprietateContract = @idProprietate, idClientContract = @idClient, valoare = @valoare, 
							lunaTranz = @lunaTranz, anTranz = @anTranz, tip = @tip, perioada = @perioada
						WHERE idContract = @idContractUpdateDelete;
					SET @executionSuccess = 1;
				END
				ELSE BEGIN
					PRINT 'Eroare in validarea datelor contractului la update. Reincercati!';
					SET @executionSuccess = 0;
				END
			END
			ELSE BEGIN
				IF( @option = 'DELETE' )
				BEGIN
					IF EXISTS( SELECT * FROM Contracte WHERE idContract = @idContractUpdateDelete )
					BEGIN
						DELETE FROM Contracte WHERE idContract = @idContractUpdateDelete;
						SET @executionSuccess = 1;
					END
					ELSE BEGIN
						PRINT 'Contractul cu ID-ul furnizat nu exista!';
						SET @executionSuccess = 0;
					END
				END
			END
		END
	END
END

GO

CREATE PROCEDURE ProprietatiCRUD(
	@option VARCHAR,
	@executionSuccess BIT OUTPUT,
	@idProprietateUpdateDelete INT = NULL,
	@idProprietar INT = NULL,
	@idAgentAsignat INT = NULL,
	@tip VARCHAR(10) = NULL,
	@oras VARCHAR(50) = NULL,
	@zona VARCHAR(59) = NULL,
	@adresa VARCHAR(200) = NULL,
	@suprafata INT = NULL
)
AS
BEGIN
	IF( @option = 'CREATE' )
	BEGIN
		IF( dbo.ValidareProprietate(@idProprietar, @idAgentAsignat, @tip, @oras, @zona, @adresa, @suprafata) = 1 )
		BEGIN
			INSERT INTO ProprietateGeneral(idProprietar, idAgentAsignat, tip, oras, zona, adresa, suprafata) 
				VALUES(@idProprietar, @idAgentAsignat, @tip, @oras, @zona, @adresa, @suprafata);
			SET @executionSuccess = 1;
		END
		ELSE BEGIN
			PRINT 'Eroare in validarea datelor proprietatii la creare. Reincercati!';
			SET @executionSuccess = 0;
		END
	END
	ELSE BEGIN
		IF( @option = 'READ' )
		BEGIN
			SELECT * FROM ProprietateGeneral;
			SET @executionSuccess = 1;
		END
		ELSE BEGIN
			IF( @option = 'UPDATE' )
			BEGIN
				IF EXISTS( SELECT * FROM ProprietateGeneral WHERE idProprietate = @idProprietateUpdateDelete )
				AND( dbo.ValidareProprietate(@idProprietar, @idAgentAsignat, @tip, @oras, @zona, @adresa, @suprafata) = 1 )
				BEGIN
					UPDATE ProprietateGeneral 
						SET idProprietar = @idProprietar, idAgentAsignat = @idAgentAsignat, tip = @tip, 
							oras = @oras, zona = @zona, adresa = @adresa, suprafata = @suprafata
						WHERE idProprietate = @idProprietateUpdateDelete;
					SET @executionSuccess = 1;
				END
				ELSE BEGIN
					PRINT 'Eroare in validarea datelor proprietatii la update. Reincercati!';
					SET @executionSuccess = 0;
				END
			END
			ELSE BEGIN
				IF( @option = 'DELETE' )
				BEGIN
					IF EXISTS( SELECT * FROM ProprietateGeneral WHERE idProprietate = @idProprietateUpdateDelete )
					BEGIN
						DELETE FROM ProprietateGeneral WHERE idProprietate = @idProprietateUpdateDelete;
						SET @executionSuccess = 1;
					END
					ELSE BEGIN
						PRINT 'Proprietatea cu ID-ul furnizat nu exista!';
						SET @executionSuccess = 0;
					END
				END
			END
		END
	END
END

GO

DECLARE @execResult BIT
EXEC ProprietatiCRUD 'CREATE', @execResult OUTPUT, 0, 700, 2001, 'locuinta', 'Cluj-Napoca', 'Marasti', 'Str. Dambovitei nr. 10A', 60
IF @execResult=1 PRINT 'Operatiune realizata cu succes!'
ELSE PRINT 'Operatiune nerealizata: Au fost intampinate erori.'


CREATE VIEW ViewClientiContracte
AS
    SELECT cl.nume, cl.telefon, cl.email
    FROM Clienti cl
    INNER JOIN Contracte ctr ON cl.idClient = ctr.idClientContract
GO   
SELECT * FROM ViewClienti

GO

CREATE VIEW ViewPropContracte 
AS
    SELECT p.tip, p.oras, p.zona
    FROM ProprietateGeneral p
    INNER JOIN Contracte ctr ON p.idProprietate = ctr.idProprietateContract
GO
SELECT * FROM ViewPropContracte

GO

IF EXISTS (SELECT name FROM sys.indexes WHERE name = N'IndexContracte')
    DROP INDEX IndexContracte ON Contracte; 
GO
CREATE NONCLUSTERED INDEX IndexContracte ON Contracte (valoare);

GO

IF EXISTS (SELECT name FROM sys.indexes WHERE name = N'IndexProprietati')
    DROP INDEX IndexProprietati ON ProprietateGeneral; 
GO
CREATE NONCLUSTERED INDEX IndexProprietati ON ProprietateGeneral (suprafata);

GO
