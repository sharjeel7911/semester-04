
-- Sharjeel [L1F24BSCS0506]

SET SQL_SAFE_UPDATES = 0;
CREATE DATABASE IF NOT EXISTS Lab_06;
Use Lab_06;
SELECT DATABASE();

--   Q - 01

CREATE TABLE IF NOT EXISTS Patients (
    patient_id VARCHAR(15) NOT NULL,
    patient_name VARCHAR(15) NOT NULL,
    patient_age INT NOT NULL,
    patient_gender VARCHAR(1),
    patient_address VARCHAR(20) NOT NULL,
    patient_disease VARCHAR(10) NOT NULL,
    doctor_id VARCHAR(15),
    PRIMARY KEY (patient_id)
);

--   Q - 02

ALter TABLE Patients
Modify COLUMN patient_gender CHAR(1);

--   Q - 03

CREATE TABLE IF NOT EXISTS Doctors (
    doctor_id VARCHAR(15) NOT NULL,
    doctor_name VARCHAR(15) NOT NULL,
    doctor_age INT NOT NULL,
    doctor_gender CHAR(1),
    doctor_address VARCHAR(20) NOT NULL,
    PRIMARY KEY (doctor_id)
);
 
--   Q - 04

ALTER TABLE Doctors
ADD COLUMN doctor_ward VARCHAR(15);

--   Q - 05

ALTER TABLE Patients
ADD CONSTRAINT fk_doctor FOREIGN KEY(doctor_id) REFERENCES Doctors(doctor_id) 
ON DELETE CASCADE ON UPDATE CASCADE;

--   Q - 06

CREATE TABLE IF NOT EXISTS Labs (
    lab_id VARCHAR(15) NOT NULL,
    test_date DATE NOT NULL,
    amount VARCHAR(20) NOT NULL,
    patient_id VARCHAR(15) NOT NULL,
    doctor_id VARCHAR(15) NOT NULL,
    PRIMARY KEY (lab_id),
    CONSTRAINT fk_lab_patient FOREIGN KEY (patient_id)
        REFERENCES Patients (patient_id)
        ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_lab_doctor FOREIGN KEY (doctor_id)
        REFERENCES Doctors (doctor_id)
        ON DELETE CASCADE ON UPDATE CASCADE
);

--   Q - 07

ALTER TABLE Labs
RENAME COLUMN amount TO test_amount;

--   Q - 08

ALTER TABLE Labs
MODIFY COLUMN test_amount DOUBLE;

--   Q - 09

ALTER TABLE Labs
ADD COLUMN lab_no VARCHAR(10) NOT NULL;

--   Q - 10

CREATE TABLE IF NOT EXISTS HospitalRoom (
    room_id VARCHAR(15) NOT NULL,
    room_allocation_date DATE NOT NULL,
    room_type VARCHAR(20),
    room_status VARCHAR(5) NOT NULL,
    PRIMARY KEY (room_id)
);

--   Q - 11

CREATE TABLE IF NOT EXISTS PatientBill (
    bill_id VARCHAR(15) NOT NULL,
    bill_date DATE NOT NULL,
    bill_amount VARCHAR(20) NOT NULL, -- should be decimal like DECIMAL (10, 2)
    patient_id VARCHAR(15) NOT NULL,
    PRIMARY KEY (bill_id)
); 

--   Q - 12

ALTER TABLE PatientBill
ADD CONSTRAINT fk_patient FOREIGN KEY (patient_id)
        REFERENCES Patients (patient_id)
		ON DELETE CASCADE ON UPDATE CASCADE;

--   Q - 13

ALTER TABLE HospitalRoom
RENAME TO Room;

DROP DATABASE Lab_06;