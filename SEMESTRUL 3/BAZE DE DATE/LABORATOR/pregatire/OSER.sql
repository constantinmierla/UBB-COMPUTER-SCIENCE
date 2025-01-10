CREATE DATABASE OSER
USE OSER
GO

CREATE TABLE Hala(
	id INT PRIMARY KEY IDENTITY(1,1),
	litera char not null,
	suprafata float not null
)
GO

CREATE TABLE Taraba(
	id INT PRIMARY KEY IDENTITY(1,1),
	suprafata float not null,
	numar int not null,
	id_hala int FOREIGN KEY REFERENCES Hala(id)
)
GO

CREATE TABLE CategorieProduse(
	id INT PRIMARY KEY IDENTITY(1,1),
	nume varchar(30)
)
GO

CREATE TABLE TarabeCategorii(
	idTaraba INT FOREIGN KEY REFERENCES Taraba(id),
	idCategorie INT FOREIGN KEY REFERENCES CategorieProduse(id),
	CONSTRAINT pk_tarabeCat PRIMARY KEY(idTaraba, idCategorie)
)

CREATE TABLE Produs(
	idProdus INT PRIMARY KEY IDENTITY(1,1),
	denumire varchar(30),
	pret FLOAT NOT NULL,
	idCategorie INT FOREIGN KEY REFERENCES CategorieProduse(id)
)
GO

INSERT INTO Hala(litera, suprafata) VALUES ('H', 20.5)

INSERT INTO Taraba(suprafata, numar, id_hala) VALUES (20, 10, 1)

INSERT INTO CategorieProduse(nume) VALUES ('Legume')

INSERT INTO Produs(denumire, pret, idCategorie) VALUES ('Rosii', 5, 1)

INSERT INTO TarabeCategorii(idTaraba, idCategorie) VALUES (1,1)

-- Populează tabelul Hala
INSERT INTO Hala (litera, suprafata) 
VALUES 
('A', 30.5),
('F', 40.0),
('X', 25.0),
('B', 35.5);

-- Populează tabelul Taraba
INSERT INTO Taraba (suprafata, numar, id_hala) 
VALUES 
(15, 5, 1),
(20, 8, 2),
(25, 12, 3),
(30, 10, 4);

-- Populează tabelul CategorieProduse
INSERT INTO CategorieProduse (nume) 
VALUES 
('Legume'),
('Fructe'),
('Lichide'),
('Carne'),
('Produse de panificatie');

-- Populează tabelul Produs
INSERT INTO Produs (denumire, pret, idCategorie) 
VALUES 
('Castraveti', 3, 1),
('Mar', 4, 2),
('Portocale', 6, 2),
('Apa minerala', 2, 3),
('Suc de portocale', 5, 3),
('Pui', 20, 4),
('Carne de vita', 35, 4),
('Paine', 2, 5),
('Cozonac', 15, 5);

-- Populează tabelul TarabeCategorii
INSERT INTO TarabeCategorii (idTaraba, idCategorie) 
VALUES 
(1, 2),
(2, 1),
(3, 2),
(4, 3),
(2, 4),
(3, 5),
(4, 4);


CREATE OR ALTER PROCEDURE ex2 @idTaraba INT AS
	BEGIN
		UPDATE Produs
		SET pret = CASE
			WHEN pret < 100 THEN pret + 10
			when pret > 200 THEN pret + 50
			WHEN pret >= 100 AND pret < 200 THEN 1.1 * pret
		END
		WHERE idProdus IN (
			SELECT P.idProdus
			FROM TarabeCategorii TC
			INNER JOIN CategorieProduse CP ON CP.id = TC.idCategorie
			INNER JOIN Produs P on CP.id = P.idCategorie
			WHERE TC.idTaraba = @idTaraba
		);
	END;
GO

EXEC ex2 2;

SELECT * FROM Produs
SELECT * FROM Taraba

CREATE OR ALTER VIEW view3 AS
	SELECT 
		P.denumire, 
		P.pret * 0.4 AS pret_redus,
		CP.nume AS categorie,
		T.numar AS numar_taraba,
		H.litera AS hala_litera
	FROM 
		TarabeCategorii TC
INNER JOIN CategorieProduse CP ON CP.id = TC.idCategorie
INNER JOIN Taraba T ON T.id = TC.idTaraba
INNER JOIN Hala H on H.id = T.id_hala
INNER JOIN Produs P on CP.id = P.idCategorie
WHERE
    (CP.nume = 'haine' OR CP.nume = 'vesela') 
    AND (H.litera = 'A' OR H.litera = 'F' OR H.litera = 'X');

GO


-- Setează valoarea de start a ID-ului în tabelul Taraba la 19
DBCC CHECKIDENT ('Taraba', RESEED, 19);

-- Adăugăm hale noi
INSERT INTO Hala (litera, suprafata) 
VALUES 
('A', 100),  -- Hala A
('F', 150),  -- Hala F
('X', 200);  -- Hala X

-- Adăugăm tarabe noi, care vor începe cu ID-ul 20
INSERT INTO Taraba (suprafata, numar, id_hala) 
VALUES 
(25, 20, 1),  -- Taraba 20 în hala A
(30, 21, 2),  -- Taraba 21 în hala F
(35, 22, 3);  -- Taraba 22 în hala X

-- Adăugăm categoriile de produse
INSERT INTO CategorieProduse (nume) 
VALUES 
('haine'),  -- Categoria 'haine'
('vesela');  -- Categoria 'vesela'

-- Adăugăm produse în aceste categorii
INSERT INTO Produs (denumire, pret, idCategorie) 
VALUES 
('Tricou', 50, 1),  -- Produs din categoria 'haine'
('Pantaloni', 120, 1),  -- Produs din categoria 'haine'
('Cana', 25, 2),  -- Produs din categoria 'vesela'
('Farfurie', 35, 2);  -- Produs din categoria 'vesela'

-- Asociază tarabe cu categoriile respective
INSERT INTO TarabeCategorii (idTaraba, idCategorie) 
VALUES 
(20, 1),  -- Taraba 20 cu categoria 'haine'
(21, 2),  -- Taraba 21 cu categoria 'vesela'
(22, 1);  -- Taraba 22 cu categoria 'haine'
