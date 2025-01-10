create database Practic
use Practic
go

-- 1.
CREATE TABLE Muzee (
    id_muzeu INT PRIMARY KEY IDENTITY,
    denumire VARCHAR(100) NOT NULL,
    an_datare INT,
    oras VARCHAR(100),
    tara VARCHAR(100)
);

CREATE TABLE Artefacte (
    id_artefact INT PRIMARY KEY IDENTITY,
    denumire VARCHAR(100) NOT NULL,
    descriere VARCHAR(255),
    an_datare INT,
    id_muzeu INT FOREIGN KEY REFERENCES Muzee(id_muzeu)
);

CREATE TABLE Tururi (
    id_tur INT PRIMARY KEY IDENTITY,
    denumire VARCHAR(100) NOT NULL,
    zi VARCHAR(20),
    data DATE,
    ora_acces TIME,
    nume_ghid VARCHAR(100),
    pret_bilet DECIMAL(10,2),
    id_muzeu INT FOREIGN KEY REFERENCES Muzee(id_muzeu)
);

CREATE TABLE Turisti (
    id_turist INT PRIMARY KEY IDENTITY,
    nume VARCHAR(100),
    prenume VARCHAR(100),
    gen CHAR(1),
    varsta INT
);

CREATE TABLE Participari (
    id_turist INT FOREIGN KEY REFERENCES Turisti(id_turist),
    id_tur INT FOREIGN KEY REFERENCES Tururi(id_tur),
    numar_bilete INT,
    numar_stele INT,
    CONSTRAINT PK_Participari PRIMARY KEY (id_turist, id_tur)
);

-- 2.
CREATE OR ALTER PROCEDURE AdaugaPart
    @id_turist INT,
    @id_tur INT,
    @numar_bilete INT,
    @numar_stele INT
AS
BEGIN
    IF EXISTS (SELECT * FROM Participari WHERE id_turist = @id_turist AND id_tur = @id_tur)
    BEGIN
        UPDATE Participari
        SET numar_bilete = @numar_bilete, numar_stele = @numar_stele
        WHERE id_turist = @id_turist AND id_tur = @id_tur;
        PRINT 'S-a actualizat';
    END
    ELSE
    BEGIN
        INSERT INTO Participari (id_turist, id_tur, numar_bilete, numar_stele)
        VALUES (@id_turist, @id_tur, @numar_bilete, @numar_stele);
        PRINT 'S-a adaugat';
    END
END;

SELECT * FROM Turisti
SELECT * FROM Tururi
SELECT * FROM Participari

EXEC AdaugaPart
    @id_turist = 4,
    @id_tur = 2,
    @numar_bilete = 1,
    @numar_stele = 1;

--3.
CREATE OR ALTER FUNCTION TuristiDevotati(@n INT)
RETURNS TABLE
AS
RETURN
(
    SELECT T.nume, T.prenume, COUNT(P.id_tur) AS numar_tururi
    FROM Turisti T
    INNER JOIN Participari P ON T.id_turist = P.id_turist
    GROUP BY T.nume, T.prenume
    HAVING COUNT(P.id_tur) >= @n
);

SELECT * FROM TuristiDevotati(2);


INSERT INTO Muzee (denumire, an_datare, oras, tara) VALUES
('Muzeul Satului', 2010, 'Suceava', 'Romania'),
('Muzeul de Istorie', 2000, 'Suceava', 'Romania'),
('Muzeul de Traditii', 1936, 'Cluj-Napoca', 'Romania');

INSERT INTO Artefacte (denumire, descriere, an_datare, id_muzeu) VALUES
('Ie', 'Foarte frumoasa', 1900, 1),
('Pictura Medievala', 'E veche', 1400, 2),
('Casa Traditionala', 'O casa veche', 1850, 3);

INSERT INTO Tururi (denumire, zi, data, ora_acces, nume_ghid, pret_bilet, id_muzeu) VALUES
('Descopera istoria Romaniei', 'Luni', '2025-05-10', '10:00', 'Ion Popescu', 30.00, 1),
('Tur de arta medievala', 'Marti', '2025-05-11', '12:00', 'Maria Ionescu', 40.00, 2),
('Traditii si obiceiuri', 'Miercuri', '2025-05-12', '15:00', 'Alexandru Vasile', 20.00, 3);

INSERT INTO Turisti (nume, prenume, gen, varsta) VALUES
('Popescu', 'Ioana', 'F', 28),
('Ionescu', 'Dan', 'M', 35),
('Dumitrescu', 'Elena', 'F', 40);

INSERT INTO Turisti(nume, prenume, gen, varsta) VALUES
('Plaiu', 'Rares', 'M', 20),
('Oanea', 'Raul', 'M', 19);

INSERT INTO Participari (id_turist, id_tur, numar_bilete, numar_stele) VALUES
(1, 1, 2, 5),
(2, 2, 1, 4),
(3, 3, 3, 5);
