CREATE DATABASE Politie
USE Politie
GO

CREATE Table Sectie(
	id INT PRIMARY KEY IDENTITY(1,1),
	denumire varchar(30),
	adresa varchar(70)
)

CREATE TABLE Grade(
	id INT PRIMARY KEY IDENTITY,
	denumire varchar(30)
)

CREATE TABLE Sector(
	id INT PRIMARY KEY IDENTITY,
	denumire varchar(30)
)

CREATE TABLE Politist(
	id INT PRIMARY KEY IDENTITY,
	nume varchar(30),
	prenume varchar(30),
	id_sectie INT FOREIGN KEY REFERENCES Sectie(id),
	id_grad INT FOREIGN KEY REFERENCES Grade(id)
)

CREATE TABLE Patrula(
	idPatrula INT PRIMARY KEY IDENTITY,
	idPolitist INT FOREIGN KEY REFERENCES Politist(id),
	idSector INT FOREIGN KEY REFERENCES Sector(id),
	inceput datetime,
	sfarsit datetime
)


insert into Sector values('sector 1')
insert into Sector values('sector 2')
insert into Sector values('sector 3')
insert into Sector values('sector 4')
insert into Sector values('sector 5')

insert into Grade values('officer')
insert into Grade values('sheriff')
insert into Grade values('detective')
insert into Grade values('swat')

insert into Sectie values('station 1', 'asdsad')
insert into Sectie values('station 2', 'asdsad')
insert into Sectie values('station 3', 'asdsad')
insert into Sectie values('station 4', 'asdsad')
insert into Sectie values('station 5', 'asdsad')

insert into Politist values('Bob', 'Bob',1,1)
insert into Politist values('George', 'Bobert', 2,2)
insert into Politist values('John', 'Wick', 3,3)
insert into Politist values('Bobish', 'Zack', 4,4)

insert into Patrula values(1,1,'2022-09-09 00:00:00', '2022-09-09 12:00:00')
insert into Patrula values(2,2,'2022-05-05 10:30:00', '2022-05-05 12:00:00')
insert into Patrula values(3,3,'2022-09-09 00:00:00', '2022-09-09 12:00:00')
insert into Patrula values(4,4,'2022-10-10 00:00:00', '2022-10-10 04:30:00')

CREATE OR ALTER PROCEDURE Schedule
	@nume varchar(50),
	@prenume varchar(50),
	@numesectie varchar(50),
	@entry datetime,
	@exit datetime
as
begin
	if exists(select * from Patrula P INNER JOIN Politist o on o.id = p.idPolitist
			where p.inceput = @entry and o.nume = @nume and o.prenume = @prenume)
	begin
		update Patrula SET sfarsit = @exit where inceput = @entry
	end
	else
	begin
		declare @idS int =(select id from Sectie where denumire = @numesectie)
		declare @idP int= (select id from Politist o where o.nume = @nume and o.prenume = @prenume)
		insert into Patrula values(@idP, @idP, @entry, @exit)
		print 'added succesfully'
	end
end

exec Schedule 'Bob', 'Bob', 'sector 3', '2022-10-10 00:00:00', '2022-10-10 04:30:00'

create or alter view ex3 as
	select top (select count(*) from Patrula) p.idPolitist, o.nume, o.prenume, s.denumire, sum(DATEDIFF(hour, inceput, sfarsit)) as nr_ore
	from Patrula p inner join Politist o on p.idPolitist = o.id
	inner join Sectie s on s.id = o.id_sectie
	where month(inceput) = 1 and year(inceput) = year(getdate())
	group by p.idPolitist, nume, prenume, s.denumire
	order by s.denumire, o.nume, o.prenume asc

insert into Patrula values(1,5,'2025-01-01 00:00:00', '2025-01-01 04:30:00')
insert into Patrula values(1,1,'2025-01-01 00:00:00', '2025-01-01 04:30:00')
insert into Patrula values(2,1,'2025-01-01 00:00:00', '2025-01-01 04:30:00')
insert into Patrula values(2,2,'2025-01-01 00:00:00', '2025-01-01 04:30:00')
insert into Patrula values(2,3,'2025-01-01 00:00:00', '2025-01-01 04:30:00')

select * from ex3

