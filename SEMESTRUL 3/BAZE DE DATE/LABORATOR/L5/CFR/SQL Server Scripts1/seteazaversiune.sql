CREATE PROCEDURE SeteazaVersiune @Versiune INT
AS
BEGIN
    -- verificare versiune valida
    IF @Versiune < 0 OR @Versiune > 5
    BEGIN
        PRINT 'Versiune invalida';
        RETURN;
    END;

    -- obtine versiunea curenta din tabel
    DECLARE @VersiuneBD INT;
    SET @VersiuneBD = (SELECT numar_versiune FROM VersiuneCurenta WHERE id_versiune = 1);

    IF @Versiune > @VersiuneBD
    BEGIN
        -- creste versiunea
        WHILE @VersiuneBD < @Versiune
        BEGIN
            SET @VersiuneBD += 1;

            IF @VersiuneBD = 1
            BEGIN
                EXEC dbo.ModificareTipColoane;
                PRINT 'S-a modificat la versiunea 1';
            END
            ELSE IF @VersiuneBD = 2
            BEGIN
                EXEC dbo.AdaugareConstrangereValoareImplicita;
                PRINT 'S-a modificat la versiunea 2';
            END
            ELSE IF @VersiuneBD = 3
            BEGIN
                EXEC dbo.CreeareTabelEvaluariTrenuri;
                PRINT 'S-a modificat la versiunea 3';
            END
            ELSE IF @VersiuneBD = 4
            BEGIN
                EXEC dbo.AdaugaCampObservatiiDrivers;
                PRINT 'S-a modificat la versiunea 4';
            END
            ELSE IF @VersiuneBD = 5
            BEGIN
                EXEC dbo.AdaugaCheieStrainaStationsCities;
                PRINT 'S-a modificat la versiunea 5';
            END
        END;
    END
    ELSE
    BEGIN
        -- scade versiunea
        WHILE @VersiuneBD > @Versiune
        BEGIN
            SET @VersiuneBD -= 1;

            IF @VersiuneBD = 4
            BEGIN
                EXEC dbo.EliminareCheieStrainaStationsCities;
                PRINT 'S-a revenit la versiunea 4';
            END
            ELSE IF @VersiuneBD = 3
            BEGIN
                EXEC dbo.EliminareCampObservatiiDrivers;
                PRINT 'S-a revenit la versiunea 3';
            END
            ELSE IF @VersiuneBD = 2
            BEGIN
                EXEC dbo.StergereTabelEvaluariTrenuri;
                PRINT 'S-a revenit la versiunea 2';
            END
            ELSE IF @VersiuneBD = 1
            BEGIN
                EXEC dbo.EliminareConstrangereValoareImplicita;
                PRINT 'S-a revenit la versiunea 1';
            END
            ELSE IF @VersiuneBD = 0
            BEGIN
                EXEC dbo.RevenireTipColoane;
                PRINT 'S-a revenit la versiunea 0';
            END
        END;
    END;

    -- actualizare versiune curenta in tabel
    UPDATE VersiuneCurenta
    SET numar_versiune = @Versiune
    WHERE id_versiune = 1;
END;
GO

EXEC SeteazaVersiune @Versiune = 1;
EXEC SeteazaVersiune @Versiune = 2;
EXEC SeteazaVersiune @Versiune = 3;
EXEC SeteazaVersiune @Versiune = 4;
EXEC SeteazaVersiune @Versiune = 5;

SELECT * FROM VersiuneCurenta;