
USE PakistanCensusDatabase;

/*
Shows complete profile of every person including gender, education, job status and nationality.
*/

CREATE VIEW Person_Detail_View AS
SELECT
    p.person_id,
    CONCAT(p.first_name, ' ', p.last_name) AS name,
    bs.sex_name,
    el.level_name AS education_level,
    es.status_name AS employment_status,
    ms.status_name AS marital_status,
    n.country_name,
    h.household_size
FROM Person p
INNER JOIN Biological_Sex bs
ON p.sex_id = bs.sex_id
INNER JOIN Education_Level el
ON p.education_level_id = el.education_level_id
INNER JOIN Employment_Status es
ON p.employment_status_id = es.employment_status_id
INNER JOIN Marital_Status ms
ON p.marital_status_id = ms.marital_status_id
INNER JOIN Nationality n
ON p.nationality_id = n.nationality_id
INNER JOIN Household h
ON p.household_id = h.household_id
ORDER BY p.first_name;

-- VIEW
SELECT * FROM Person_Detail_View;

-- -------------------------------------------------------------------

/* 
Shows people who have Bachelors, Masters or PhD degree with their job and income.
*/

CREATE VIEW Highly_Educated_Persons AS
SELECT
    p.first_name,
    p.last_name,
    el.level_name,
    es.status_name,
    o.occupation_name,
    i.industry_name,
    p.monthly_income
FROM Person p
INNER JOIN Education_Level el
ON p.education_level_id = el.education_level_id
INNER JOIN Employment_Status es
ON p.employment_status_id = es.employment_status_id
INNER JOIN Occupation o
ON p.occupation_id = o.occupation_id
INNER JOIN Industry i
ON p.industry_id = i.industry_id
WHERE el.level_name IN('BACHELORS', 'MASTERS', 'PHD');

-- VIEW
SELECT* FROM Highly_Educated_Persons;

-- -------------------------------------------------------------------




/* 
Shows people who moved from one district to another with their education and job details.
Results are ordered by most recent migration year first.
*/

CREATE VIEW Migration_Record AS
	SELECT
		p.first_name,
		p.last_name,
		mh.migration_reason,
		mh.year_of_migration,
		d.district_name,
		el.level_name,
		es.status_name
	FROM Migration_History mh
	INNER JOIN Person p
	ON mh.person_id = p.person_id
	INNER JOIN District d
	ON mh.previous_district_id = d.district_id
	INNER JOIN Education_Level el
	ON p.education_level_id = el.education_level_id
	INNER JOIN Employment_Status es
	ON p.employment_status_id = es.employment_status_id
	ORDER BY mh.year_of_migration DESC;
SELECT* FROM Migration_Record;



/* CENSUS STAFF WORKING REPORT
Staff_Working_Report
Shows every census staff member with their role, assigned block, union council and district.
Helps track which staff member is working in which area.
*/
CREATE VIEW STAFF_WORKING_REPORT AS
SELECT
    cs.first_name,
    cs.last_name,
    cs.staff_role,
    cb.census_block_code,
    uc.union_council_name,
    t.tehsil_name,
    d.district_name
FROM Census_Staff cs

INNER JOIN Census_Block cb
ON cs.assigned_census_block_id = cb.census_block_id

INNER JOIN Union_Council uc
ON cb.union_council_id = uc.union_council_id

INNER JOIN Tehsil t
ON uc.tehsil_id = t.tehsil_id

INNER JOIN District d
ON t.district_id = d.district_id

ORDER BY cs.staff_role;
/* VIEW */
SELECT* FROM STAFF_WORKING_REPORT;


/* TOP 3 CITIES HIGHIGHLY POPULATION
Top_Population_Cities
Shows top 3 districts in Pakistan with highest number of households.
Useful for identifying most populated cities in the country.
*/
CREATE VIEW TOP_POPULATION_CITIES AS
SELECT
    p.province_name,
    d.district_name,
    SUM(cb.estimated_household_count) AS Total_Population

FROM Province p

INNER JOIN Division dv
ON p.province_id = dv.province_id

INNER JOIN District d
ON dv.division_id = d.division_id

INNER JOIN Tehsil t
ON d.district_id = t.district_id

INNER JOIN Union_Council uc
ON t.tehsil_id = uc.tehsil_id

INNER JOIN Census_Block cb
ON uc.union_council_id = cb.union_council_id

GROUP BY
    p.province_name,
    d.district_name

ORDER BY
    Total_Population DESC

LIMIT 3;

SELECT* FROM TOP_POPULATION_CITIES;


/* ...........................LEFT JOIN.......................

Citizens_Record
Shows all persons with their education, job, occupation and nationality — even if some info is missing.
NULL appears where information is not available for a person.
*/

CREATE VIEW CITIZENS_RECORD AS
SELECT
    p.first_name,
    p.last_name,
    el.level_name,
    es.status_name AS employment_status,
    o.occupation_name,
    i.industry_name,
    n.country_name

FROM Person p

LEFT JOIN Education_Level el
ON p.education_level_id = el.education_level_id

LEFT JOIN Employment_Status es
ON p.employment_status_id = es.employment_status_id

LEFT JOIN Occupation o
ON p.occupation_id = o.occupation_id

LEFT JOIN Industry i
ON p.industry_id = i.industry_id

LEFT JOIN Mother_Tongue mt
ON p.mother_tongue_id = mt.mother_tongue_id

LEFT JOIN Nationality n
ON p.nationality_id = n.nationality_id

ORDER BY el.level_name;
SELECT* FROM CITIZENS_RECORD;



/* Highly Educated Individuals Missing Occupation or Industry Information
Educated_Unemployed
Shows educated people (Bachelor, Master, MPhil) who have no occupation or industry assigned.
Helps find highly educated people who are still unemployed or unregistered.
 */
CREATE VIEW  EDUACATED_UNEMPLOYED AS
SELECT
    p.first_name,
    p.last_name,
    el.level_name,
    o.occupation_name,
    i.industry_name

FROM Person p

LEFT JOIN Education_Level el
ON p.education_level_id = el.education_level_id

LEFT JOIN Occupation o
ON p.occupation_id = o.occupation_id

LEFT JOIN Industry i
ON p.industry_id = i.industry_id

WHERE el.level_name IN ('Bachelor','Master','MPhil')
AND (o.occupation_name IS NULL
     OR i.industry_name IS NULL);

/* HOUSEHOLD BASED ANALYSIS 
Household_Analysis
Shows all married persons with their household size information.
Useful for studying family structure of married citizens.
*/
CREATE VIEW HOUSEhOLD_ANALYSIS AS
SELECT
    p.first_name,
    p.last_name,
    ms.status_name,
    h.household_size

FROM Person p

LEFT JOIN Marital_Status ms
ON p.marital_status_id = ms.marital_status_id

LEFT JOIN Employment_Status es
ON p.employment_status_id = es.employment_status_id

LEFT JOIN Household h
ON p.household_id = h.household_id

WHERE ms.status_name = 'Married';
SELECT* FROM HOUSEHOLD_ANALYSIS;

/* Migration and Educated Unemployment Assessment Report
Migration_Educated_Unemployment
Shows educated people who migrated but are still unemployed.
Helps government understand brain drain and unemployment after migration.
 */
CREATE VIEW MIGRATIONEDUCATED_UNEMPLOYMENT AS
SELECT
    p.first_name,
    p.last_name,
    mh.migration_reason,
    el.level_name,
    es.status_name

FROM Person p

LEFT JOIN Migration_History mh
ON p.person_id = mh.person_id

LEFT JOIN Education_Level el
ON p.education_level_id = el.education_level_id

LEFT JOIN Employment_Status es
ON p.employment_status_id = es.employment_status_id

WHERE mh.person_id IS NOT NULL
AND el.level_name IN ('Bachelor','Master','MPhil')
AND es.status_name = 'Unemployed';

SELECT* FROM MIGRATIONEDUCATED_UNEMPLOYMENT;

/* ................RIGHT JOIN.................
Urban_Block_Staff_Assignment
Shows urban census blocks with more than 300 households and their assigned enumerators or supervisors.
Blocks without staff also appear — helps find uncovered areas.
*/
CREATE VIEW URBAN_BLOCK_STAFF_ASSIGNMENT AS
SELECT
    cs.first_name           AS staff_first_name,
    cs.last_name            AS staff_last_name,
    cs.staff_role,
    cs.contact_number,
    cb.census_block_code,
    cb.estimated_household_count,
    cb.area_sq_km,
    uc.union_council_name,
    t.tehsil_name,
    d.district_name

FROM Census_Staff cs

RIGHT JOIN Census_Block cb
    ON cs.assigned_census_block_id = cb.census_block_id

RIGHT JOIN Union_Council uc
    ON cb.union_council_id = uc.union_council_id

RIGHT JOIN Tehsil t
    ON uc.tehsil_id = t.tehsil_id

RIGHT JOIN District d
    ON t.district_id = d.district_id

WHERE cb.is_urban = TRUE
AND cb.estimated_household_count > 300
AND cs.staff_role IN ('Enumerator', 'Supervisor')

ORDER BY cb.estimated_household_count DESC;

-- View Query:
SELECT * FROM URBAN_BLOCK_STAFF_ASSIGNMENT;


/* Employed_Religion_Education_Profile
Shows highly educated and full-time employed persons with their religion and mother tongue.
Only persons earning more than 30,000 with Bachelors or higher degree are shown. */

CREATE VIEW EMPLOYED_RELIGION_EDUCATION_PROFILE AS
SELECT
    p.first_name,
    p.last_name,
    r.religion_name,
    mt.tongue_name          AS mother_tongue,
    el.level_name           AS education_level,
    es.status_name          AS employment_status,
    p.monthly_income,
    TIMESTAMPDIFF(YEAR, p.date_of_birth, CURDATE()) AS age

FROM Religion r

RIGHT JOIN Person p
    ON r.religion_id = p.religion_id

RIGHT JOIN Household h
    ON p.household_id = h.household_id

RIGHT JOIN Mother_Tongue mt
    ON p.mother_tongue_id = mt.mother_tongue_id

RIGHT JOIN Education_Level el
    ON p.education_level_id = el.education_level_id

LEFT JOIN Employment_Status es
    ON p.employment_status_id = es.employment_status_id

WHERE el.level_name IN ('Bachelors', 'Masters', 'Doctorate')
AND es.status_name = 'Employed Full-Time'
AND p.monthly_income > 30000

ORDER BY p.monthly_income DESC;

-- View Query:
SELECT * FROM EMPLOYED_RELIGION_EDUCATION_PROFILE;

/* Disabled_Unemployed_Location_Report
Shows disabled and unemployed persons with their location from district to province level.
Only persons with no income are shown — useful for welfare targeting. */
CREATE VIEW DISABLEDUNEMPLOYED_LOCATION_REPORT AS
SELECT
    dt.disability_name,
    p.first_name,
    p.last_name,
    p.date_of_birth,
    bs.sex_name             AS gender,
    es.status_name          AS employment_status,
    el.level_name           AS education_level,
    p.monthly_income,
    d.district_name,
    pr.province_name

FROM Disability_Type dt

RIGHT JOIN Person_Disability pd
    ON dt.disability_type_id = pd.disability_type_id

RIGHT JOIN Person p
    ON pd.person_id = p.person_id

RIGHT JOIN Biological_Sex bs
    ON p.sex_id = bs.sex_id

RIGHT JOIN Employment_Status es
    ON p.employment_status_id = es.employment_status_id

RIGHT JOIN Education_Level el
    ON p.education_level_id = el.education_level_id

RIGHT JOIN Household h
    ON p.household_id = h.household_id

RIGHT JOIN Structure s
    ON h.structure_id = s.structure_id

RIGHT JOIN Census_Block cb
    ON s.census_block_id = cb.census_block_id

RIGHT JOIN Union_Council uc
    ON cb.union_council_id = uc.union_council_id

RIGHT JOIN Tehsil t
    ON uc.tehsil_id = t.tehsil_id

RIGHT JOIN District d
    ON t.district_id = d.district_id

RIGHT JOIN Division dv
    ON d.division_id = dv.division_id

RIGHT JOIN Province pr
    ON dv.province_id = pr.province_id

WHERE es.status_name IN (
    'Unemployed - Seeking Work',
    'Unemployed - Not Seeking Work',
    'Disabled - Unable to Work'
)
AND p.monthly_income IS NULL

ORDER BY dt.disability_name,
         pr.province_name;

-- View Query:
SELECT * FROM DISABLEDUNEMPLOYED_LOCATION_REPORT;

/*  Migrant_Employment_Housing_Report
Shows persons who migrated between 2015 and 2023 and are currently employed.
Also shows their housing condition, water source and lighting source. */
CREATE VIEW MIGRANT_EMPLOYMENT_HOUSING_REPORT AS
SELECT
    p.first_name,
    p.last_name,
    mh.migration_reason,
    mh.year_of_migration,
    d.district_name         AS migrated_from_district,
    el.level_name           AS education_level,
    es.status_name          AS employment_status,
    o.occupation_name,
    p.monthly_income,
    rst.status_name         AS residential_status,
    h.number_of_rooms,
    h.household_size,
    ws.source_name          AS water_source,
    ls.source_name          AS lighting_source

FROM District d

RIGHT JOIN Migration_History mh
    ON d.district_id = mh.previous_district_id

RIGHT JOIN Person p
    ON mh.person_id = p.person_id

RIGHT JOIN Education_Level el
    ON p.education_level_id = el.education_level_id

RIGHT JOIN Employment_Status es
    ON p.employment_status_id = es.employment_status_id

RIGHT JOIN Occupation o
    ON p.occupation_id = o.occupation_id

RIGHT JOIN Household h
    ON p.household_id = h.household_id

RIGHT JOIN Residential_Status_Type rst
    ON h.residential_status_type_id = rst.residential_status_type_id

RIGHT JOIN Structure s
    ON h.structure_id = s.structure_id

RIGHT JOIN Water_Source ws
    ON s.water_source_id = ws.water_source_id

RIGHT JOIN Lighting_Source ls
    ON s.lighting_source_id = ls.lighting_source_id

WHERE mh.year_of_migration BETWEEN 2015 AND 2023
AND es.status_name IN (
    'Employed Full-Time',
    'Employed Part-Time',
    'Self-Employed'
)
AND h.household_size >= 3

ORDER BY mh.year_of_migration DESC,
         p.monthly_income DESC;

-- View Query:
SELECT * FROM MIGRANT_EMPLOYMENT_HOUSING_REPORT;



/* ..................FULL OUTER JOIN..............

Full_Person_Disability_Report
Shows employed persons with Bachelors or Masters degree along with their disability status.
Both disabled and non-disabled employed persons appear in this report.

*/

CREATE VIEW FULL_PERSON_DISABILITY_REPORT AS

SELECT
    p.first_name,
    p.last_name,
    p.date_of_birth,
    bs.sex_name          AS gender,
    dt.disability_name,
    el.level_name        AS education_level,
    es.status_name       AS employment_status

FROM Person p

LEFT JOIN Person_Disability pd
    ON p.person_id = pd.person_id

LEFT JOIN Disability_Type dt
    ON pd.disability_type_id = dt.disability_type_id

LEFT JOIN Biological_Sex bs
    ON p.sex_id = bs.sex_id

LEFT JOIN Education_Level el
    ON p.education_level_id = el.education_level_id

LEFT JOIN Employment_Status es
    ON p.employment_status_id = es.employment_status_id

WHERE es.status_name = 'Employed Full-Time'
AND el.level_name IN ('Bachelors', 'Masters')

UNION

SELECT
    p.first_name,
    p.last_name,
    p.date_of_birth,
    bs.sex_name          AS gender,
    dt.disability_name,
    el.level_name        AS education_level,
    es.status_name       AS employment_status

FROM Person p

RIGHT JOIN Person_Disability pd
    ON p.person_id = pd.person_id

RIGHT JOIN Disability_Type dt
    ON pd.disability_type_id = dt.disability_type_id

RIGHT JOIN Biological_Sex bs
    ON p.sex_id = bs.sex_id

RIGHT JOIN Education_Level el
    ON p.education_level_id = el.education_level_id

RIGHT JOIN Employment_Status es
    ON p.employment_status_id = es.employment_status_id

WHERE es.status_name = 'Employed Full-Time'
AND el.level_name IN ('Bachelors', 'Masters')

ORDER BY disability_name, last_name;

-- View Query:
SELECT * FROM FULL_PERSON_DISABILITY_REPORT;



/* Full_Household_Structure_Report
Shows all households with their structure type, water source and residential ownership status.
Both owned and rented households with more than 2 members are included.   */
CREATE VIEW FULL_HOUSEHOLD_STRUCTURE_REPORT AS

SELECT
    h.household_id,
    h.household_size,
    h.number_of_rooms,
    rst.status_name      AS residential_status,
    s.structure_address_no,
    st.type_name         AS structure_type,
    ws.source_name       AS water_source

FROM Household h

LEFT JOIN Structure s
    ON h.structure_id = s.structure_id

LEFT JOIN Residential_Status_Type rst
    ON h.residential_status_type_id = rst.residential_status_type_id

LEFT JOIN Structure_Type st
    ON s.structure_type_id = st.structure_type_id

LEFT JOIN Water_Source ws
    ON s.water_source_id = ws.water_source_id

WHERE h.household_size > 2
AND rst.status_name IN ('Owned', 'Rented')

UNION

SELECT
    h.household_id,
    h.household_size,
    h.number_of_rooms,
    rst.status_name      AS residential_status,
    s.structure_address_no,
    st.type_name         AS structure_type,
    ws.source_name       AS water_source

FROM Household h

RIGHT JOIN Structure s
    ON h.structure_id = s.structure_id

RIGHT JOIN Residential_Status_Type rst
    ON h.residential_status_type_id = rst.residential_status_type_id

RIGHT JOIN Structure_Type st
    ON s.structure_type_id = st.structure_type_id

RIGHT JOIN Water_Source ws
    ON s.water_source_id = ws.water_source_id

WHERE h.household_size > 2
AND rst.status_name IN ('Owned', 'Rented')

ORDER BY household_size DESC;

-- View Query:
SELECT * FROM FULL_HOUSEHOLD_STRUCTURE_REPORT;



/*   Full_Block_Union_Council_Report
Shows all urban census blocks with more than 200 households linked to their union council and tehsil.
Blocks with or without full union council data both appear. */
CREATE VIEW FULL_BLOCK_UNION_COUNCIL_REPORT AS

SELECT
    cb.census_block_code,
    cb.estimated_household_count,
    cb.is_urban,
    cb.area_sq_km,
    uc.union_council_name,
    ucc.classification_name,
    t.tehsil_name

FROM Census_Block cb

LEFT JOIN Union_Council uc
    ON cb.union_council_id = uc.union_council_id

LEFT JOIN Union_Council_Classification ucc
    ON uc.union_council_classification_id = ucc.union_council_classification_id

LEFT JOIN Tehsil t
    ON uc.tehsil_id = t.tehsil_id

WHERE cb.estimated_household_count > 200
AND cb.is_urban = TRUE

UNION

SELECT
    cb.census_block_code,
    cb.estimated_household_count,
    cb.is_urban,
    cb.area_sq_km,
    uc.union_council_name,
    ucc.classification_name,
    t.tehsil_name

FROM Census_Block cb

RIGHT JOIN Union_Council uc
    ON cb.union_council_id = uc.union_council_id

RIGHT JOIN Union_Council_Classification ucc
    ON uc.union_council_classification_id = ucc.union_council_classification_id

RIGHT JOIN Tehsil t
    ON uc.tehsil_id = t.tehsil_id

WHERE cb.estimated_household_count > 200
AND cb.is_urban = TRUE

ORDER BY estimated_household_count DESC;

-- View Query:
SELECT * FROM FULL_BLOCK_UNION_COUNCIL_REPORT;

/* Full_Commercial_Province_Report
Shows all licensed commercial businesses with more than 5 employees from district to province level.
Both matched and unmatched commercial records appear to show complete business picture.
 */
CREATE VIEW FULL_COMMERCIAL_PROVINCE_REPORT AS

SELECT
    sc.business_name,
    sc.estimated_active_employees,
    sc.has_active_license,
    cst.commercial_type_name,
    s.structure_address_no,
    d.district_name,
    pr.province_name

FROM Structure_Commercial sc

LEFT JOIN Commercial_Sector_Type cst
    ON sc.commercial_type_id = cst.commercial_type_id

LEFT JOIN Structure s
    ON sc.structure_id = s.structure_id

LEFT JOIN Census_Block cb
    ON s.census_block_id = cb.census_block_id

LEFT JOIN Union_Council uc
    ON cb.union_council_id = uc.union_council_id

LEFT JOIN Tehsil t
    ON uc.tehsil_id = t.tehsil_id

LEFT JOIN District d
    ON t.district_id = d.district_id

LEFT JOIN Division dv
    ON d.division_id = dv.division_id

LEFT JOIN Province pr
    ON dv.province_id = pr.province_id

WHERE sc.has_active_license = TRUE
AND sc.estimated_active_employees > 5

UNION

SELECT
    sc.business_name,
    sc.estimated_active_employees,
    sc.has_active_license,
    cst.commercial_type_name,
    s.structure_address_no,
    d.district_name,
    pr.province_name

FROM Structure_Commercial sc

RIGHT JOIN Commercial_Sector_Type cst
    ON sc.commercial_type_id = cst.commercial_type_id

RIGHT JOIN Structure s
    ON sc.structure_id = s.structure_id

RIGHT JOIN Census_Block cb
    ON s.census_block_id = cb.census_block_id

RIGHT JOIN Union_Council uc
    ON cb.union_council_id = uc.union_council_id

RIGHT JOIN Tehsil t
    ON uc.tehsil_id = t.tehsil_id

RIGHT JOIN District d
    ON t.district_id = d.district_id

RIGHT JOIN Division dv
    ON d.division_id = dv.division_id

RIGHT JOIN Province pr
    ON dv.province_id = pr.province_id

WHERE sc.has_active_license = TRUE
AND sc.estimated_active_employees > 5

ORDER BY estimated_active_employees DESC;

-- View Query:
SELECT * FROM FULL_COMMERCIAL_PROVINCE_REPORT;



/* .....................NATURAL JOIN.....................




Natural_Person_Marital_Report
Shows all married persons with their date of birth and monthly income above 20,000.
Join happens automatically on matching column name marital_status_id.*/

CREATE VIEW NATURAL_PERSON_MARITAL_REPORT AS

SELECT
    p.first_name,
    p.last_name,
    p.date_of_birth,
    p.monthly_income,
    ms.status_name

FROM Marital_Status ms

NATURAL JOIN (
    SELECT
        marital_status_id,
        first_name,
        last_name,
        date_of_birth,
        monthly_income
    FROM Person
) p

WHERE ms.status_name = 'Married'
AND p.monthly_income > 20000

ORDER BY p.monthly_income DESC;

-- View Query:
SELECT * FROM NATURAL_PERSON_MARITAL_REPORT;

/*  Natural_Person_Employment_Report
Shows full-time employed or self-employed persons earning more than 30,000.
Join automatically matches on employment_status_id column between both tables. */
CREATE VIEW NATURAL_PERSON_EMPLOYMENT_REPORT AS

SELECT
    p.first_name,
    p.last_name,
    p.monthly_income,
    p.date_of_birth,
    es.status_name

FROM Employment_Status es

NATURAL JOIN (
    SELECT
        employment_status_id,
        first_name,
        last_name,
        monthly_income,
        date_of_birth
    FROM Person
) p

WHERE es.status_name IN (
    'Employed Full-Time',
    'Self-Employed'
)
AND p.monthly_income > 30000

ORDER BY p.monthly_income DESC;

-- View Query:
SELECT * FROM NATURAL_PERSON_EMPLOYMENT_REPORT;


/* Natural_Person_Education_Report
Shows persons with Bachelors, Masters or Doctorate degree earning more than 25,000.
Join automatically connects person to education level using education_level_id column. */
CREATE VIEW NATURAL_PERSON_EDUCATION_REPORT AS

SELECT
    p.first_name,
    p.last_name,
    p.monthly_income,
    p.date_of_birth,
    el.level_name

FROM Education_Level el

NATURAL JOIN (
    SELECT
        education_level_id,
        first_name,
        last_name,
        monthly_income,
        date_of_birth
    FROM Person
) p

WHERE el.level_name IN (
    'Bachelors',
    'Masters',
    'Doctorate'
)
AND p.monthly_income > 25000

ORDER BY el.level_name, p.monthly_income DESC;

-- View Query:
SELECT * FROM NATURAL_PERSON_EDUCATION_REPORT;





