USE CFR;
GO

CREATE PROCEDURE ExecutaTest @NumeTest VARCHAR(50)
AS
BEGIN
    -- Verific daca testul exista
    IF (NOT EXISTS(SELECT TestID FROM Tests WHERE Name = @NumeTest))
        RAISERROR('Testul nu exista', 16, 1);

    DECLARE @TestID INT;
    SET @TestID = (SELECT TestID FROM Tests WHERE Name = @NumeTest);

    DECLARE CursorTestTables_Asc CURSOR FAST_FORWARD FOR
        SELECT TableID, Position, NoOfRows FROM TestTables WHERE TestID = @TestID ORDER BY Position ASC;
    OPEN CursorTestTables_Asc;

    DECLARE @TableID INT, @Pos INT, @NoOfRows INT;
    DECLARE @TableName VARCHAR(50), @InsertProcedure VARCHAR(50);

    -- Creare TestRun
    DECLARE @TestRunID INT;
    INSERT INTO TestRuns (Description) VALUES ('Executia testului ' + @NumeTest);
    SET @TestRunID = @@IDENTITY;

    -- Declarare cronometre
    DECLARE @StartTime DATETIME, @EndTime DATETIME; -- Start si final total
    DECLARE @CurrentStartTime DATETIME, @CurrentEndTime DATETIME; -- Start si final pentru fiecare test in parte

    -- Stergerea datelor din tabele
    FETCH NEXT FROM CursorTestTables_Asc INTO @TableID, @Pos, @NoOfRows;
    WHILE @@FETCH_STATUS = 0
    BEGIN
        SET @TableName = (SELECT Name FROM Tables WHERE TableID = @TableID);
        EXEC('DELETE FROM ' + @TableName);

        FETCH NEXT FROM CursorTestTables_Asc INTO @TableID, @Pos, @NoOfRows;
    END;
    CLOSE CursorTestTables_Asc;
    DEALLOCATE CursorTestTables_Asc;

    DECLARE CursorTestTables_Desc CURSOR FAST_FORWARD FOR
        SELECT TableID, Position, NoOfRows FROM TestTables WHERE TestID = @TestID ORDER BY Position DESC;
    OPEN CursorTestTables_Desc;

    SET @StartTime = GETDATE();

    -- Inserarea datelor in tabele
    FETCH NEXT FROM CursorTestTables_Desc INTO @TableID, @Pos, @NoOfRows;
    WHILE @@FETCH_STATUS = 0
    BEGIN
        SET @TableName = (SELECT Name FROM Tables WHERE TableID = @TableID);
        SET @InsertProcedure = @TableName + '_Inserari';

        SET @CurrentStartTime = GETDATE();
        EXEC @InsertProcedure @NoOfRows;
        SET @CurrentEndTime = GETDATE();

        INSERT INTO TestRunTables (TestRunID, TableID, StartAt, EndAt)
        VALUES (@TestRunID, @TableID, @CurrentStartTime, @CurrentEndTime);

        FETCH NEXT FROM CursorTestTables_Desc INTO @TableID, @Pos, @NoOfRows;
    END;

    CLOSE CursorTestTables_Desc;
    DEALLOCATE CursorTestTables_Desc;

    -- Testare view-uri
    DECLARE CursorTestViews CURSOR FAST_FORWARD FOR
        SELECT ViewID FROM TestViews WHERE TestID = @TestID;
    OPEN CursorTestViews;

    DECLARE @ViewID INT, @ViewName VARCHAR(50);

    FETCH NEXT FROM CursorTestViews INTO @ViewID;
    WHILE @@FETCH_STATUS = 0
    BEGIN
        SET @ViewName = (SELECT Name FROM Views WHERE ViewID = @ViewID);

        SET @CurrentStartTime = GETDATE();
        EXEC('SELECT * FROM ' + @ViewName);
        SET @CurrentEndTime = GETDATE();

        INSERT INTO TestRunViews (TestRunID, ViewID, StartAt, EndAt)
        VALUES (@TestRunID, @ViewID, @CurrentStartTime, @CurrentEndTime);

        FETCH NEXT FROM CursorTestViews INTO @ViewID;
    END;

    SET @EndTime = GETDATE();

    -- Setez timpul pentru intreg testul
    UPDATE TestRuns SET StartAt = @StartTime, EndAt = @EndTime WHERE TestRunID = @TestRunID;

    CLOSE CursorTestViews;
    DEALLOCATE CursorTestViews;
END;
GO
USE CFR;
GO
CREATE PROCEDURE TestPassengers_Inserari @NoOfRows INT
AS
BEGIN
    DECLARE @Num INT;
    SET @Num = 1;
	DECLARE @
    WHILE @Num <= @NoOfRows
    BEGIN
        INSERT INTO TestPassengers (name_test_pas, age, gender)
        VALUES 
        (
            'Pasager' + CAST(@Num AS VARCHAR(10)), -- Numele pasagerului, generat dinamic
            20 + (@Num % 50),                    -- Varsta intre 20 si 69 (pentru diversitate)
            @Num % 2                             -- Gender: 0 (Femeie) sau 1 (Barbat)
        );

        SET @Num += 1;
    END;
END;
GO

USE CFR;
GO
CREATE OR ALTER PROCEDURE TestDepartures_Inserari @NoOfRows INT
AS
BEGIN
    DECLARE @Num INT;
    SET @Num = 1;
	DECLARE @Tid INT;
	SET @Tid = (SELECT MIN(id_tr) FROM Trains);
    WHILE @Num <= @NoOfRows
    BEGIN
        INSERT INTO TestDepartures (id_test_route, id_test_train, departure_time, price)
        VALUES 
        (
            (@Num % 10) + 1,                             -- id_test_route
            @TID,										
            DATEADD(MINUTE, @Num * 15, GETDATE()),       -- departure_time
            50.00 + (@Num % 50)                         -- price: pret intre 50.00 si 99.99
        );

        SET @Num += 1;
    END;
END;
GO

USE CFR;
GO
CREATE OR ALTER PROCEDURE TestTickets_Inserari @NoOfRows INT
AS
BEGIN
    DECLARE @Num INT;
    SET @Num = 1;

    WHILE @Num <= @NoOfRows
    BEGIN
        INSERT INTO TestTickets (id_test_pas, id_test_train)
        VALUES 
        (
            (@Num % 100) + 1,                          
            (@Num % 20) + 1                            
        );

        SET @Num += 1;
    END;
END;
GO


SELECT * FROM Passengers
SELECT * FROM Trains