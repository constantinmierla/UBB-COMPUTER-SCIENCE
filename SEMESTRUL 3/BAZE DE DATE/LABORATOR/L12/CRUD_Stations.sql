USE CFR;
GO

SELECT * FROM Stations
EXEC CRUD_Stations 'Veresti', 7

CREATE OR ALTER PROCEDURE CRUD_Stations
    @NameS VARCHAR(50),
    @IdCity INT
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        -- validare
        EXEC dbo.Validate_Stations @NameS, @IdCity;

        -- inserare
        INSERT INTO Stations (nameS, id_city)
        VALUES (@NameS, @IdCity);

        -- selectare date dupa Inserare
        SELECT * FROM Stations;

		UPDATE Stations SET nameS = UPPER(nameS) WHERE nameS = @NameS

		SELECT * FROM Stations;
        -- stergere
        DELETE FROM Stations
        WHERE nameS = UPPER(@NameS);

        -- selectare dupa Stergere
        SELECT * FROM Stations;

        PRINT 'Operatiile CRUD pentru Stations au fost realizate cu succes!';
    END TRY
    BEGIN CATCH
        PRINT 'Eroare: ' + ERROR_MESSAGE();
    END CATCH
END;

USE CFR;
GO

CREATE OR ALTER PROCEDURE Validate_Stations
    @NameS VARCHAR(50),
    @IdCity INT
AS
BEGIN
    DECLARE @ErrorMessages NVARCHAR(MAX) = '';

    IF @NameS IS NULL OR LTRIM(RTRIM(@NameS)) = ''
        SET @ErrorMessages += 'Numele statiei nu poate fi NULL sau vid!' + CHAR(13) + CHAR(10);

    IF NOT EXISTS (SELECT 1 FROM Cities WHERE id = @IdCity)
        SET @ErrorMessages += 'Orasul specificat nu exista!' + CHAR(13) + CHAR(10);

    IF @ErrorMessages <> ''
    BEGIN
        RAISERROR(@ErrorMessages, 16, 1);
        RETURN 0;
    END

    RETURN 1;
END;
