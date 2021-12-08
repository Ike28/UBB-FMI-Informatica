USE DiebmannImobiliare
GO

-- 1. toate locuintele si informatii despre proprietarii lor
SELECT ProprietatiGenerale.oras, ProprietatiGenerale.adresa AS adresaLocuinta, Proprietari.nume AS numeProprietar, Proprietari.email AS emailProprietar
FROM ProprietatiGenerale
INNER JOIN Proprietari ON ProprietatiGenerale.idProprietar = Proprietari.idProprietar
WHERE ProprietatiGenerale.tip = 'locuinta'

-- 2. orasele cu proprietati in cel putin 2 zone diferite, si numarul proprietatilor in ele
SELECT COUNT(idProprietate) AS numarProp, oras
FROM ProprietatiGenerale
GROUP BY oras
HAVING COUNT(DISTINCT zona) > 1

-- 3. toti agentii si sediile la care sunt angajati
SELECT Sedii.oras, Sedii.adresa, Agenti.nume AS numeAgent
FROM Sedii
INNER JOIN Agenti ON Sedii.idSediu = Agenti.idSediuAsignat

-- 4. toate sediile din Cluj-Napoca si numarul de agenti angajati la fiecare
WITH numarAgenti AS (SELECT COUNT(Agenti.idSediuAsignat) AS valoare, idSediuAsignat AS idSediu
FROM Agenti
GROUP BY Agenti.idSediuAsignat)

SELECT Sedii.oras AS orasSediu, Sedii.adresa AS adresaSediu, numarAgenti.valoare AS numarAgenti
FROM numarAgenti
INNER JOIN Sedii ON Sedii.idSediu = numarAgenti.idSediu
WHERE Sedii.oras = 'Cluj-Napoca'

-- 5. proprietatile cu cel putin un anunt, si numarul anunturilor
SELECT COUNT(Anunturi.idProprietateAnunt) AS numarAnunturi, ProprietatiGenerale.idProprietate
FROM Anunturi
INNER JOIN ProprietatiGenerale ON Anunturi.idProprietateAnunt = ProprietatiGenerale.idProprietate
GROUP BY ProprietatiGenerale.idProprietate
HAVING COUNT(Anunturi.idProprietateAnunt) > 0

-- 6. numarul de terenuri detinut de fiecare proprietar (daca acesta detine vreunul)
SELECT COUNT(ProprietatiGenerale.idProprietar) AS numarTerenuri, Proprietari.nume AS numeProprietar
FROM ProprietatiGenerale
INNER JOIN Proprietari ON ProprietatiGenerale.idProprietar = Proprietari.idProprietar
GROUP BY Proprietari.nume, ProprietatiGenerale.idProprietar, ProprietatiGenerale.tip
HAVING ProprietatiGenerale.tip = 'teren'

-- 7. orasele in care sunt inregistrate locuinte
SELECT DISTINCT oras FROM ProprietatiGenerale
WHERE tip = 'locuinta'

-- 8. toate proprietatile dinafara Cluj-Napoca cu informatii despre zona, tip si numarul de camere daca este aplicabil
(SELECT l.tipLoc AS tip, CAST(l.camere AS VARCHAR(4)) AS camere, p.oras AS oras, p.zona AS zona
FROM Locuinte l
INNER JOIN ProprietatiGenerale p ON p.idProprietate = l.idLocuinta
WHERE LOWER(oras) !='Cluj-Napoca')
UNION
(SELECT 'teren ' + t.tipTeren AS tip, 'neaplicabil' as camere, p.oras AS oras, p.zona
FROM Terenuri t
INNER JOIN ProprietatiGenerale p ON p.idProprietate = t.idTeren
WHERE LOWER(oras) !='Cluj-Napoca')
UNION
(SELECT 'spatiu ' + s.tipSpatiu AS tip, CAST(s.camere AS VARCHAR(4)) AS camere, p.oras AS oras, p.zona AS zona
FROM Spatii s
INNER JOIN ProprietatiGenerale p ON p.idProprietate = s.idSpatiu
WHERE LOWER(oras) !='Cluj-Napoca')

-- 9. contractele pe proprietatile inafara Cluj-Napoca si date despre clientii care le-au incheiat
WITH prop_contractate AS ( SELECT pg.oras, pg.adresa, ctr.idClientContract AS idClient, ctr.valoare, CAST(ctr.lunaTranz AS VARCHAR(2)) + '/' + CAST(ctr.anTranz AS VARCHAR(4))
	AS incheiat, ctr.tip, ctr.perioada AS perioadaInLuni
FROM ProprietatiGenerale pg
INNER JOIN Contracte ctr ON ctr.idProprietateContract = pg.idProprietate
WHERE LOWER(pg.oras) != 'Cluj-Napoca')


SELECT pc.oras, pc.adresa, pc.incheiat, pc.tip, pc.perioadaInLuni, cl.nume, cl.email
FROM prop_contractate pc
INNER JOIN Clienti cl ON pc.idClient = cl.idClient

-- 10. contractele pe terenuri si date despre clienti
WITH prop_contractate AS ( SELECT pg.oras, pg.adresa, ctr.idClientContract AS idClient, ctr.valoare, CAST(ctr.lunaTranz AS VARCHAR(2)) + '/' + CAST(ctr.anTranz AS VARCHAR(4))
	AS incheiat, ctr.tip AS tipC, ctr.perioada AS perioadaInLuni
FROM ProprietatiGenerale pg
INNER JOIN Contracte ctr ON ctr.idProprietateContract = pg.idProprietate
WHERE LOWER(pg.tip) = 'teren')


SELECT pc.oras, pc.adresa, pc.incheiat, pc.tipC as tipContract, pc.valoare AS valoareInEuro, pc.perioadaInLuni, cl.nume AS numeClient, cl.email AS emailClient
FROM prop_contractate pc
INNER JOIN Clienti cl ON pc.idClient = cl.idClient
