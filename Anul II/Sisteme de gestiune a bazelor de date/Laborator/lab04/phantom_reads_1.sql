USE DiebmannImobiliare

BEGIN TRAN
WAITFOR DELAY '00:00:10'
INSERT INTO Agenti VALUES (2, 'Phantom', 'Phantom', 'Phantom')
COMMIT TRAN

DELETE FROM Agenti where nume = 'Phantom'