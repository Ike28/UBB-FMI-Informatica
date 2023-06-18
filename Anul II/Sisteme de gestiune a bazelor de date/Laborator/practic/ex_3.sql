USE S32023
GO

CREATE INDEX ix_CostAchizitii ON Achizitii(cost_sejur ASC);
GO

alter index ix_CostAchizitii on Achizitii disable
alter index ix_CostAchizitii on Achizitii rebuild

SELECT cost_sejur
FROM Achizitii
WHERE cost_sejur > 1200
