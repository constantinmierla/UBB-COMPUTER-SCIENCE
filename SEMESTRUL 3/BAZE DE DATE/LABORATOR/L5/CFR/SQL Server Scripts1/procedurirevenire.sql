USE CFR;
GO
-- Procedura pentru revenirea tipului coloanei 'price' in tabelul 'Departures' la MONEY
CREATE PROCEDURE RevenireTipColoane
AS
BEGIN
    ALTER TABLE Departures
    ALTER COLUMN price MONEY;
END
GO

-- Procedura pentru eliminarea constrangerii de valoare implicita 'DF_ComfortLevel_Implicit' din coloana 'comfort_level' in tabelul 'Routes'
CREATE PROCEDURE EliminareConstrangereValoareImplicita
AS
BEGIN
    ALTER TABLE Routes
    DROP CONSTRAINT DF_ComfortLevel_Implicit;
END
GO

-- Procedura pentru stergerea tabelei 'EvaluariTrenuri' daca aceasta exista
CREATE PROCEDURE StergereTabelEvaluariTrenuri
AS
BEGIN
    DROP TABLE IF EXISTS EvaluariTrenuri;
END
GO

-- Procedura pentru eliminarea coloanei 'Observatii' din tabelul 'Drivers'
CREATE PROCEDURE EliminareCampObservatiiDrivers
AS
BEGIN
    ALTER TABLE Drivers
    DROP COLUMN Observatii;
END
GO

-- Procedura pentru eliminarea constrangerii de cheie straina 'FK_Stations_Cities' dintre 'Stations' si 'Cities'
CREATE PROCEDURE EliminareCheieStrainaStationsCities
AS
BEGIN
    ALTER TABLE Stations
    DROP CONSTRAINT FK_Stations_Cities;
END
GO
