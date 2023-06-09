USE DiebmannImobiliare

BEGIN TRANSACTION

	UPDATE Agenti SET
	nume = 'DirtyRead' where idAgent = 2
	WAITFOR DELAY '00:00:7'

ROLLBACK TRANSACTION