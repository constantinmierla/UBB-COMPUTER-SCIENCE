USE CFR;
GO

-- Procedura pentru modificarea tipului coloanei 'price' in tabelul 'Departures' la FLOAT
CREATE PROCEDURE ModificareTipColoane
AS
BEGIN
    ALTER TABLE Departures
    ALTER COLUMN price FLOAT;
END
GO

-- Procedura pentru adaugarea unei constrangeri de valoare implicita de 1 pentru coloana 'comfort_level' in tabelul 'Routes'
CREATE PROCEDURE AdaugareConstrangereValoareImplicita
AS
BEGIN
    ALTER TABLE Routes
    ADD CONSTRAINT DF_ComfortLevel_Implicit DEFAULT 1 FOR comfort_level;
END
GO


-- Procedura pentru crearea unei noi tabele 'EvaluariTrenuri' cu coloane pentru evaluarea trenurilor
CREATE PROCEDURE CreeareTabelEvaluariTrenuri
AS
BEGIN
	CREATE TABLE EvaluariTrenuri (
        EvaluareID INT PRIMARY KEY IDENTITY,
        id_tr INT NOT NULL FOREIGN KEY REFERENCES Trains(id_tr),
        DataEvaluare DATE NOT NULL,
        Scor INT CHECK (Scor BETWEEN 1 AND 10),
        Feedback VARCHAR(255)
    );
END
GO

-- Procedura pentru adaugarea unui camp 'Observatii' in tabelul 'Drivers' pentru comentarii suplimentare
CREATE PROCEDURE AdaugaCampObservatiiDrivers
AS
BEGIN
    ALTER TABLE Drivers
    ADD Observatii VARCHAR(255);
END
GO

-- Procedura pentru adaugarea unei constrangeri de cheie straina intre 'Stations' si 'Cities'
CREATE PROCEDURE AdaugaCheieStrainaStationsCities
AS
BEGIN
    ALTER TABLE Stations
    ADD CONSTRAINT FK_Stations_Cities
    FOREIGN KEY (id_city) REFERENCES Cities(id);
END
GO

