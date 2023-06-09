USE DiebmannImobiliare

SET DEADLOCK_PRIORITY LOW
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE

BEGIN TRAN

UPDATE Agenti SET nume = 'Transaction 2' where idAgent = 1
WAITFOR DELAY '00:00:07'
UPDATE Sedii SET adresa = 'Transaction 1' where idSediu = 1

COMMIT TRAN