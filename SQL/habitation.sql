-- SQLite
SELECT DISTINCT p1.prenom, p1.nom, p2.prenom, p2.nom, v.nom, h1.debut, h1.fin
FROM personne p1
JOIN habite h1 ON p1.id_pers = h1.id_pers
JOIN agglomeration v ON v.code = h1.code_agglo
JOIN habite h2 ON v.code = h2.code_agglo
JOIN personne p2 ON h2.id_pers = p2.id_pers
WHERE NOT (h1.debut > h2.fin OR h2.debut > h1.fin)
AND p1.id_pers < p2.id_pers;