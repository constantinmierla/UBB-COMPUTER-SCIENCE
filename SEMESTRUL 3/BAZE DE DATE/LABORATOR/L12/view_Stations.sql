USE CFR;
GO
-- crearea unui view pentru statiile din orase cu nume care incep cu 'C'
SELECT * FROM vw_stations_name

SELECT * FROM Stations

CREATE OR ALTER VIEW vw_stations_name AS
SELECT 
    id_st, 
    nameS
FROM Stations
WHERE LEFT(nameS, 1) = 'G';
GO

-- crearea unui index neclusterizat pe coloana nameS din tabela Stations
CREATE NONCLUSTERED INDEX idx_nameS
ON Stations (nameS);
GO

-- crearea unui index neclusterizat pe coloanele id_city si nameS pentru interogari combinate
CREATE NONCLUSTERED INDEX idx_id_nameS
ON Stations (id_city, nameS);
GO