

SELECT p.person_id, p.first_name, p.last_name, h.household_sub_token, h.household_size
FROM Person p INNER JOIN Household h ON p.household_id = h.household_id;

SELECT p.person_id, p.first_name, m.migration_reason, m.year_of_migration FROM Person p LEFT JOIN Migration_History m ON p.person_id = m.person_id;

SELECT c.census_block_code, s.first_name,
s.staff_role FROM Census_Staff s RIGHT JOIN Census_Block c ON s.assigned_census_block_id = c.census_block_id;
SELECT p.person_id, m.migration_reason FROM Person p LEFT JOIN Migration_History m
ON p.person_id=m.person_id UNION SELECT p.person_id,
m.migration_reason FROM Person p RIGHT JOIN Migration_History m ON p.person_id=m.person_id;

SELECT * FROM Occupation NATURAL JOIN ( SELECT occupation_id FROM Person ) A;

SELECT e.first_name AS Employee, s.first_name AS Supervisor
FROM Census_Staff e LEFT JOIN Census_Staff s ON e.supervisor_id=s.staff_id;

SELECT p.first_name,p.last_name,h.household_sub_token,cb.census_block_code,uc.union_council_name
FROM Person p INNER JOIN Household h ON p.household_id=h.household_id 
INNER JOIN Census_Block cb ON cb.census_block_id=h.household_id 
INNER JOIN Union_Council uc ON cb.union_council_id=uc.union_council_id;

SELECT first_name,last_name FROM Person WHERE household_id IN
( SELECT household_id FROM Household
WHERE household_size > 5 );
SELECT first_name,last_name
FROM Person
WHERE household_id IN
(
SELECT household_id
FROM Household
WHERE household_size > 5
);

SELECT first_name,monthly_income FROM Person
WHERE monthly_income > ANY (
SELECT monthly_income FROM Person WHERE sex_id=2
);

SELECT first_name,monthly_income FROM Person WHERE monthly_income >
ALL ( SELECT monthly_income FROM Person WHERE sex_id=2 );

SELECT first_name FROM Person WHERE person_id NOT IN
( SELECT person_id FROM Migration_History );

SELECT first_name
FROM Person
WHERE monthly_income <= ALL
(
SELECT monthly_income
FROM Person
WHERE sex_id=1
);

SELECT first_name FROM Person WHERE monthly_income <= ANY
( SELECT monthly_income FROM Person WHERE sex_id=1 );

SELECT p.first_name FROM Person p WHERE EXISTS (
SELECT * FROM Migration_History m WHERE m.person_id=p.person_id );


SELECT p.first_name FROM Person p WHERE NOT EXISTS
 ( SELECT * FROM Migration_History m WHERE m.person_id=p.person_id );

SELECT COUNT(*) AS TotalPopulation
FROM Person;

SELECT SUM(monthly_income) AS TotalIncome
FROM Person;
SELECT AVG(monthly_income) AS AverageIncome
FROM Person;

SELECT MIN(monthly_income) AS LowestIncome
FROM Person;

SELECT MAX(monthly_income) AS HighestIncome
FROM Person;

SELECT b.sex_name, COUNT(*) AS Population FROM Person p
INNER JOIN Biological_Sex b ON p.sex_id=b.sex_id GROUP BY b.sex_name;

SELECT sex_id, COUNT(*) AS Population FROM Person GROUP BY sex_id
HAVING COUNT(*) > 3;

SELECT r.religion_name, COUNT(*) AS Population, AVG(monthly_income) AS AvgIncome
FROM Person p INNER JOIN Religion r ON p.religion_id=r.religion_id
GROUP BY r.religion_name;

SELECT first_name FROM Person UNION 
SELECT first_name FROM Census_Staff;

SELECT first_name FROM Person 
UNION ALL SELECT first_name FROM Census_Staff;

SELECT first_name
FROM Person
WHERE first_name IN
(
SELECT first_name
FROM Census_Staff
);

SELECT first_name FROM Person WHERE first_name NOT IN
( SELECT first_name FROM Census_Staff );

CREATE VIEW vw_population_summary AS
SELECT
person_id,
first_name,
last_name,
monthly_income
FROM Person;
SELECT * FROM vw_population_summary;

CREATE VIEW vw_staff_assignment AS
SELECT
s.staff_id,
s.first_name,
s.last_name,
c.census_block_code
FROM Census_Staff s
INNER JOIN Census_Block c
ON s.assigned_census_block_id=c.census_block_id;

SELECT * FROM vw_staff_assignment;

CREATE VIEW vw_structure_details AS
SELECT
st.structure_id,
st.structure_address_no,
cb.census_block_code
FROM Structure st
INNER JOIN Census_Block cb
ON st.census_block_id=cb.census_block_id;

SELECT * FROM vw_structure_details;


