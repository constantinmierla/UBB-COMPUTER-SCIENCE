USE CFR;
GO

SELECT * FROM Trains

EXEC CRUD_Trains 'INTER_REGIO', 300, 'RO813SVX', 2

CREATE OR ALTER PROCEDURE CRUD_Trains
    @Model VARCHAR(50),
    @Capacity INT,
    @Registration VARCHAR(50),
    @NoOfRows INT
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        -- Validare
        EXEC dbo.Validate_Trains @Model, @Capacity, @Registration;

        -- Inserare multiple randuri
        DECLARE @i INT = 0;
        WHILE @i < @NoOfRows
        BEGIN
            INSERT INTO Trains (model, capacity, registration)
            VALUES (@Model, @Capacity, @Registration);

            SET @i = @i + 1;
        END

        -- selectare date dupa Inserare (Create)
        SELECT * FROM Trains
        ORDER BY id_tr;

        -- actualizare date (Update)
        UPDATE Trains
        SET capacity = capacity + 10 -- Exemplu: creste capacitatea cu 10
        WHERE model = @Model;

        -- selectare date dupa Actualizare
        SELECT * FROM Trains
        ORDER BY id_tr;

        -- stergere date (Delete)
        DELETE FROM Trains
        WHERE model = @Model;

        -- selectare date dupa Stergere
        SELECT * FROM Trains
        ORDER BY id_tr;

        PRINT 'Operațiile CRUD pentru Trains au fost realizate cu succes!';
    END TRY
    BEGIN CATCH
        PRINT 'Eroare: ' + ERROR_MESSAGE();
    END CATCH
END;

USE CFR;
GO

CREATE OR ALTER PROCEDURE Validate_Trains
    @Model VARCHAR(50),
    @Capacity INT,
    @Registration VARCHAR(50)
AS
BEGIN
    DECLARE @ErrorMessages NVARCHAR(MAX) = '';

    IF @Model IS NULL OR LTRIM(RTRIM(@Model)) = ''
        SET @ErrorMessages += 'Modelul nu poate fi NULL sau vid!' + CHAR(13) + CHAR(10);

    IF @Capacity <= 0
        SET @ErrorMessages += 'Capacitatea trebuie sa fie un numar pozitiv!' + CHAR(13) + CHAR(10);

    IF @Registration IS NULL OR LTRIM(RTRIM(@Registration)) = ''
        SET @ErrorMessages += 'Numarul de inregistrare nu poate fi NULL sau vid!' + CHAR(13) + CHAR(10);

    IF @ErrorMessages <> ''
    BEGIN
        RAISERROR(@ErrorMessages, 16, 1);
        RETURN 0;
    END

    RETURN 1;
END;
