CREATE DATABASE Trainsp
GO
USE Trainsp

CREATE TABLE TipuriDeTrenuri(
	id_tip INT PRIMARY KEY IDENTITY,
	descriere VARCHAR(100)
);
CREATE TABLE Trenuri(
	id_tren INT PRIMARY KEY IDENTITY,
	nume varchar(20),
	id_tip INT FOREIGN KEY REFERENCES TipuriDeTrenuri(id_tip)
);


CREATE TABLE Rute(
	id_ruta INT PRIMARY KEY IDENTITY,
	nume_ruta varchar(20),
	id_tren INT FOREIGN KEY REFERENCES Trenuri(id_tren)
);

CREATE TABLE Statii(
	id_statie INT PRIMARY KEY IDENTITY,
	nume varchar(20)
);

CREATE TABLE RuteStatii(
	id_statie INT,
	id_ruta INT,
	ora_sosire TIME,
	ora_plecarii TIME,
	CONSTRAINT fk_RuteStatii_Statii FOREIGN KEY (id_statie) REFERENCES Statii(id_statie),
	CONSTRAINT fk_RuteStatii_Rute Foreign KEY (id_ruta) REFERENCES Rute(id_ruta),
	CONSTRAINT fk_RuteStatii PRIMARY KEY (id_statie, id_ruta)
);


INSERT INTO TipuriDeTrenuri VALUES ('InterRegio'),('Regio'),('International'),('RegioExpress'),('Personal');
 
INSERT INTO Trenuri VALUES ('TrenuletulThomas',5),('Tren1',3),('Tren2',1),('Tren3',4),('Tren4',1)
 
INSERT INTO Rute VALUES ('Cluj-Sibiu', 1),('Cluj-BaiaMare', 4),('Bistria-Sibiu', 3),('Cluj-Bistrita', 2)
 
INSERT INTO Statii VALUES ('Cluj'),('Sibiu'),('BaiaMare'),('Bistrita');
 
INSERT INTO RuteStatii VALUES (1,1,'10:30','10:45'),(1,2,'14:30','14:45'),(2,1,'10:50','10:55'),(2,2,'12:30','12:45'),
(3,4,'11:10','11:12'),(3,2,'19:10','19:20'),(4,1,'17:10','17:12'),(4,4,'20:10','20:15');

--PROCEDURA
USE Trainsp
GO
CREATE PROCEDURE AdaugaRuteStatii
	@numeStatie varchar(20),
	@numeRuta varchar(20),
	@oraPlecarii time,
	@oraSosirii time
as
begin
	DECLARE @idStatie int
	DECLARE @idRuta int

	SET @idRuta = 0
	SET @idStatie = 0

	SELECT TOP 1 @idStatie = id_statie from Statii where nume = @numeStatie
	SELECT TOP 1 @idRuta = id_ruta from Rute where nume_ruta = @numeRuta

	IF (exists (SELECT * FROM RuteStatii WHERE id_statie = @idStatie and id_ruta = @idRuta))
	BEGIN
		UPDATE RuteStatii SET ora_sosire = @oraSosirii, ora_plecarii = @oraPlecarii WHERE id_statie = @idStatie and id_ruta = @idRuta
	END
	ELSE
		INSERT INTO RuteStatii(id_statie,id_ruta,ora_sosire, ora_plecarii)
		VALUES(@idStatie, @idRuta, @oraSosirii, @oraPlecarii)
end

go
select * from Rute
select * from Statii
select * from RuteStatii
exec AdaugaRuteStatii 'Bistrita', 'Cluj-Sibiu', '11:50', '11:40'

--VIEW

CREATE VIEW viewRute AS
SELECT nume_ruta
FROM Rute R
INNER JOIN RuteStatii RS
ON R.id_ruta = RS.id_ruta
GROUP BY R.id_ruta, R.nume_ruta
HAVING COUNT(*) = (SELECT COUNT(*) FROM Statii);

SELECT * FROM viewRute

CREATE FUNCTION StatiileCuMaiMultDeUnTren(@oraVerificare TIME)
RETURNS TABLE
AS
RETURN (
	SELECT S.nume
	FROM RuteStatii RS
	INNER JOIN Statii S ON RS.id_statie = S.id_statie
	WHERE RS.ora_sosire <= @oraVerificare AND RS.ora_plecarii > @oraVerificare
	GROUP BY S.nume
	HAVING COUNT(DISTINCT RS.id_ruta) > 0
);

SELECT * FROM StatiileCuMaiMultDeUnTren('11:11');
SELECT * FROM StatiileCuMaiMultDeUnTren('19:00');