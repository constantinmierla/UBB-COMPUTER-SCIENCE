USE CFR;
GO

EXEC CRUD_Counties 'Chiajna', 5

CREATE OR ALTER PROCEDURE CRUD_Counties
    @NameCo VARCHAR(50),
    @NoOfRows INT
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        -- validare
        EXEC dbo.Validate_Counties @NameCo;

        -- inserare multiple randuri
        DECLARE @i INT = 0;
        WHILE @i < @NoOfRows
        BEGIN
            INSERT INTO Counties (nameCo)
            VALUES (@NameCo);

            SET @i = @i + 1;
        END

        -- selectare date dupa Inserare (Create)
        SELECT * FROM Counties
        ORDER BY id;

        -- actualizare date (Update)
        UPDATE Counties
        SET nameCo = UPPER(nameCo)
        WHERE nameCo = @NameCo;

        -- selectare date după Actualizare
        SELECT * FROM Counties
        ORDER BY id;

        -- stergere date (Delete)
        DELETE FROM Counties
        WHERE nameCo = UPPER(@NameCo);

        -- selectare date dupa Stergere
        SELECT * FROM Counties
        ORDER BY id;

        -- finalizare
        PRINT 'Operatiile CRUD au fost realizate cu succes!';
    END TRY
    BEGIN CATCH
        -- Gestionare erori
        PRINT 'A apărut o eroare: ' + ERROR_MESSAGE();
    END CATCH
END;

DELETE FROM Counties
        WHERE nameCo = UPPER('Constanta');


CREATE OR ALTER PROCEDURE Validate_Counties
    @NameCo VARCHAR(50)
AS
BEGIN
    -- declarare variabila pentru acumularea erorilor
    DECLARE @ErrorMessages NVARCHAR(MAX) = '';

    -- validare NameCo (nu poate fi NULL sau vid)
    IF @NameCo IS NULL OR LTRIM(RTRIM(@NameCo)) = ''
    BEGIN
        SET @ErrorMessages += 'Numele judetului nu poate fi NULL sau vid!' + CHAR(13) + CHAR(10);
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
