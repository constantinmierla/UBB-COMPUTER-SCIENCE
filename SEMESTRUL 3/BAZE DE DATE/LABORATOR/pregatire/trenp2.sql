create database trenp2
use trenp2
go
create table Tiptren(
	id_tip INT PRIMARY KEY IDENTITY,
	descriere varchar(70)
)

create table Tren(
	id_tren INT PRIMARY KEY IDENTITY,
	nume varchar(30),
	id_tip INT FOREIGN KEY REFERENCES Tiptren(id_tip)
)

create table Statie(
	id_statie INT PRIMARY KEY IDENTITY,
	nume varchar(30)
)

create table Rute(
	id_ruta INT PRIMARY KEY IDENTITY,
	nume varchar(30),
	id_tren INT FOREIGN KEY REFERENCES Tren(id_tren)
)

create table Opriri(
	id_ruta INT FOREIGN KEY REFERENCES Rute(id_ruta),
	id_statie INT FOREIGN KEY REFERENCES Statie(id_statie),
	ora_sosire TIME,
	ora_plecare TIME,
	CONSTRAINT PK_Opriri PRIMARY KEY(id_ruta, id_statie)
);

insert into Tiptren values ('de muzeu'), ('de calatori'), ('marfar');
insert into Tren values ('Thomas', 1), ('Johnny', 2),('Magnus',2),('Fritz',3),('BigShow',3),('Jordi',1);
insert into Statie values ('Cluj Nord'), ('Cluj Est'), ('Bistrita Nord'), ('Dej Calatori');
insert into Rute values('Bistrita-Cluj', 1), ('Suceava-Dej', 2), ('Cluj-Bistrita', 3), ('Dej-Cluj', 4);
INSERT INTO Opriri VALUES
    (2,1,'10:10','10:15'),(2,2,'12:15','12:47'),(2,3,'9:00','11:15'),(2,4,'7:45','10:11'),(3,3,'15:21','16:22'),(3,4,'12:15','12:16'),(3,2,'11:05','12:00');

CREATE OR ALTER PROCEDURE adauga_statie @idRuta INT, @idStatie INT, @oraSosire TIME, @oraPlecare TIME
AS
BEGIN
	IF(EXISTS(SELECT * FROM Opriri WHERE id_statie = @idStatie and id_ruta = @idRuta))
	BEGIN
		UPDATE Opriri
		SET ora_plecare = @oraPlecare, ora_sosire = @oraSosire
		WHERE id_ruta = @idRuta AND id_statie = @idStatie
		PRINT 'Oprirea a fost modificata cu succes!'
	END
	ELSE
	BEGIN
		INSERT INTO Opriri VALUES(@idRuta, @idStatie, @oraSosire, @oraPlecare)
		PRINT 'Oprirea a fost adaugata cu succes!'
	END
END

EXEC adauga_statie 2, 1, '11:30', '13:40'

SELECT * FROM Opriri

CREATE VIEW afiseaza AS
SELECT nume FROM Rute R INNER JOIN Opriri O ON R.id_ruta = O.id_ruta
GROUP BY R.id_ruta, R.nume
HAVING COUNT(*) = (SELECT COUNT(*) FROM Statie)

select * from afiseaza

