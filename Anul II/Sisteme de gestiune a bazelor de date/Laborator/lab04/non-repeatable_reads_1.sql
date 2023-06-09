USE DiebmannImobiliare


INSERT INTO Agenti VALUES (2, 'TestAgenti', 'TestAgenti', 'TestAgenti')

BEGIN TRAN
WAITFOR DELAY '00:00:10'
UPDATE Agenti SET nume = 'Modificat' where nume = 'TestAgenti'
COMMIT TRAN


DELETE FROM Agenti where nume = 'Modificat'
SELECT * FROM Agenti