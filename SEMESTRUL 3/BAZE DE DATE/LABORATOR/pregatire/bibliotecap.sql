create database bibliotecap
use bibliotecap
go

create table Domenii(
	id_dom INT PRIMARY KEY IDENTITY,
	descriere varchar(30)
)
create table Librarii(
	id_lib INT PRIMARY KEY IDENTITY,
	nume varchar(50),
	adresa varchar(30)
)
create table Autor(
	id_autor INT PRIMARY KEY IDENTITY,
	nume varchar(50)
)
create table Carti(
	id_car INT PRIMARY KEY IDENTITY,
	titlu varchar(50),
	id_dom INT FOREIGN KEY REFERENCES Domenii(id_dom)
)
create table Achizitii(
	id_lib INT FOREIGN KEY REFERENCES Librarii(id_lib),
	id_car INT FOREIGN KEY REFERENCES Carti(id_car),
	data_ach DATE,
	CONSTRAINT PK_Achizitii PRIMARY KEY(id_lib, id_car)
)
create table Realizari(
	id_car INT FOREIGN KEY REFERENCES Carti(id_car),
	id_autor INT FOREIGN KEY REFERENCES Autor(id_autor),
	CONSTRAINT PK_Realizari PRIMARY KEY(id_car, id_autor)
)


create or alter procedure asociaza_autor
	@nume varchar(50),
	@titlu varchar(50)
AS
BEGIN
	declare @id_autor int = (SELECT id_autor FROM Autor WHERE nume = @nume)
	declare @id_car int = (SELECT id_car FROM Carti WHERE titlu = @titlu)
	IF @id_autor is null
	BEGIN
		INSERT INTO Autor values(@nume)
		declare @id_autnou int = (SELECT TOP 1 id_autor FROM Autor order by id_autor desc)
		insert into Realizari VALUES(@id_car, @id_autnou)
		PRINT 'Adaugat autor nou la carte'
	END
	ELSE
	BEGIN
		IF EXISTS(SELECT * FROM Realizari WHERE id_autor = @id_autor AND id_car = @id_car)
		BEGIN
			PRINT 'DEJA EXISTA ACEST AUTOR ASOCIAT ACESTEI CARTI' 
		END
		ELSE
			BEGIN
				INSERT INTO Realizari Values(@id_car, @id_autor)
				PRINT 'Adaugat autor vechi la carte'
			END
	END
END

exec asociaza_autor 'costi', 'ion'

CREATE OR ALTER VIEW carti_cumparate as
select L.nume as numeLibrarie, count(*) as cartiCumparate from Carti C
inner join Achizitii A on C.id_car = A.id_car
inner join Librarii L on A.id_lib = L.id_lib
where A.data_ach >= '2010-01-01'
GROUP BY A.id_lib, L.nume

select * from carti_cumparate


create or alter function howManyAuthors(@titlu varchar(50))
returns int
as
begin
declare @howm int=(select count(r.id_autor) from Realizari r
inner join Carti c on c.id_car=r.id_car
where c.titlu=@titlu)
return @howm
end

create or alter function afiseaza_carti(@nrautori INT)
returns table
as
	return select distinct L.nume, L.adresa, C.titlu, @nrautori as NrAutori from Librarii L
	inner join Achizitii A on A.id_lib = L.id_lib
	inner join Carti C on C.id_car = A.id_car
	inner join Realizari R on R.id_car = C.id_car
	where [dbo].howmanyauthors(C.titlu) = @nrautori

select * from afiseaza_carti(2)

insert into Domenii values('isto')
insert into Domenii values('literatura')
insert into Domenii values('psihologie')
insert into Domenii values('comedie')
insert into Domenii values('fictiune')



insert into Carti values('sadsad', 1)
insert into Carti values('ion', 2)
insert into Carti values('o scrs pierd', 4)
insert into Carti values('monte cristo', 2)
insert into Carti values('hobbitul', 5)

insert into Autor values('Dan Badea')
insert into Autor values('Liv Rebreanu')
insert into Autor values('Dan Dan')
insert into Autor values('Mircea Eliade')
insert into Autor values('George Bacovia')
insert into Autor values('Mara Bladea')

insert into Librarii values('libraria1', 'fagului 23')
insert into Librarii values('libraria2', 'somesului 25')
insert into Librarii values('libraria3', 'piata unirii 44')
insert into Librarii values('libraria4', 'eroilor 56')
insert into Librarii values('libraria5', 'aviatorilor 29')

insert into Achizitii values(1,1, '2020-05-09')
insert into Achizitii values(2,2, '2022-07-09')
insert into Achizitii values(3,3, '2023-01-09')
insert into Achizitii values(4,4, '2021-08-20')
insert into Achizitii values(5,5, '2020-05-09')

insert into Realizari values(2,2)
