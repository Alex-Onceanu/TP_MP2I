SELECT name FROM villagers
WHERE color = 'Red';

SELECT DISTINCT color from villagers;

SELECT name from villagers
WHERE color = 'Beige' AND birthday = '10-28';

SELECT DISTINCT name from articles
ORDER BY price DESC
LIMIT 10;

SELECT * from wallpapers
ORDER BY price ASC
LIMIT 6 OFFSET 3;

SELECT date FROM purchases
JOIN villagers ON date = birthday
WHERE style = 'Cool' AND NOT amount = 7;

SELECT * FROM villagers v
JOIN wallpapers w ON v.wallpaper = w.name
WHERE NOT w.color = v.color;

SELECT v2.name FROM villagers v1
JOIN referral r ON r.id_referee = v1.id
JOIN villagers v2 ON r.id_referrer = v2.id
WHERE v1.name = 'Charlise';

SELECT v1.name FROM villagers v1
JOIN referral r ON r.id_referee = v1.id
JOIN villagers v2 ON r.id_referrer = v2.id
WHERE v1.name = v2.name;

SELECT count(*) FROM villagers v
JOIN purchases p ON p.villager_id = v.id
WHERE v.birthday = p.date;

SELECT DISTINCT v.name, a.name, a.price, v.birthday FROM villagers v
JOIN purchases p ON p.villager_id = v.id
JOIN articles a ON a.id = p.article_id
WHERE v.birthday = p.date
ORDER BY price DESC
LIMIT 10;

SELECT DISTINCT v.name FROM villagers v
JOIN purchases p ON v.id = p.villager_id
JOIN articles a ON a.id = p.article_id AND a.variant_id = p.variant_id
WHERE NOT v.color = a.color;

SELECT DISTINCT v1.name FROM villagers v1 EXCEPT
SELECT DISTINCT v.name FROM villagers v 
JOIN articles a ON v.color = a.color
JOIN purchases p ON p.villager_id = v.id AND p.article_id = a.id AND p.variant_id = a.variant_id;

SELECT color, count(*) FROM villagers GROUP BY color;

SELECT v.name, count(a.price), max(a.price), min(a.price) FROM villagers v
JOIN purchases p ON v.id = p.villager_id
JOIN articles a ON a.id = p.article_id AND a.variant_id = p.variant_id
GROUP BY v.name;

SELECT count(name), species, color, style FROM villagers
GROUP BY species, color, style 
ORDER BY count(name) DESC
LIMIT 10;

SELECT v.name, sum(a.price * p.amount) / sum(p.amount) FROM villagers v 
JOIN purchases p ON v.id = p.villager_id 
JOIN articles a ON a.id = p.article_id AND a.variant_id = p.variant_id
GROUP BY v.name
ORDER BY sum(a.price * p.amount) / sum(p.amount) ASC
LIMIT 10; 

SELECT v.name, sum(a.price * p.amount) as s FROM villagers v 
JOIN purchases p ON p.villager_id = v.id 
JOIN articles a ON a.id = p.article_id AND a.variant_id = p.variant_id
WHERE p.date > '01-01' AND p.date < '03-31'
GROUP BY v.name
ORDER BY s DESC
LIMIT 5;

SELECT v.name, sum(a.price * p.amount) as s FROM villagers v 
JOIN purchases p ON p.villager_id = v.id 
JOIN articles a ON a.id = p.article_id AND a.variant_id = p.variant_id
WHERE p.date > '01-01' AND p.date < '03-31'
GROUP BY v.name
HAVING s >= 40000 AND s <= 50000
ORDER BY s DESC;

SELECT v.name, v.birthday, a.name, a.price, p.amount, s.reduction FROM villagers v
JOIN purchases p  ON p.villager_id = v.id AND p.date = v.birthday
JOIN articles a ON p.article_id = a.id AND p.variant_id = a.variant_id
JOIN promotions s ON s.article_id = a.id AND p.date LIKE s.month || "-%";

SELECT name, CASE WHEN variation_name IS NULL THEN name
    ELSE variation_name || ' ' || name 
    END AS detail
FROM articles;

SELECT a.name, a.price, p.date, CASE 
    WHEN s.reduction IS NULL THEN 0
    ELSE s.reduction
    END AS reduction
FROM articles a
JOIN purchases p ON p.article_id = a.id AND p.variant_id = a.variant_id
LEFT JOIN promotions s ON s.article_id = a.id AND p.date LIKE s.month || "-%";

SELECT v.name, 
sum(
    CASE 
        WHEN p.date = v.birthday 
            THEN 0 
        ELSE a.price * p.amount * (1.0 - 0.01 * (
            CASE 
                WHEN s.reduction IS NULL THEN 0 
                ELSE s.reduction 
            END)) 
    END
)
    as total_depense
FROM villagers v 
JOIN purchases p ON v.id = p.villager_id
JOIN articles a ON a.id = p.article_id AND a.variant_id = p.variant_id
LEFT JOIN promotions s ON s.article_id = a.id AND p.date LIKE s.month || "-%"
GROUP BY v.name
ORDER BY total_depense ASC 
LIMIT 1;