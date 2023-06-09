USE DiebmannImobiliare

SET DEADLOCK_PRIORITY HIGH
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE


SELECT * FROM Sedii
SELECT * FROM Agenti

BEGIN TRAN

UPDATE Sedii SET adresa = 'Transaction 1' where idSediu = 2
WAITFOR DELAY '00:00:07'
UPDATE Agenti SET nume = 'Transaction 2' where idAgent = 2

COMMIT TRAN
