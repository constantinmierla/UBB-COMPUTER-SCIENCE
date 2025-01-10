USE CFR;
GO

-- Inserare tabele de test in dbo.Tables
INSERT INTO dbo.Tables (Name) VALUES
('TestPassengers'),         -- tabel doar cu cheie primara
('TestDepartures'),         -- tabel cu cheie primara si cheie străină
('TestTickets');            -- tabel cu cheie primara compusă

-- Inserare views corespunzatoare
INSERT INTO Views (Name) VALUES
('VW_Drivers'),              -- SELECT pe o tabela
('VW_TrainsStations'),     -- SELECT pe doua tabele
('VW_RoutesSummary');        -- SELECT pe doua tabele + GROUP BY

-- Inserare test principal
INSERT INTO Tests (Name) VALUES ('Main');

-- Verificare tabele si view-uri inserate
SELECT * FROM dbo.Tables;
SELECT * FROM dbo.Views;

-- Mapare intre test si view-uri
INSERT INTO dbo.TestViews (TestID, ViewID) VALUES
(1, 1),  -- Testul 'Main' include VW_Soferi
(1, 2),  -- Testul 'Main' include VW_CamioaneRemorci
(1, 3);  -- Testul 'Main' include VW_CursePeMarca

-- Mapare între test si tabele
INSERT INTO dbo.TestTables (TestID, TableID, Position, NoOfRows) VALUES
(1, 3, 1, 10),  -- Testul 'Main', tabelul TestTickets, pozitia 1
(1, 2, 2, 10),  -- Testul 'Main', tabelul TestDepartures, pozitia 2
(1, 1, 3, 10);  -- Testul 'Main', tabelul TestPassengers, pozitia 3

SELECT * FROM dbo.TestViews
SELECT * FROM dbo.TestTables

SELECT * FROM dbo.Tests