Use DiebmannImobiliare
go


create or alter function dbo.validare_Text (@denumire varchar(50))
returns bit
as
begin 
	declare @flag bit
	set @flag = 1

	if @denumire is null or @denumire =''
		set @flag=0;
	return @flag;
end
go

create or alter function dbo.validare_Nr (@numar int)
returns bit
as
begin 
	declare @flag bit
	set @flag = 1

	if @numar = 0  
		set @flag=0;
	return @flag;
end
go



CREATE OR ALTER PROCEDURE AddTerenuriSpatii
		@tip varchar(100), @camere int as

begin 
begin tran

	begin try
		--- validari texte
		if dbo.validare_Text(@tip) <> 1
			begin 
				print 'Tip valid!'
				raiserror('Tip invalid',14,1);
			end

		if dbo.validare_Nr(@camere) <> 1
			begin 
				print 'nr camere valid!'
				raiserror('nr camere invalid',14,1);
			end
		
		

		INSERT INTO Spatii(camere)
		values 
		(@camere);

		print 'Spatiu adaugat'

		INSERT INTO Terenuri(tipTeren)
		values 
		(@tip);

		print 'Teren adaugat'

		declare @Id_Spatiu int;
		declare @Id_Teren int;

		SELECT TOP 1 @Id_Spatiu = S.idSpatiu
		FROM dbo.Spatii as S
		WHERE S.camere = @camere;

		SELECT TOP 1 @Id_Teren = T.idTeren
		FROM dbo.Terenuri as T
		WHERE T.tipTeren = @tip;

		INSERT INTO TerenuriSpatii(idTeren, idSpatiu)
		values 
		(@Id_Teren, @Id_Spatiu);

		commit tran
		select 'Transaction committed'
	end try

	begin catch
		rollback tran
		print ERROR_MESSAGE(); 
		select 'Transaction rollbacked'
	end catch
end

DELETE FROM TerenuriSpatii;
DELETE FROM Terenuri;
DELETE FROM Spatii;
Select * from Terenuri;
Select * from Spatii;
Select * from TerenuriSpatii;
EXECUTE AddTerenuriSpatii 'intravilan', 2;

Select * from Terenuri;
Select * from Spatii;
Select * from TerenuriSpatii;
EXECUTE AddTerenuriSpatii '', 3;

Select * from Terenuri;
Select * from Spatii;
Select * from TerenuriSpatii;