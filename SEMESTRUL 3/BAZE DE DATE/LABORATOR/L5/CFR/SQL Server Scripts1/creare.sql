USE CFR;
GO

CREATE TABLE VersiuneCurenta (
	id_versiune INT PRIMARY KEY,
	numar_versiune INT
);

INSERT INTO VersiuneCurenta (id_versiune, numar_versiune)
VALUES (1, 0);

SELECT * FROM VersiuneCurenta;
