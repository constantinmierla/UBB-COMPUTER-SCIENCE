USE CFR;
GO

-- adauga un bilet pentru trenul cu ID 1 si pasagerul cu ID 5
SELECT * FROM Trains
SELECT * FROM Passengers
SELECT * FROM Tickets
EXEC CRUD_Tickets 3, 5;

CREATE OR ALTER PROCEDURE CRUD_Tickets
    @IdTrain INT,
    @IdPas INT
AS
BEGIN
    SET NOCOUNT ON;

    BEGIN TRY
        -- validare date
        EXEC dbo.Validate_Tickets @IdTrain, @IdPas;

        -- inserare date (Create)
        INSERT INTO Tickets (id_train, id_pas)
        VALUES (@IdTrain, @IdPas);

        PRINT 'Datele au fost inserate:';
        SELECT * FROM Tickets ORDER BY id_train, id_pas;

        -- actualizare date (Update)
        UPDATE Tickets
        SET id_pas = (SELECT min(id_pas) FROM Passengers)
        WHERE id_train = @IdTrain AND id_pas = @IdPas;

        PRINT 'Datele au fost actualizate:';
        SELECT * FROM Tickets ORDER BY id_train, id_pas;

        -- stergere date (Delete)
        DELETE FROM Tickets
        WHERE id_train = @IdTrain AND id_pas = (SELECT min(id_pas) FROM Passengers);

        PRINT 'Datele au fost sterse:';
        SELECT * FROM Tickets ORDER BY id_train, id_pas;

        -- finalizare
        PRINT 'Operatiile CRUD pentru Tickets au fost realizate cu succes!';
    END TRY
    BEGIN CATCH
        -- gestionare erori
        PRINT 'A aparut o eroare: ' + ERROR_MESSAGE();
    END CATCH
END;

USE CFR;
GO

CREATE OR ALTER PROCEDURE Validate_Tickets
    @IdTrain INT,
    @IdPas INT
AS
BEGIN
    DECLARE @ErrorMessages NVARCHAR(MAX) = '';

    -- verifica daca trenul exista
    IF NOT EXISTS (SELECT 1 FROM Trains WHERE id_tr = @IdTrain)
        SET @ErrorMessages += 'Trenul specificat nu exista!' + CHAR(13) + CHAR(10);

    -- verifica daca pasagerul exista
    IF NOT EXISTS (SELECT 1 FROM Passengers WHERE id_pas = @IdPas)
        SET @ErrorMessages += 'Pasagerul specificat nu exista!' + CHAR(13) + CHAR(10);

    -- verificare erori
    IF @ErrorMessages <> ''
    BEGIN
        RAISERROR(@ErrorMessages, 16, 1);
        RETURN 0;
    END

    RETURN 1;
END;
