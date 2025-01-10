create database clinicap
use clinicap
go

create table Pacienti(
	id_pac INT PRIMARY KEY IDENTITY,
	nume varchar(30),
	prenume varchar(30),
	adresa varchar(30)
)

insert into Pacienti values ('Mierla', 'Costi', 'c@gmail.com'), ('Matei', 'Alex', 'a@gmail.com');
create table Specializari(
	id_spec INT PRIMARY KEY IDENTITY,
	denumire varchar(30)
)
insert into Specializari values('Cardiologie'), ('Oncologie');
create table Diagnostice(
	id_diag INT PRIMARY KEY IDENTITY,
	denumire varchar(30),
	descriere varchar(100)
)
insert into Diagnostice values('Cancer', 'belita treaba'), ('Raceala', 'mai rau decat cancerul')
create table Medici(
	id_medic INT PRIMARY KEY IDENTITY,
	nume varchar(30),
	prenume varchar(30),
	id_spec INT FOREIGN KEY REFERENCES Specializari(id_spec)
)
insert into Medici values('Acea', 'Daniela', 1), ('Coanea', 'Radu', 2)

create table Programari(
	id_prog INT PRIMARY KEY IDENTITY,
	id_medic INT FOREIGN KEY REFERENCES Medici(id_medic),
	id_pac INT FOREIGN KEY REFERENCES Pacienti(id_pac),
	id_diag INT FOREIGN KEY REFERENCES Diagnostice(id_diag),
	data_cons DATETIME,
	observatii varchar(100)
)

insert into Programari values(1, 1, 2, '2025-01-08 10:00:00', 'moare')
insert into Programari values(2, 2, 1, '2025-01-08 12:00:00', 'traieste')
insert into Programari values(2, 1, 2, '2025-01-08 14:00:00', 'moare de tot')


create or alter procedure adauga_programare
	@id_pac INT,
	@id_medic INT,
	@id_diag INT,
	@data_cons DATETIME,
	@observatii varchar(100)
AS
BEGIN
	IF (EXISTS(SELECT * FROM Programari WHERE @id_medic = id_medic AND @id_pac = id_pac AND DATEDIFF(DAY, data_cons, @data_cons) = 0))
	BEGIN
	UPDATE Programari
	SET id_diag = @id_diag, observatii = @observatii, data_cons = @data_cons
	WHERE @id_medic = id_medic AND @id_pac = id_pac AND DATEDIFF(DAY, data_cons, @data_cons) = 0
	PRINT 'S-A MODIFICAT'
	END
	ELSE
	BEGIN
	INSERT INTO Programari VALUES (@id_pac, @id_medic, @id_diag, @observatii, @data_cons)
	PRINT 'S-A ADAUGAT'
	END
END

EXEC adauga_programare 1,1,2, '2025-01-08 11:00:00', 'tot moare'
SELECT * FROM Programari

create or alter view afiseaza as
select M.nume as numeMedic, M.prenume as prenumeMedic, COUNT(P.id_prog) as nrConsultari
from Medici M inner join Programari P ON P.id_medic = M.id_medic
GROUP BY M.id_medic, M.nume, M.prenume
HAVING COUNT(P.id_prog) > 1

select * from afiseaza;

create or alter function mediciafiseaza(@date_prog DATETIME)
returns table
as
	return SELECT M.nume as numeMedic, M.Prenume as prenumeMedic, COUNT(P.id_prog) as consultatiiMedic 
	FROM Medici M INNER JOIN Programari P ON M.id_medic = P.id_medic 
	WHERE P.data_cons = @date_prog 
	GROUP BY M.id_medic, M.nume, M.prenume
	HAVING COUNT(P.id_prog) > 0;

select * from mediciafiseaza('2025-01-08 11:00:00')