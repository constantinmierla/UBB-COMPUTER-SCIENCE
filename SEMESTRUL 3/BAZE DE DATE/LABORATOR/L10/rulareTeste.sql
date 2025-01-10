USE CFR;
GO

-- Actualizeaza numarul de randuri pentru tabelele de testare
UPDATE TestTables SET NoOfRows = 100;

-- Executa testul principal
EXEC ExecutaTest @NumeTest = 'Main';

-- Afiseaza rezultatele testarilor
SELECT * FROM TestRuns;
SELECT * FROM TestRunTables;
SELECT * FROM TestRunViews;

-- Afiseaza continutul tabelelor de test
SELECT * FROM TestPassengers;
SELECT * FROM TestDepartures;
SELECT * FROM TestTickets;
