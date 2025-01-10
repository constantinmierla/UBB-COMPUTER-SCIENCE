USE CFR;
GO

EXEC CRUD_Passengers 'Ion Popescu','2000-05-20', 1, 7, 3;

CREATE OR ALTER PROCEDURE CRUD_Passengers
    @NameP VARCHAR(50),
    @Birthdate DATETIME,
    @Gender BIT,
    @IdCity INT,
    @NoOfRows INT
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        -- validare date
        EXEC dbo.Validate_Passengers @NameP, @Birthdate, @Gender, @IdCity;

        -- inserare multiple randuri
        DECLARE @i INT = 0;
        WHILE @i < @NoOfRows
        BEGIN
            INSERT INTO Passengers (nameP, birthdate, gender, id_city)
            VALUES (@NameP, @Birthdate, @Gender, @IdCity);
            SET @i = @i + 1;
        END

        -- selectare date dupa Inserare (Create)
        PRINT 'Datele au fost inserate:';
        SELECT * FROM Passengers ORDER BY id_pas;

        -- actualizare date (Update)
        UPDATE Passengers
        SET nameP = UPPER(nameP)
        WHERE nameP = @NameP;

        PRINT 'Datele au fost actualizate:';
        SELECT * FROM Passengers ORDER BY id_pas;

        -- stergere date (Delete)
        DELETE FROM Passengers
        WHERE nameP = UPPER(@NameP);

        PRINT 'Datele au fost sterse:';
        SELECT * FROM Passengers ORDER BY id_pas;

        -- finalizare
        PRINT 'Operatiile CRUD pentru Passengers au fost realizate cu succes!';
    END TRY
    BEGIN CATCH
        -- gestionare erori
        PRINT 'A aparut o eroare: ' + ERROR_MESSAGE();
    END CATCH
END;


CREATE OR ALTER PROCEDURE Validate_Passengers
    @NameP VARCHAR(50),
    @Birthdate DATETIME,
    @Gender BIT,
    @IdCity INT
AS
BEGIN
    DECLARE @ErrorMessages NVARCHAR(MAX) = '';

    -- validare NameP (nu poate fi NULL sau vid)
    IF @NameP IS NULL OR LTRIM(RTRIM(@NameP)) = ''
    BEGIN
        SET @ErrorMessages += 'Numele pasagerului nu poate fi NULL sau vid!' + CHAR(13) + CHAR(10);
    END

    -- validare Birthdate (nu poate fi NULL sau viitor)
    IF @Birthdate IS NULL OR @Birthdate > GETDATE()
    BEGIN
        SET @ErrorMessages += 'Data nasterii nu poate fi NULL sau din viitor!' + CHAR(13) + CHAR(10);
    END

    -- validare Gender (1 sau 0)
    IF @Gender NOT IN (0, 1)
    BEGIN
        SET @ErrorMessages += 'Genul trebuie sa fie 1 (Masculin) sau 0 (Feminin)!' + CHAR(13) + CHAR(10);
    END

    -- validare IdCity (trebuie sa existe in tabela Cities)
    IF NOT EXISTS (SELECT 1 FROM Cities WHERE id = @IdCity)
    BEGIN
        SET @ErrorMessages += 'ID-ul orasului nu exista in tabela Cities!' + CHAR(13) + CHAR(10);
    END

    -- verificare erori
    IF @ErrorMessages <> ''
    BEGIN
        RAISERROR(@ErrorMessages, 16, 1);
        RETURN 0;
    END

    -- fara erori
    RETURN 1;
END;
