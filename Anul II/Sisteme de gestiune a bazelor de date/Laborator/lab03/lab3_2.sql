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


CREATE OR ALTER PROCEDURE AddTeren
		@tip varchar(100) as
begin 
begin tran

	begin try
		--- validari texte
		if dbo.validare_Text(@tip) <> 1
			begin 
				print 'Tip valid'
				raiserror('Tip invalid',14,1);
			end
		

		INSERT INTO Terenuri(tipTeren)
		values 
		(@tip);

		print 'Teren adaugat'

		commit tran
		print 'Transaction committed'
	end try

	begin catch
		rollback tran
		print ERROR_MESSAGE(); 
		print 'Transaction rollbacked'
		return 0
	end catch

	return 1
end

go
CREATE OR ALTER PROCEDURE AddSpatiu
	@camere int as
begin 
begin tran
	begin try

		if dbo.validare_Nr(@camere) <> 1
			begin 
				print 'Spatiu valid'
				raiserror('Spatiu invalid',14,1);
			end
	

		INSERT INTO Spatii(camere)
		values 
		(@camere);

		print 'Spatiu adaugat'

		commit tran
		print 'Transaction committed'
	end try

	begin catch
		rollback tran
		print ERROR_MESSAGE(); 
		print 'Transaction rollbacked'
		return 0
	end catch

	return 1
end

go
CREATE OR ALTER PROCEDURE AddTerenuriSpatii_2 
	@tip varchar(100), @camere int as

begin 
		
		declare @spatiu_added int;
		declare @teren_added int;

		EXEC @teren_added = AddTeren @tip
		EXECUTE @spatiu_added = AddSpatiu @camere
		
		if @teren_added <> 1
			begin
				print 'teren was not added so we can not add to TerenuriSpatii'
				return 0
			end

		if @spatiu_added <> 1
			begin
			print 'spatiu was not added so we can not add to TerenuriSpatii'
				return 0
			end

		declare @Id_Teren int;
		declare @Id_Spatiu int;

		SELECT TOP 1 @Id_Teren = T.idTeren
		FROM dbo.Terenuri as T
		WHERE T.tipTeren = @tip;

		SELECT TOP 1 @Id_Spatiu = S.idSpatiu
		FROM dbo.Spatii as S
		WHERE S.camere = @camere;

		INSERT INTO TerenuriSpatii(idTeren, idSpatiu)
		values 
		(@Id_Teren, @Id_Spatiu);

		print 'card_actual adaugat'
end

create table TerenuriSpatii(
idTeren INT,
idSpatiu INT
);

delete from TerenuriSpatii;
delete from Terenuri;
delete from Spatii;

Select * from Terenuri;
Select * from Spatii;
Select * from TerenuriSpatii;
EXECUTE AddTerenuriSpatii_2 'intravilan', 2;

Select * from Terenuri;
Select * from Spatii;
Select * from TerenuriSpatii;
EXECUTE AddTerenuriSpatii_2 '', 3;

Select * from Terenuri;
Select * from Spatii;
Select * from TerenuriSpatii;