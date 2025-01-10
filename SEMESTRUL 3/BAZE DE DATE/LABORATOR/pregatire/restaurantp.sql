create database restaurantp
use restaurantp
go

create table TipRestaurant(
	id_tip INT PRIMARY KEY IDENTITY,
	nume varchar(40),
	descriere varchar(70)
)

create table Oras(
	id_oras INT PRIMARY KEY IDENTITY,
	nume varchar(40)
)

create table Restaurant(
	id_rest INT PRIMARY KEY IDENTITY,
	id_oras INT FOREIGN KEY REFERENCES Oras(id_oras),
	id_tip INT FOREIGN KEY REFERENCES TipRestaurant(id_tip),
	nume varchar(40),
	adresa varchar(40),
	telefon varchar(40)
)

create table Utilizator(
	id_user INT PRIMARY KEY IDENTITY,
	nume varchar(40),
	adresa varchar(40),
	parola varchar(20)
)

create table Note(
	id_user INT,
	id_rest INT,
	nota FLOAT,
	CONSTRAINT FK_Note_Utilizator FOREIGN KEY(id_user) REFERENCES Utilizator(id_user),
	CONSTRAINT FK_Note_Restaurant FOREIGN KEY(id_rest) REFERENCES Restaurant(id_rest),
	CONSTRAINT PK_NOTE PRIMARY KEY(id_user, id_rest)
)
select * from Restaurant
INSERT INTO TipRestaurant VALUES
    ('t1','Chinezesc'),('t2','Romanesc'),('t3','Italian'),('t4','Coreean'),('t5','FastFood');

INSERT INTO Oras VALUES
    ('Bistrita'),('Cluj'),('Craiova'),('Bucuresti'),('Suceava'),('Dej');

INSERT INTO Restaurant VALUES
    (1,5,'KFC','strada libertatii','0763196245'),
    (2,5,'MC','strada libertatii','0763196245'),
    (3,1,'Madona','strada libertatii','0763196245'),
    (4,2,'Spartan','strada libertatii','0763196245'),
    (5,3,'Friday','strada libertatii','0763196245');

INSERT INTO Utilizator VALUES
    ('Paul','default@gmail.com','123'),
    ('Denis','default@gmail.com','123'),
    ('Alex','default@gmail.com','123'),
    ('Ionut','default@gmail.com','123'),
    ('Florina','default@gmail.com','123');

INSERT INTO Note VALUES
    (1,2,10),(2,2,10),(3,3,9),(1,3,7);

CREATE OR ALTER PROCEDURE adauga_nota
	@id_user INT,
	@id_rest INT,
	@nota FLOAT
AS
BEGIN
	IF (EXISTS(SELECT * FROM Note WHERE id_user = @id_user AND id_rest = @id_rest))
	BEGIN
	UPDATE Note
	SET nota = @nota
	WHERE id_user = @id_user AND id_rest = @id_rest
	PRINT 'S-A MODIFICAT'
	END
	ELSE
	BEGIN
	INSERT INTO Note VALUES(@id_user, @id_rest, @nota)
	PRINT 'S-A ADAUGAT'
	END
END

EXEC adauga_nota 1,2,10

SELECT * FROM Note

CREATE OR ALTER FUNCTION Afiseaza(@email VARCHAR(100))
RETURNS TABLE
AS
	RETURN SELECT T.nume as numeTip, R.nume as numeRes, R.telefon as numeTel, O.nume as numeOras, N.nota as numeNota, U.nume as numeUser, U.adresa as numeAdresa
	FROM Utilizator U INNER JOIN Note N ON U.id_user = N.id_user
	INNER JOIN Restaurant R ON R.id_rest = N.id_rest
	INNER JOIN Oras O ON O.id_oras = R.id_oras
	INNER JOIN TipRestaurant T ON R.id_tip = T.id_tip
	WHERE U.adresa = @email;

SELECT * FROM Afiseaza('default@gmail.com')
