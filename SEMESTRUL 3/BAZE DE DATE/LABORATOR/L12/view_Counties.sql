USE CFR;
GO

SELECT * FROM vw_counties_name
CREATE OR ALTER VIEW vw_counties_name

AS
SELECT 
    id, 
    nameCo
FROM Counties
WHERE LEFT(nameCo, 1) = 'C';
GO

CREATE NONCLUSTERED INDEX idx_nameCo
ON Counties (nameCo);
GO

-- index pe coloana id si nameCo pentru interogari combinate
CREATE NONCLUSTERED INDEX idx_id_nameCo
ON Counties (id, nameCo);
GO