
CREATE DATABASE IF NOT EXISTS PakistanCensusDatabase;
USE PakistanCensusDatabase;


-- CREATE TABLE IF NOT EXISTS Census_Cycle (
--     cycle_id INT PRIMARY KEY, -- e.g., 2017, 2023
--     start_date DATE NOT NULL,
--     end_date DATE NOT NULL,
--     description TEXT
-- );




-- 1. Province
CREATE TABLE IF NOT EXISTS Province (
    province_id INT AUTO_INCREMENT,
    province_name VARCHAR(100) NOT NULL,
    CONSTRAINT pk_province PRIMARY KEY (province_id)
);

-- 2. Division
CREATE TABLE IF NOT EXISTS Division (
    division_id INT AUTO_INCREMENT,
    division_name VARCHAR(100) NOT NULL,
    province_id INT NOT NULL,
    CONSTRAINT pk_division PRIMARY KEY (division_id),
    CONSTRAINT fk_province FOREIGN KEY (province_id) REFERENCES Province(province_id) 
	ON DELETE RESTRICT ON UPDATE CASCADE
);

-- 3. District
CREATE TABLE IF NOT EXISTS District (
    district_id INT AUTO_INCREMENT,
    district_name VARCHAR(100) NOT NULL,
    division_id INT NOT NULL,
    CONSTRAINT pk_district PRIMARY KEY (district_id),
    CONSTRAINT fk_division FOREIGN KEY (division_id) REFERENCES Division(division_id) 
	ON DELETE RESTRICT ON UPDATE CASCADE
);

-- 4. Tehsil
CREATE TABLE IF NOT EXISTS Tehsil (
    tehsil_id INT AUTO_INCREMENT,
    tehsil_name VARCHAR(100) NOT NULL,
    district_id INT NOT NULL,
    CONSTRAINT pk_tehsil PRIMARY KEY (tehsil_id) ,
    CONSTRAINT fk_district FOREIGN KEY (district_id) REFERENCES District(district_id) 
	ON DELETE RESTRICT ON UPDATE CASCADE
);

-- 5. Union_Council
CREATE TABLE IF NOT EXISTS Union_Council (
    union_council_id INT AUTO_INCREMENT,
    union_council_name VARCHAR(100) NOT NULL,
    tehsil_id INT NOT NULL,
    CONSTRAINT pk_union_council PRIMARY KEY (union_council_id),
    CONSTRAINT fk_tehsil FOREIGN KEY (tehsil_id) REFERENCES Tehsil(tehsil_id) 
	ON DELETE RESTRICT ON UPDATE CASCADE
);

-- 6. Census_Block
CREATE TABLE IF NOT EXISTS Census_Block (
    census_block_id INT AUTO_INCREMENT,
    census_block_code VARCHAR(20) UNIQUE NOT NULL,
    description TEXT,
    estimated_household_count INT DEFAULT 0 CHECK (estimated_household_count >= 0),
	is_urban BOOLEAN NOT NULL,           -- Required for Table 1, 2, 3, etc.
    area_sq_km DECIMAL(10, 2),           -- Required for Table 1 (Density calculation)
	union_council_id INT NOT NULL,
    CONSTRAINT pk_census_block PRIMARY KEY (census_block_id),
    CONSTRAINT fk_union_council FOREIGN KEY (union_council_id) REFERENCES Union_Council(union_council_id) 
	ON DELETE RESTRICT ON UPDATE CASCADE
);

-- ----------------------------------------------------------------------------------------------------------


-- 7. Household
CREATE TABLE IF NOT EXISTS Household (
    household_id INT AUTO_INCREMENT,
    address_description TEXT,
    structure_type VARCHAR(50), -- e.g., Pucca, Katcha, Semi-Pucca
    water_source VARCHAR(50),   -- e.g., Tap, Well, Tanker
    has_electricity BOOLEAN DEFAULT FALSE,
    has_gas BOOLEAN DEFAULT FALSE,
    total_members INT DEFAULT 0 CHECK (total_members >= 0),
    is_institutional bool DEFAULT FALSE, 
    census_block_id INT NOT NULL,
    cycle_id INT NOT NULL,
    CONSTRAINT pk_household PRIMARY KEY (household_id),
    CONSTRAINT fk_household_block FOREIGN KEY (census_block_id) REFERENCES Census_Block(census_block_id) 
	ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT fk_household_cycle FOREIGN KEY (cycle_id) REFERENCES Census_Cycle(cycle_id) 
	ON DELETE RESTRICT ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS Lkp_Religion (
    religion_id INT PRIMARY KEY,
    name VARCHAR(50)
);

CREATE TABLE IF NOT EXISTS Lkp_Language (
    language_id INT PRIMARY KEY,
    name VARCHAR(50)
);

CREATE TABLE IF NOT EXISTS Individual (
    individual_id INT AUTO_INCREMENT,
    
    full_name VARCHAR(100),
    gender ENUM('Male', 'Female', 'Other') NOT NULL,
    date_of_birth DATE NOT NULL,
    marital_status ENUM('Single', 'Married', 'Widowed', 'Divorced') NOT NULL,
    relationship_to_head VARCHAR(50),
    
    religion_id INT,
    language_id INT,
    nationality VARCHAR(50) DEFAULT 'Pakistani',
    
    household_id INT NOT NULL,
	CONSTRAINT pk_individual PRIMARY KEY (individual_id),
    -- Foreign Keys
    CONSTRAINT fk_household FOREIGN KEY (household_id) REFERENCES Household(household_id),
    CONSTRAINT fk_religion FOREIGN KEY (religion_id) REFERENCES Lkp_Religion(religion_id),
    CONSTRAINT fk_language FOREIGN KEY (language_id) REFERENCES Lkp_Language(language_id)
);


CREATE TABLE IF NOT EXISTS Lkp_Education_Level (
    education_id INT PRIMARY KEY,
    name VARCHAR(50)
);
CREATE TABLE IF NOT EXISTS Lkp_Employment_Status (
    employment_id INT PRIMARY KEY,
    name VARCHAR(50)
);


-- Disability (Tables 16, 17)
CREATE TABLE IF NOT EXISTS Individual_Disability (
    disability_id INT AUTO_INCREMENT,
    
    disability_type VARCHAR(100), -- e.g., Visual, Auditory, Physical
    severity_level VARCHAR(50),
    
    individual_id INT NOT NULL,
	CONSTRAINT pk_individual_disability PRIMARY KEY (disability_id),
    CONSTRAINT fk_individual FOREIGN KEY (individual_id) REFERENCES Individual(individual_id)
);

-- Migration (Tables 18, 19)
CREATE TABLE IF NOT EXISTS Migration_History (
    migration_id INT AUTO_INCREMENT,
    individual_id INT NOT NULL,
    previous_district_id INT, -- Links back to District table
    migration_reason VARCHAR(100), -- e.g., Employment, Marriage, Education
    year_of_migration INT,
    CONSTRAINT pk_migration_history PRIMARY KEY (migration_id),
    CONSTRAINT fkindividual FOREIGN KEY (individual_id) REFERENCES Individual(individual_id)
);



-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++






CREATE DATABASE IF NOT EXISTS PakistanCensusDatabase;
USE PakistanCensusDatabase;

-- ============================================
-- GEOGRAPHIC HIERARCHY TABLES
-- ============================================

CREATE TABLE IF NOT EXISTS Province (
    province_id INT AUTO_INCREMENT,
    province_name VARCHAR(100) NOT NULL UNIQUE,
    CONSTRAINT pk_province PRIMARY KEY (province_id)
);

CREATE TABLE IF NOT EXISTS Division (
    division_id INT AUTO_INCREMENT,
    division_name VARCHAR(100) NOT NULL,
    province_id INT NOT NULL,
    CONSTRAINT pk_division PRIMARY KEY (division_id),
    CONSTRAINT fk_division_province FOREIGN KEY (province_id) 
        REFERENCES Province(province_id) ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT uq_division UNIQUE (division_name, province_id)
);

CREATE TABLE IF NOT EXISTS District (
    district_id INT AUTO_INCREMENT,
    district_name VARCHAR(100) NOT NULL,
    division_id INT NOT NULL,
    CONSTRAINT pk_district PRIMARY KEY (district_id),
    CONSTRAINT fk_district_division FOREIGN KEY (division_id) 
        REFERENCES Division(division_id) ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT uq_district UNIQUE (district_name, division_id)
);

CREATE TABLE IF NOT EXISTS Tehsil (
    tehsil_id INT AUTO_INCREMENT,
    tehsil_name VARCHAR(100) NOT NULL,
    district_id INT NOT NULL,
    CONSTRAINT pk_tehsil PRIMARY KEY (tehsil_id),
    CONSTRAINT fk_tehsil_district FOREIGN KEY (district_id) 
        REFERENCES District(district_id) ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT uq_tehsil UNIQUE (tehsil_name, district_id)
);

CREATE TABLE IF NOT EXISTS Union_Council (
    union_council_id INT AUTO_INCREMENT,
    union_council_name VARCHAR(100) NOT NULL,
    tehsil_id INT NOT NULL,
    CONSTRAINT pk_union_council PRIMARY KEY (union_council_id),
    CONSTRAINT fk_union_council_tehsil FOREIGN KEY (tehsil_id) 
        REFERENCES Tehsil(tehsil_id) ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT uq_union_council UNIQUE (union_council_name, tehsil_id)
);

CREATE TABLE IF NOT EXISTS Census_Block (
    census_block_id INT AUTO_INCREMENT,
    census_block_code VARCHAR(20) NOT NULL UNIQUE,
    union_council_id INT NOT NULL,
    is_urban BOOLEAN NOT NULL,
    area_sq_km DECIMAL(10, 2),
    estimated_household_count INT DEFAULT 0 CHECK (estimated_household_count >= 0),
    description TEXT,
    CONSTRAINT pk_census_block PRIMARY KEY (census_block_id),
    CONSTRAINT fk_census_block_uc FOREIGN KEY (union_council_id) 
        REFERENCES Union_Council(union_council_id) ON DELETE RESTRICT ON UPDATE CASCADE
);

-- ============================================
-- DEMOGRAPHIC DIMENSION TABLES
-- ============================================

CREATE TABLE IF NOT EXISTS Religion (
    religion_id INT AUTO_INCREMENT,
    religion_name VARCHAR(100) NOT NULL UNIQUE,
    CONSTRAINT pk_religion PRIMARY KEY (religion_id)
);

CREATE TABLE IF NOT EXISTS Nationality (
    nationality_id INT AUTO_INCREMENT,
    nationality_name VARCHAR(100) NOT NULL UNIQUE,
    CONSTRAINT pk_nationality PRIMARY KEY (nationality_id)
);

CREATE TABLE IF NOT EXISTS Mother_Tongue (
    tongue_id INT AUTO_INCREMENT,
    tongue_name VARCHAR(100) NOT NULL UNIQUE,
    CONSTRAINT pk_mother_tongue PRIMARY KEY (tongue_id)
);

CREATE TABLE IF NOT EXISTS Marital_Status (
    marital_status_id INT AUTO_INCREMENT,
    status_name VARCHAR(50) NOT NULL UNIQUE,
    CONSTRAINT pk_marital_status PRIMARY KEY (marital_status_id)
);

CREATE TABLE IF NOT EXISTS Relationship_To_Head (
    relation_id INT AUTO_INCREMENT,
    relation_name VARCHAR(100) NOT NULL UNIQUE,
    CONSTRAINT pk_relationship_to_head PRIMARY KEY (relation_id)
);

CREATE TABLE IF NOT EXISTS Age_Group (
    age_group_id INT AUTO_INCREMENT,
    min_age INT NOT NULL,
    max_age INT NOT NULL,
    group_label VARCHAR(50) NOT NULL UNIQUE,
    CONSTRAINT pk_age_group PRIMARY KEY (age_group_id),
    CONSTRAINT chk_age_range CHECK (min_age <= max_age)
);

-- ============================================
-- HOUSING FACILITIES DIMENSION TABLES
-- ============================================

CREATE TABLE IF NOT EXISTS Structure_Type (
    structure_type_id INT AUTO_INCREMENT,
    type_name VARCHAR(100) NOT NULL UNIQUE,
    description TEXT,
    CONSTRAINT pk_structure_type PRIMARY KEY (structure_type_id)
);

CREATE TABLE IF NOT EXISTS Water_Source (
    water_source_id INT AUTO_INCREMENT,
    source_name VARCHAR(100) NOT NULL UNIQUE,
    CONSTRAINT pk_water_source PRIMARY KEY (water_source_id)
);

CREATE TABLE IF NOT EXISTS Lighting_Source (
    lighting_source_id INT AUTO_INCREMENT,
    source_name VARCHAR(100) NOT NULL UNIQUE,
    CONSTRAINT pk_lighting_source PRIMARY KEY (lighting_source_id)
);

CREATE TABLE IF NOT EXISTS Cooking_Fuel (
    cooking_fuel_id INT AUTO_INCREMENT,
    fuel_name VARCHAR(100) NOT NULL UNIQUE,
    CONSTRAINT pk_cooking_fuel PRIMARY KEY (cooking_fuel_id)
);

CREATE TABLE IF NOT EXISTS Toilet_Type (
    toilet_type_id INT AUTO_INCREMENT,
    type_name VARCHAR(100) NOT NULL UNIQUE,
    CONSTRAINT pk_toilet_type PRIMARY KEY (toilet_type_id)
);

CREATE TABLE IF NOT EXISTS Kitchen_Status (
    kitchen_status_id INT AUTO_INCREMENT,
    status_name VARCHAR(100) NOT NULL UNIQUE,
    CONSTRAINT pk_kitchen_status PRIMARY KEY (kitchen_status_id)
);

CREATE TABLE IF NOT EXISTS Washroom_Status (
    washroom_status_id INT AUTO_INCREMENT,
    status_name VARCHAR(100) NOT NULL UNIQUE,
    CONSTRAINT pk_washroom_status PRIMARY KEY (washroom_status_id)
);

CREATE TABLE IF NOT EXISTS Tenure_Status (
    tenure_status_id INT AUTO_INCREMENT,
    status_name VARCHAR(100) NOT NULL UNIQUE,
    CONSTRAINT pk_tenure_status PRIMARY KEY (tenure_status_id)
);

-- ============================================
-- PERSON DIMENSION TABLES
-- ============================================

CREATE TABLE IF NOT EXISTS Educational_Attainment (
    education_id INT AUTO_INCREMENT,
    level_name VARCHAR(100) NOT NULL UNIQUE,
    years_completed INT,
    CONSTRAINT pk_educational_attainment PRIMARY KEY (education_id)
);

CREATE TABLE IF NOT EXISTS Employment_Status (
    employment_status_id INT AUTO_INCREMENT,
    status_name VARCHAR(100) NOT NULL UNIQUE,
    CONSTRAINT pk_employment_status PRIMARY KEY (employment_status_id)
);

CREATE TABLE IF NOT EXISTS Disability_Type (
    disability_type_id INT AUTO_INCREMENT,
    disability_name VARCHAR(100) NOT NULL UNIQUE,
    functional_limitation TEXT,
    CONSTRAINT pk_disability_type PRIMARY KEY (disability_type_id)
);

CREATE TABLE IF NOT EXISTS Migration_Reason (
    migration_reason_id INT AUTO_INCREMENT,
    reason_name VARCHAR(100) NOT NULL UNIQUE,
    CONSTRAINT pk_migration_reason PRIMARY KEY (migration_reason_id)
);

-- ============================================
-- CORE FACT TABLES
-- ============================================

CREATE TABLE IF NOT EXISTS Structure (
    structure_id INT AUTO_INCREMENT,
    census_block_id INT NOT NULL,
    structure_type_id INT NOT NULL,
    is_institutional BOOLEAN DEFAULT FALSE,
    gps_latitude DECIMAL(9, 6),
    gps_longitude DECIMAL(9, 6),
    created_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT pk_structure PRIMARY KEY (structure_id),
    CONSTRAINT fk_structure_census_block FOREIGN KEY (census_block_id) 
        REFERENCES Census_Block(census_block_id) ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT fk_structure_type FOREIGN KEY (structure_type_id) 
        REFERENCES Structure_Type(structure_type_id) ON DELETE RESTRICT ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS Household (
    household_id INT AUTO_INCREMENT,
    structure_id INT NOT NULL,
    census_block_id INT NOT NULL,
    number_of_rooms INT NOT NULL CHECK (number_of_rooms >= 1),
    residential_status_id INT NOT NULL,
    owner_gender ENUM('Male', 'Female', 'Unknown') DEFAULT 'Unknown',
    household_size INT DEFAULT 0 CHECK (household_size >= 0),
    gps_latitude DECIMAL(9, 6),
    gps_longitude DECIMAL(9, 6),
    created_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT pk_household PRIMARY KEY (household_id),
    CONSTRAINT fk_household_structure FOREIGN KEY (structure_id) 
        REFERENCES Structure(structure_id) ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT fk_household_census_block FOREIGN KEY (census_block_id) 
        REFERENCES Census_Block(census_block_id) ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT fk_household_tenure_status FOREIGN KEY (residential_status_id) 
        REFERENCES Tenure_Status(tenure_status_id) ON DELETE RESTRICT ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS Person (
    person_id INT AUTO_INCREMENT,
    household_id INT NOT NULL,
    census_block_id INT NOT NULL,
    sex ENUM('Male', 'Female', 'Other') NOT NULL,
    date_of_birth DATE,
    age_calculated INT GENERATED ALWAYS AS (YEAR(CURDATE()) - YEAR(date_of_birth)) STORED,
    religion_id INT,
    nationality_id INT,
    mother_tongue_id INT,
    marital_status_id INT,
    relation_to_head_id INT NOT NULL,
    is_literacy BOOLEAN DEFAULT FALSE,
    created_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT pk_person PRIMARY KEY (person_id),
    CONSTRAINT fk_person_household FOREIGN KEY (household_id) 
        REFERENCES Household(household_id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_person_census_block FOREIGN KEY (census_block_id) 
        REFERENCES Census_Block(census_block_id) ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT fk_person_religion FOREIGN KEY (religion_id) 
        REFERENCES Religion(religion_id) ON DELETE SET NULL ON UPDATE CASCADE,
    CONSTRAINT fk_person_nationality FOREIGN KEY (nationality_id) 
        REFERENCES Nationality(nationality_id) ON DELETE SET NULL ON UPDATE CASCADE,
    CONSTRAINT fk_person_mother_tongue FOREIGN KEY (mother_tongue_id) 
        REFERENCES Mother_Tongue(tongue_id) ON DELETE SET NULL ON UPDATE CASCADE,
    CONSTRAINT fk_person_marital_status FOREIGN KEY (marital_status_id) 
        REFERENCES Marital_Status(marital_status_id) ON DELETE SET NULL ON UPDATE CASCADE,
    CONSTRAINT fk_person_relation_to_head FOREIGN KEY (relation_to_head_id) 
        REFERENCES Relationship_To_Head(relation_id) ON DELETE RESTRICT ON UPDATE CASCADE
);

-- ============================================
-- HOUSEHOLD FACILITIES (M:M JUNCTION TABLES)
-- ============================================

CREATE TABLE IF NOT EXISTS Household_Kitchen (
    household_kitchen_id INT AUTO_INCREMENT,
    household_id INT NOT NULL,
    kitchen_status_id INT NOT NULL,
    location_type ENUM('Inside', 'Outside', 'Separate', 'None') DEFAULT 'None',
    CONSTRAINT pk_household_kitchen PRIMARY KEY (household_kitchen_id),
    CONSTRAINT fk_household_kitchen_household FOREIGN KEY (household_id) 
        REFERENCES Household(household_id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_household_kitchen_status FOREIGN KEY (kitchen_status_id) 
        REFERENCES Kitchen_Status(kitchen_status_id) ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT uq_household_kitchen UNIQUE (household_id, kitchen_status_id)
);

CREATE TABLE IF NOT EXISTS Household_Washroom (
    household_washroom_id INT AUTO_INCREMENT,
    household_id INT NOT NULL,
    washroom_status_id INT NOT NULL,
    CONSTRAINT pk_household_washroom PRIMARY KEY (household_washroom_id),
    CONSTRAINT fk_household_washroom_household FOREIGN KEY (household_id) 
        REFERENCES Household(household_id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_household_washroom_status FOREIGN KEY (washroom_status_id) 
        REFERENCES Washroom_Status(washroom_status_id) ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT uq_household_washroom UNIQUE (household_id, washroom_status_id)
);

CREATE TABLE IF NOT EXISTS Household_Toilet (
    household_toilet_id INT AUTO_INCREMENT,
    household_id INT NOT NULL,
    toilet_type_id INT NOT NULL,
    CONSTRAINT pk_household_toilet PRIMARY KEY (household_toilet_id),
    CONSTRAINT fk_household_toilet_household FOREIGN KEY (household_id) 
        REFERENCES Household(household_id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_household_toilet_type FOREIGN KEY (toilet_type_id) 
        REFERENCES Toilet_Type(toilet_type_id) ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT uq_household_toilet UNIQUE (household_id, toilet_type_id)
);

CREATE TABLE IF NOT EXISTS Household_Water_Source (
    household_water_id INT AUTO_INCREMENT,
    household_id INT NOT NULL,
    water_source_id INT NOT NULL,
    is_primary BOOLEAN DEFAULT FALSE,
    CONSTRAINT pk_household_water_source PRIMARY KEY (household_water_id),
    CONSTRAINT fk_household_water_household FOREIGN KEY (household_id) 
        REFERENCES Household(household_id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_household_water_source FOREIGN KEY (water_source_id) 
        REFERENCES Water_Source(water_source_id) ON DELETE RESTRICT ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS Household_Lighting_Source (
    household_lighting_id INT AUTO_INCREMENT,
    household_id INT NOT NULL,
    lighting_source_id INT NOT NULL,
    is_primary BOOLEAN DEFAULT FALSE,
    CONSTRAINT pk_household_lighting_source PRIMARY KEY (household_lighting_id),
    CONSTRAINT fk_household_lighting_household FOREIGN KEY (household_id) 
        REFERENCES Household(household_id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_household_lighting_source FOREIGN KEY (lighting_source_id) 
        REFERENCES Lighting_Source(lighting_source_id) ON DELETE RESTRICT ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS Household_Cooking_Fuel (
    household_fuel_id INT AUTO_INCREMENT,
    household_id INT NOT NULL,
    cooking_fuel_id INT NOT NULL,
    is_primary BOOLEAN DEFAULT FALSE,
    CONSTRAINT pk_household_cooking_fuel PRIMARY KEY (household_fuel_id),
    CONSTRAINT fk_household_fuel_household FOREIGN KEY (household_id) 
        REFERENCES Household(household_id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_household_cooking_fuel FOREIGN KEY (cooking_fuel_id) 
        REFERENCES Cooking_Fuel(cooking_fuel_id) ON DELETE RESTRICT ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS Household_Housing_Type (
    household_housing_type_id INT AUTO_INCREMENT,
    household_id INT NOT NULL,
    housing_type_id INT NOT NULL,
    CONSTRAINT pk_household_housing_type PRIMARY KEY (household_housing_type_id),
    CONSTRAINT fk_household_housing_household FOREIGN KEY (household_id) 
        REFERENCES Household(household_id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_household_housing_type FOREIGN KEY (housing_type_id) 
        REFERENCES Structure_Type(structure_type_id) ON DELETE RESTRICT ON UPDATE CASCADE,
    CONSTRAINT uq_household_housing_type UNIQUE (household_id, housing_type_id)
);

-- ============================================
-- PERSON ATTRIBUTES (M:M JUNCTION TABLES)
-- ============================================

CREATE TABLE IF NOT EXISTS Person_Education (
    person_education_id INT AUTO_INCREMENT,
    person_id INT NOT NULL,
    education_id INT NOT NULL,
    completion_year INT,
    institution_name VARCHAR(255),
    CONSTRAINT pk_person_education PRIMARY KEY (person_education_id),
    CONSTRAINT fk_person_education_person FOREIGN KEY (person_id) 
        REFERENCES Person(person_id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_person_education_education FOREIGN KEY (education_id) 
        REFERENCES Educational_Attainment(education_id) ON DELETE RESTRICT ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS Person_Employment (
    person_employment_id INT AUTO_INCREMENT,
    person_id INT NOT NULL,
    employment_status_id INT NOT NULL,
    occupation VARCHAR(100),
    employer VARCHAR(100),
    industry_sector VARCHAR(100),
    hours_per_week INT,
    monthly_income DECIMAL(10, 2),
    employment_start_date DATE,
    CONSTRAINT pk_person_employment PRIMARY KEY (person_employment_id),
    CONSTRAINT fk_person_employment_person FOREIGN KEY (person_id) 
        REFERENCES Person(person_id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_person_employment_status FOREIGN KEY (employment_status_id) 
        REFERENCES Employment_Status(employment_status_id) ON DELETE RESTRICT ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS Person_Disability (
    person_disability_id INT AUTO_INCREMENT,
    person_id INT NOT NULL,
    disability_type_id INT NOT NULL,
    severity_level ENUM('Mild', 'Moderate', 'Severe', 'Unknown') DEFAULT 'Unknown',
    assistance_required BOOLEAN DEFAULT FALSE,
    CONSTRAINT pk_person_disability PRIMARY KEY (person_disability_id),
    CONSTRAINT fk_person_disability_person FOREIGN KEY (person_id) 
        REFERENCES Person(person_id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_person_disability_type FOREIGN KEY (disability_type_id) 
        REFERENCES Disability_Type(disability_type_id) ON DELETE RESTRICT ON UPDATE CASCADE
);

CREATE TABLE IF NOT EXISTS Person_Migration (
    person_migration_id INT AUTO_INCREMENT,
    person_id INT NOT NULL,
    origin_location_id INT,
    destination_location_id INT,
    migration_reason_id INT,
    migration_date DATE,
    is_seasonal BOOLEAN DEFAULT FALSE,
    duration_months INT,
    CONSTRAINT pk_person_migration PRIMARY KEY (person_migration_id),
    CONSTRAINT fk_person_migration_person FOREIGN KEY (person_id) 
        REFERENCES Person(person_id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_person_migration_reason FOREIGN KEY (migration_reason_id) 
        REFERENCES Migration_Reason(migration_reason_id) ON DELETE SET NULL ON UPDATE CASCADE,
    CONSTRAINT fk_person_migration_origin FOREIGN KEY (origin_location_id) 
        REFERENCES Census_Block(census_block_id) ON DELETE SET NULL ON UPDATE CASCADE,
    CONSTRAINT fk_person_migration_destination FOREIGN KEY (destination_location_id) 
        REFERENCES Census_Block(census_block_id) ON DELETE SET NULL ON UPDATE CASCADE
);

-- ============================================
-- SPECIAL STRUCTURES
-- ============================================

CREATE TABLE IF NOT EXISTS Institution (
    institution_id INT AUTO_INCREMENT,
    structure_id INT NOT NULL,
    institution_type VARCHAR(100) NOT NULL,
    population_count INT DEFAULT 0,
    notes TEXT,
    CONSTRAINT pk_institution PRIMARY KEY (institution_id),
    CONSTRAINT fk_institution_structure FOREIGN KEY (structure_id) 
        REFERENCES Structure(structure_id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT uq_institution UNIQUE (structure_id)
);

CREATE TABLE IF NOT EXISTS Economic_Unit (
    economic_unit_id INT AUTO_INCREMENT,
    structure_id INT NOT NULL,
    unit_type VARCHAR(100) NOT NULL,
    employer_name VARCHAR(255),
    employees_count INT DEFAULT 0,
    establishment_date DATE,
    CONSTRAINT pk_economic_unit PRIMARY KEY (economic_unit_id),
    CONSTRAINT fk_economic_unit_structure FOREIGN KEY (structure_id) 
        REFERENCES Structure(structure_id) ON DELETE CASCADE ON UPDATE CASCADE
);

-- ============================================
-- INDEXES FOR PERFORMANCE
-- ============================================

CREATE INDEX idx_person_household ON Person(household_id);
CREATE INDEX idx_person_census_block ON Person(census_block_id);
CREATE INDEX idx_person_religion ON Person(religion_id);
CREATE INDEX idx_person_nationality ON Person(nationality_id);
CREATE INDEX idx_person_marital_status ON Person(marital_status_id);
CREATE INDEX idx_household_structure ON Household(structure_id);
CREATE INDEX idx_household_census_block ON Household(census_block_id);
CREATE INDEX idx_household_water ON Household_Water_Source(household_id);
CREATE INDEX idx_household_lighting ON Household_Lighting_Source(household_id);
CREATE INDEX idx_household_fuel ON Household_Cooking_Fuel(household_id);
CREATE INDEX idx_structure_census_block ON Structure(census_block_id);
CREATE INDEX idx_census_block_uc ON Census_Block(union_council_id);
CREATE INDEX idx_person_education_person ON Person_Education(person_id);
CREATE INDEX idx_person_employment_person ON Person_Employment(person_id);
CREATE INDEX idx_person_disability_person ON Person_Disability(person_id);
CREATE INDEX idx_person_migration_person ON Person_Migration(person_id);



