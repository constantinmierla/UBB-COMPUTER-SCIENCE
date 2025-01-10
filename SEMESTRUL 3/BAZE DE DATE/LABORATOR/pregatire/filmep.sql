create database filme
use filme
go

create table Tari(
	id_tara INT PRIMARY KEY IDENTITY,
	nume varchar(50)
)
create table TipFilme(
	id_tip INT PRIMARY KEY IDENTITY
)
create or alter view afiseaza as
select * from Actori A inner join Actori_filme AF ON A.id_actor = AF.id_actor
GROUP BY A.nume
HAVING COUNT(AF.id_film) > 3

create or alter procedure filmeinchiriate
as begin
	select *
	FROM Filme F
	WHERE F.i_film NOT IN (
		SELECT DISTINCT I.id_film
		FROM Inchirieri I)
	end
