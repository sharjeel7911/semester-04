CREATE DATABASE Pakistan_Census_2023;
USE Pakistan_Census_2023;
CREATE TABLE Province (
    province_id TINYINT AUTO_INCREMENT,
    province_name VARCHAR(100) NOT NULL UNIQUE,
    PRIMARY KEY (province_id)
);
CREATE TABLE Division (
    division_id SMALLINT AUTO_INCREMENT,
    division_name VARCHAR(100) NOT NULL,
    province_id TINYINT NOT NULL,

    PRIMARY KEY (division_id),

    FOREIGN KEY (province_id)
    REFERENCES Province(province_id)
);
CREATE TABLE District (
    district_id SMALLINT AUTO_INCREMENT,
    district_name VARCHAR(100) NOT NULL,
    division_id SMALLINT NOT NULL,

    PRIMARY KEY (district_id),

    FOREIGN KEY (division_id)
    REFERENCES Division(division_id)
);
CREATE TABLE Tehsil (
    tehsil_id SMALLINT AUTO_INCREMENT,
    tehsil_name VARCHAR(100) NOT NULL,
    district_id SMALLINT NOT NULL,

    PRIMARY KEY (tehsil_id),

    FOREIGN KEY (district_id)
    REFERENCES District(district_id)
);
CREATE TABLE Biological_Sex (
    sex_id TINYINT AUTO_INCREMENT,
    sex_name VARCHAR(30) NOT NULL UNIQUE,

    PRIMARY KEY (sex_id)
);
CREATE TABLE Religion (
    religion_id TINYINT AUTO_INCREMENT,
    religion_name VARCHAR(100) NOT NULL UNIQUE,

    PRIMARY KEY (religion_id)
);
CREATE TABLE Nationality (
    nationality_id TINYINT AUTO_INCREMENT,
    country_name VARCHAR(100) NOT NULL,
    citizenship_status VARCHAR(50),

    PRIMARY KEY (nationality_id)
);
CREATE TABLE Education_Level (
    education_level_id TINYINT AUTO_INCREMENT,
    level_name VARCHAR(100) NOT NULL,

    PRIMARY KEY (education_level_id)
);
CREATE TABLE Employment_Status (
    employment_status_id TINYINT AUTO_INCREMENT,
    status_name VARCHAR(100) NOT NULL,

    PRIMARY KEY (employment_status_id)
);
CREATE TABLE Marital_Status (
    marital_status_id TINYINT AUTO_INCREMENT,
    status_name VARCHAR(50) NOT NULL,

    PRIMARY KEY (marital_status_id)
);
CREATE TABLE Household (

    household_id INT AUTO_INCREMENT,

    household_sub_token VARCHAR(10),

    household_size INT NOT NULL
    CHECK (household_size > 0),

    number_of_rooms INT
    CHECK (number_of_rooms > 0),

    created_date TIMESTAMP
    DEFAULT CURRENT_TIMESTAMP,

    PRIMARY KEY (household_id)
);
CREATE TABLE Person (

    person_id INT AUTO_INCREMENT,

    first_name VARCHAR(100) NOT NULL,

    last_name VARCHAR(100) NOT NULL,

    cnic_number VARCHAR(20)
    UNIQUE NOT NULL,

    date_of_birth DATE NOT NULL,

    is_literate BOOLEAN DEFAULT FALSE,

    currently_attending_school BOOLEAN DEFAULT FALSE,

    monthly_income DECIMAL(10,2)
    CHECK (monthly_income >= 0),

    created_date TIMESTAMP
    DEFAULT CURRENT_TIMESTAMP,

    household_id INT,

    sex_id TINYINT,

    nationality_id TINYINT,

    religion_id TINYINT,

    education_level_id TINYINT,

    employment_status_id TINYINT,

    marital_status_id TINYINT,

    PRIMARY KEY(person_id),

    FOREIGN KEY (household_id)
    REFERENCES Household(household_id)
    ON DELETE CASCADE,

    FOREIGN KEY (sex_id)
    REFERENCES Biological_Sex(sex_id),

    FOREIGN KEY (nationality_id)
    REFERENCES Nationality(nationality_id),

    FOREIGN KEY (religion_id)
    REFERENCES Religion(religion_id)
    ON DELETE SET NULL,

    FOREIGN KEY (education_level_id)
    REFERENCES Education_Level(education_level_id),

    FOREIGN KEY (employment_status_id)
    REFERENCES Employment_Status(employment_status_id),

    FOREIGN KEY (marital_status_id)
    REFERENCES Marital_Status(marital_status_id)
);
CREATE TABLE Union_Council (
    union_council_id INT AUTO_INCREMENT,
    union_council_name VARCHAR(100) NOT NULL,
    union_council_classification_id TINYINT,
    tehsil_id SMALLINT NOT NULL,

    PRIMARY KEY (union_council_id),

    FOREIGN KEY (tehsil_id)
    REFERENCES Tehsil(tehsil_id)
);
CREATE TABLE Census_Block (

    census_block_id INT AUTO_INCREMENT,

    census_block_code VARCHAR(20)
    UNIQUE NOT NULL,

    estimated_household_count INT,

    is_urban BOOLEAN,

    area_sq_km DECIMAL(10,2),

    union_council_id INT,

    PRIMARY KEY(census_block_id),

    FOREIGN KEY(union_council_id)
    REFERENCES Union_Council(union_council_id)
);
CREATE TABLE Census_Staff (

    staff_id INT AUTO_INCREMENT,

    first_name VARCHAR(100),

    last_name VARCHAR(100),

    staff_role VARCHAR(100),

    contact_number VARCHAR(20),

    email VARCHAR(100),

    employment_date DATE,

    assigned_census_block_id INT,

    supervisor_id INT,

    PRIMARY KEY(staff_id),

    FOREIGN KEY(assigned_census_block_id)
    REFERENCES Census_Block(census_block_id),

    FOREIGN KEY(supervisor_id)
    REFERENCES Census_Staff(staff_id)
    ON DELETE SET NULL
);
CREATE TABLE Water_Source(
water_source_id TINYINT AUTO_INCREMENT,
source_name VARCHAR(100) NOT NULL,
PRIMARY KEY(water_source_id)
);
CREATE TABLE Lighting_Source(
lighting_source_id TINYINT AUTO_INCREMENT,
source_name VARCHAR(100),
PRIMARY KEY(lighting_source_id)
);
CREATE TABLE Cooking_Fuel_Source(
fuel_source_id TINYINT AUTO_INCREMENT,
fuel_source_name VARCHAR(100),
PRIMARY KEY(fuel_source_id)
);
CREATE TABLE Washroom_Status(
washroom_status_id TINYINT AUTO_INCREMENT,
status_name VARCHAR(100),
PRIMARY KEY(washroom_status_id)
);
CREATE TABLE Kitchen_Status(
kitchen_status_id TINYINT AUTO_INCREMENT,
status_name VARCHAR(100),
PRIMARY KEY(kitchen_status_id)
);
CREATE TABLE Structure (

structure_id INT AUTO_INCREMENT,

structure_address_no VARCHAR(50),

gps_latitude DECIMAL(9,6),

gps_longitude DECIMAL(9,6),

created_date TIMESTAMP
DEFAULT CURRENT_TIMESTAMP,

structure_type_id TINYINT,

water_source_id TINYINT,

lighting_source_id TINYINT,

fuel_source_id TINYINT,

washroom_status_id TINYINT,

kitchen_status_id TINYINT,

census_block_id INT,

PRIMARY KEY(structure_id),

FOREIGN KEY(census_block_id)
REFERENCES Census_Block(census_block_id)
);
CREATE TABLE Structure_Residential(

structure_id INT,

total_residential_units INT,

PRIMARY KEY(structure_id),

FOREIGN KEY(structure_id)
REFERENCES Structure(structure_id)
ON DELETE CASCADE
);
CREATE TABLE Occupation(
occupation_id SMALLINT AUTO_INCREMENT,
occupation_name VARCHAR(150),
PRIMARY KEY(occupation_id)
);
CREATE TABLE Industry(
industry_id SMALLINT AUTO_INCREMENT,
industry_name VARCHAR(150),
PRIMARY KEY(industry_id)
);
CREATE TABLE Disability_Type(
disability_type_id TINYINT AUTO_INCREMENT,
disability_name VARCHAR(100),
PRIMARY KEY(disability_type_id)
);
CREATE TABLE Person_Disability(

person_disability_id INT AUTO_INCREMENT,

disability_type_id TINYINT,

person_id INT,

PRIMARY KEY(person_disability_id),

FOREIGN KEY(person_id)
REFERENCES Person(person_id)
ON DELETE CASCADE,

FOREIGN KEY(disability_type_id)
REFERENCES Disability_Type(disability_type_id)
);
CREATE TABLE Migration_History(

migration_id INT AUTO_INCREMENT,

migration_reason VARCHAR(100),

year_of_migration INT,

person_id INT,

previous_district_id SMALLINT,

PRIMARY KEY(migration_id),

FOREIGN KEY(person_id)
REFERENCES Person(person_id)
ON DELETE CASCADE
);
CREATE TABLE Mother_Tongue(
    mother_tongue_id TINYINT AUTO_INCREMENT,
    language_name VARCHAR(100) NOT NULL UNIQUE,
    PRIMARY KEY(mother_tongue_id)
);
CREATE TABLE Relationship_Type(
    relationship_type_id TINYINT AUTO_INCREMENT,
    relationship_name VARCHAR(100) NOT NULL,
    PRIMARY KEY(relationship_type_id)
);
CREATE TABLE Union_Council_Classification(
    union_council_classification_id TINYINT AUTO_INCREMENT,
    classification_name VARCHAR(50) NOT NULL,
    PRIMARY KEY(union_council_classification_id)
);
CREATE TABLE Census_Cycle(
    census_id TINYINT AUTO_INCREMENT,
    census_year YEAR NOT NULL,
    census_name VARCHAR(100),
    PRIMARY KEY(census_id)
);
CREATE TABLE Structure_Type(
    structure_type_id TINYINT AUTO_INCREMENT,
    structure_type_name VARCHAR(100),
    PRIMARY KEY(structure_type_id)
);
CREATE TABLE Commercial_Sector_Type(
    commercial_type_id TINYINT AUTO_INCREMENT,
    commercial_type_name VARCHAR(100),
    PRIMARY KEY(commercial_type_id)
);
CREATE TABLE Structure_Commercial(

    structure_id INT,

    commercial_type_id TINYINT,

    employee_count INT,

    annual_revenue DECIMAL(15,2),

    PRIMARY KEY(structure_id),

    FOREIGN KEY (structure_id)
    REFERENCES Structure(structure_id)
    ON DELETE CASCADE,

    FOREIGN KEY (commercial_type_id)
    REFERENCES Commercial_Sector_Type(commercial_type_id)

);
CREATE TABLE Structure_Institution(

    structure_id INT,

    institution_name VARCHAR(200),

    institution_type VARCHAR(100),

    registered_capacity INT,

    PRIMARY KEY(structure_id),

    FOREIGN KEY(structure_id)
    REFERENCES Structure(structure_id)
    ON DELETE CASCADE
);
CREATE TABLE Household_Category(
    household_category_id TINYINT AUTO_INCREMENT,
    category_name VARCHAR(100),
    PRIMARY KEY(household_category_id)
);
CREATE TABLE Residential_Status_Type(
    residential_status_type_id TINYINT AUTO_INCREMENT,
    status_name VARCHAR(100),
    PRIMARY KEY(residential_status_type_id)
);
INSERT IGNORE INTO Province(province_name)
VALUES
('Punjab'),
('Sindh'),
('KPK'),
('Balochistan'),
('Gilgit Baltistan');
INSERT INTO Division(division_name,province_id)
VALUES
('Lahore',1),
('Rawalpindi',1),
('Karachi',2),
('Hyderabad',2),
('Peshawar',3),
('Mardan',3),
('Quetta',4),
('Makran',4),
('Gilgit',5),
('Baltistan',5);
INSERT INTO District(district_name,division_id)
VALUES
('Lahore',1),
('Kasur',1),
('Rawalpindi',2),
('Attock',2),
('Karachi East',3),
('Karachi West',3),
('Peshawar',5),
('Mardan',6),
('Quetta',7),
('Gilgit',9);
INSERT INTO Tehsil(tehsil_name,district_id)
VALUES
('Lahore City',1),
('Model Town',1),
('Kasur City',2),
('Rawalpindi City',3),
('Attock City',4),
('Gulshan',5),
('Orangi',6),
('Peshawar City',7),
('Mardan City',8),
('Quetta City',9);
INSERT INTO Biological_Sex(sex_name)
VALUES
('Male'),
('Female');
INSERT INTO Religion(religion_name)
VALUES
('Islam'),
('Christianity'),
('Hinduism'),
('Sikhism'),
('Buddhism'),
('Jainism'),
('Parsi'),
('Bahai'),
('Judaism'),
('Other');
INSERT INTO Household
(household_sub_token,
household_size,
number_of_rooms)
VALUES
('H001',6,4),
('H002',5,3),
('H003',8,5);
INSERT INTO Education_Level(level_name)
VALUES
('No Education'),
('Primary'),
('Middle'),
('Matric'),
('Intermediate'),
('Bachelor'),
('Master'),
('MPhil'),
('PhD'),
('Other');
INSERT INTO Employment_Status(status_name)
VALUES
('Employed'),
('Unemployed'),
('Self Employed'),
('Government Employee'),
('Private Employee'),
('Student'),
('Retired'),
('Housewife'),
('Disabled'),
('Other');
INSERT INTO Marital_Status(status_name)
VALUES
('Single'),
('Married'),
('Widowed'),
('Divorced'),
('Separated'),
('Engaged'),
('Remarried'),
('Unknown'),
('Annulled'),
('Other');
INSERT INTO Nationality(country_name,citizenship_status)
VALUES
('Pakistan','Citizen'),
('Afghanistan','Resident'),
('China','Resident'),
('India','Resident'),
('Iran','Resident'),
('Turkey','Resident'),
('Saudi Arabia','Resident'),
('UAE','Resident'),
('UK','Resident'),
('USA','Resident');
INSERT INTO Person
(
first_name,last_name,cnic_number,
date_of_birth,is_literate,
monthly_income,
household_id,
sex_id,
religion_id,
nationality_id,
education_level_id,
employment_status_id,
marital_status_id
)
VALUES
('Ahmed','Raza','3520111111113','1988-01-01',1,60000,1,1,1,1,5,1,2),
('Fatima','Noor','3520111111114','1995-02-02',1,45000,1,2,1,1,6,5,1),
('Usman','Ali','3520111111115','1993-03-03',1,70000,1,1,1,1,6,1,2),
('Ayesha','Khan','3520111111116','1998-04-04',1,30000,1,2,1,1,5,5,1),
('Bilal','Ahmed','3520111111117','1991-05-05',1,80000,1,1,1,1,7,1,2),
('Hina','Raza','3520111111118','1996-06-06',1,35000,1,2,1,1,5,5,1),
('Saad','Malik','3520111111119','1987-07-07',1,90000,1,1,1,1,8,1,2),
('Zain','Khan','3520111111120','2000-08-08',1,25000,1,1,1,1,4,6,1),
('Maryam','Ali','3520111111121','1999-09-09',1,28000,1,2,1,1,4,6,1);
INSERT INTO Union_Council
(union_council_name,tehsil_id)
VALUES
('UC-1',1),
('UC-2',1),
('UC-3',2),
('UC-4',2),
('UC-5',3),
('UC-6',3),
('UC-7',4),
('UC-8',4),
('UC-9',5),
('UC-10',5);
SELECT * FROM Union_Council;
SELECT
(SELECT COUNT(*) FROM Province) AS Province,
(SELECT COUNT(*) FROM Division) AS Division,
(SELECT COUNT(*) FROM District) AS District,
(SELECT COUNT(*) FROM Tehsil) AS Tehsil,
(SELECT COUNT(*) FROM Union_Council) AS UnionCouncil,
(SELECT COUNT(*) FROM Census_Block) AS CensusBlock;

INSERT INTO Census_Block
(
census_block_code,
estimated_household_count,
is_urban,
area_sq_km,
union_council_id
)
VALUES
('CB001',250,TRUE,2.50,1),
('CB002',300,FALSE,3.20,2),
('CB003',280,TRUE,1.80,3),
('CB004',350,FALSE,4.50,4),
('CB005',220,TRUE,2.00,5),
('CB006',180,FALSE,3.10,6),
('CB007',275,TRUE,2.40,7),
('CB008',290,FALSE,4.20,8),
('CB009',240,TRUE,1.90,9),
('CB010',310,FALSE,5.00,10);
INSERT INTO Census_Staff
(
first_name,last_name,
staff_role,
contact_number,
email,
employment_date,
assigned_census_block_id
)
VALUES
('Ali','Khan','Enumerator','03001234567','ali@gmail.com','2023-01-01',1),
('Sara','Ahmed','Enumerator','03001234568','sara@gmail.com','2023-01-01',2),
('Bilal','Raza','Supervisor','03001234569','bilal@gmail.com','2023-01-01',3),
('Usman','Malik','Enumerator','03001234570','usman@gmail.com','2023-01-01',4),
('Ayesha','Noor','Enumerator','03001234571','ayesha@gmail.com','2023-01-01',5),
('Hamza','Iqbal','Supervisor','03001234572','hamza@gmail.com','2023-01-01',6),
('Fatima','Ali','Enumerator','03001234573','fatima@gmail.com','2023-01-01',7),
('Zain','Khan','Enumerator','03001234574','zain@gmail.com','2023-01-01',8),
('Hina','Raza','Enumerator','03001234575','hina@gmail.com','2023-01-01',9),
('Saad','Ahmed','Supervisor','03001234576','saad@gmail.com','2023-01-01',10);
INSERT INTO Water_Source(source_name)
VALUES
('Tap Water'),
('Tube Well'),
('Hand Pump'),
('Bore Water'),
('Canal'),
('River'),
('Spring'),
('Tanker'),
('Bottled Water'),
('Other');
INSERT INTO Lighting_Source(source_name)
VALUES
('Electricity'),
('Solar'),
('Generator'),
('Gas Lamp'),
('Kerosene Lamp'),
('Battery'),
('UPS'),
('Wind'),
('Mixed'),
('Other');
INSERT INTO Cooking_Fuel_Source(fuel_source_name)
VALUES
('Natural Gas'),
('LPG'),
('Wood'),
('Coal'),
('Biogas'),
('Electric'),
('Kerosene'),
('Charcoal'),
('Solar'),
('Other');
INSERT INTO Kitchen_Status(status_name)
VALUES
('Separate'),
('Shared'),
('Open'),
('Indoor'),
('Outdoor'),
('Temporary'),
('Permanent'),
('Modern'),
('Traditional'),
('Other');
INSERT INTO Structure
(
structure_address_no,
gps_latitude,
gps_longitude,
census_block_id
)
VALUES
('A-101',31.5204,74.3587,1),
('A-102',31.5205,74.3588,2),
('A-103',31.5206,74.3589,3),
('A-104',31.5207,74.3590,4),
('A-105',31.5208,74.3591,5),
('A-106',31.5209,74.3592,6),
('A-107',31.5210,74.3593,7),
('A-108',31.5211,74.3594,8),
('A-109',31.5212,74.3595,9),
('A-110',31.5213,74.3596,10);
INSERT INTO Structure_Residential
VALUES
(1,2),(2,3),(3,1),(4,2),(5,4),
(6,3),(7,2),(8,5),(9,1),(10,2);
INSERT INTO Occupation(occupation_name)
VALUES
('Teacher'),
('Doctor'),
('Engineer'),
('Farmer'),
('Driver'),
('Shopkeeper'),
('Lawyer'),
('Police Officer'),
('Nurse'),
('Student');
INSERT INTO Industry(industry_name)
VALUES
('Education'),
('Healthcare'),
('Construction'),
('Agriculture'),
('Transport'),
('Retail'),
('Legal'),
('Security'),
('Manufacturing'),
('IT');
INSERT INTO Disability_Type(disability_name)
VALUES
('Visual'),
('Hearing'),
('Speech'),
('Physical'),
('Mental'),
('Learning'),
('Autism'),
('Multiple'),
('Temporary'),
('Other');
INSERT INTO Migration_History
(
migration_reason,
year_of_migration,
person_id,
previous_district_id
)
VALUES
('Job',2018,1,1),
('Marriage',2020,3,3),
('Business',2017,4,4),
('Transfer',2016,5,5),
('Study',2015,6,1),
('Employment',2021,7,2),
('Family',2022,8,3),
('Health',2020,9,4);
SELECT person_id FROM Person;
INSERT INTO Mother_Tongue(language_name)
VALUES
('Punjabi'),
('Sindhi'),
('Pashto'),
('Balochi'),
('Urdu'),
('Saraiki'),
('Hindko'),
('Kashmiri'),
('Shina'),
('Other');
INSERT INTO Relationship_Type(relationship_name)
VALUES
('Head'),
('Spouse'),
('Son'),
('Daughter'),
('Father'),
('Mother'),
('Brother'),
('Sister'),
('Grandparent'),
('Other');
INSERT INTO Union_Council_Classification(classification_name)
VALUES
('Urban'),
('Rural'),
('Metropolitan'),
('Municipal'),
('Town'),
('City'),
('Suburban'),
('Industrial'),
('Mixed'),
('Other');
INSERT INTO Census_Cycle(census_year,census_name)
VALUES
(1951,'Population Census'),
(1961,'Population Census'),
(1972,'Population Census'),
(1981,'Population Census'),
(1998,'Population Census'),
(2017,'Population Census'),
(2023,'Digital Census'),
(2028,'Projected Census'),
(2033,'Projected Census'),
(2038,'Projected Census');
INSERT INTO Structure_Type(structure_type_name)
VALUES
('Residential'),
('Commercial'),
('Industrial'),
('Educational'),
('Healthcare'),
('Religious'),
('Government'),
('Mixed'),
('Agricultural'),
('Other');
INSERT INTO Commercial_Sector_Type(commercial_type_name)
VALUES
('Retail'),
('Wholesale'),
('Manufacturing'),
('Banking'),
('Transport'),
('Hospitality'),
('Education'),
('Healthcare'),
('IT'),
('Other');
INSERT INTO Structure_Commercial
VALUES
(1,1,10,500000),
(2,2,12,650000),
(3,3,20,900000),
(4,4,8,450000),
(5,5,15,750000),
(6,6,6,300000),
(7,7,25,1200000),
(8,8,18,850000),
(9,9,30,2000000),
(10,10,5,150000);
INSERT INTO Structure_Institution
VALUES
(1,'Govt School A','School',500),
(2,'Govt School B','School',450),
(3,'District Hospital','Hospital',300),
(4,'College A','College',1000),
(5,'University A','University',5000),
(6,'Police Station','Government',100),
(7,'Union Office','Government',50),
(8,'Basic Health Unit','Healthcare',150),
(9,'Technical Institute','Institute',800),
(10,'Community Center','Public',400);
INSERT INTO Household_Category(category_name)
VALUES
('Regular'),
('Institutional'),
('Collective'),
('Temporary'),
('Permanent'),
('Urban'),
('Rural'),
('Mixed'),
('Owned'),
('Rented');
INSERT INTO Residential_Status_Type(status_name)
VALUES
('Owned'),
('Rented'),
('Government'),
('Employer Provided'),
('Free Occupancy'),
('Leased'),
('Inherited'),
('Joint Ownership'),
('Temporary'),
('Other');
UPDATE Person
SET monthly_income = 90000
WHERE person_id = 1;
DELETE FROM Person
WHERE person_id = 2;
ALTER TABLE Person
ADD email VARCHAR(100);
ALTER TABLE Person
ADD mother_tongue_id TINYINT,
ADD relationship_type_id TINYINT,
ADD occupation_id SMALLINT,
ADD industry_id SMALLINT;
ALTER TABLE Person
ADD CONSTRAINT fk_person_mother_tongue
FOREIGN KEY (mother_tongue_id)
REFERENCES Mother_Tongue(mother_tongue_id);

ALTER TABLE Person
ADD CONSTRAINT fk_person_relationship
FOREIGN KEY (relationship_type_id)
REFERENCES Relationship_Type(relationship_type_id);

ALTER TABLE Person
ADD CONSTRAINT fk_person_occupation
FOREIGN KEY (occupation_id)
REFERENCES Occupation(occupation_id);

ALTER TABLE Person
ADD CONSTRAINT fk_person_industry
FOREIGN KEY (industry_id)
REFERENCES Industry(industry_id);
ALTER TABLE Person
MODIFY email VARCHAR(150);
ALTER TABLE Household
ADD household_category_id TINYINT,
ADD residential_status_type_id TINYINT;

ALTER TABLE Household
ADD CONSTRAINT fk_household_category
FOREIGN KEY (household_category_id)
REFERENCES Household_Category(household_category_id);

ALTER TABLE Household
ADD CONSTRAINT fk_residential_status
FOREIGN KEY (residential_status_type_id)
REFERENCES Residential_Status_Type(residential_status_type_id);
ALTER TABLE Person
DROP COLUMN email;
RENAME TABLE Religion TO Religion_Master;
RENAME TABLE Religion_Master TO Religion;
TRUNCATE TABLE Household;
DROP TABLE Test_Table;
