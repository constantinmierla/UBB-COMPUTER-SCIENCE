USE CFR;
GO

-- Select pe un tabel --
CREATE VIEW VW_Drivers
AS
    SELECT 
        id_driver, 
        nameP AS Nume, 
        birthdate AS DataNastere,
        height AS Inaltime,
        weight AS Greutate,
        gender AS Gen
    FROM Drivers;
GO

-- Select pe doua tabele --
CREATE VIEW VW_TrainsStations
AS
    SELECT 
        Routes.duration AS Durata,
		Stations.nameS as StatiePlecare
    FROM Routes
    INNER JOIN Stations ON Routes.id_from = Stations.id_st;
GO

-- Select pe doua tabele + Group By --
CREATE VIEW VW_RoutesSummary
AS
SELECT 
    Cities.nameCi AS Oras,
    COUNT(DISTINCT Routes.id_route) AS NrRute,
    MIN(Routes.duration) AS DurataMinima,
    MAX(Routes.duration) AS DurataMaxima
FROM 
    Routes
JOIN 
    Stations ON Routes.id_from = Stations.id_st
JOIN 
    Cities ON Stations.id_city = Cities.id
GROUP BY 
    Cities.nameCi;
GO
