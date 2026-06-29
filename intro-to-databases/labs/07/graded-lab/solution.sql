SET SQL_SAFE_UPDATES = 0;

CREATE DATABASE IF NOT EXISTS L1F24BSCS0506;
USE L1F24BSCS0506;

-- Task - 01
CREATE TABLE Instructor (
    instructor_id VARCHAR(15),
    name VARCHAR(50),
    age INT,
    gender CHAR(1),
    office_address VARCHAR(100),
    PRIMARY KEY (instructor_id)
);

-- Task - 02
CREATE TABLE Student (
    student_id VARCHAR(15),
    name VARCHAR(50),
    age INT,
    gender CHAR(1),
    address VARCHAR(100),
    major VARCHAR(30),
    PRIMARY KEY (student_id)
);

-- Task - 03
ALTER TABLE Instructor
ADD COLUMN department VARCHAR(20);

-- Task - 04
ALTER TABLE Student 
MODIFY COLUMN major VARCHAR(50);

-- Task - 05
ALTER TABLE Student 
ADD COLUMN instructor_id VARCHAR(15);

ALTER TABLE Student
ADD CONSTRAINT instructor_fk FOREIGN KEY(instructor_id) REFERENCES Instructor(instructor_id) 
ON DELETE CASCADE ON UPDATE CASCADE;

-- Task - 06
CREATE TABLE Registration_Record (
    reg_id VARCHAR(15),
    reg_date DATE,
    fee DOUBLE,
    student_id VARCHAR(15),
    instructor_id VARCHAR(15),
    PRIMARY KEY (reg_id),
    CONSTRAINT fk_student FOREIGN KEY (student_id)
        REFERENCES Student (student_id)
        ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_instructor FOREIGN KEY (instructor_id)
        REFERENCES Instructor (instructor_id)
        ON DELETE CASCADE ON UPDATE CASCADE
);

-- Task - 07
ALTER TABLE Registration_Record
CHANGE COLUMN fee registration_fee DOUBLE;

-- Task - 08
ALTER TABLE Registration_Record
ADD COLUMN room_no VARCHAR(10);

-- Task - 09
CREATE TABLE Classroom (
    room_id VARCHAR(15),
    room_type VARCHAR(20),
    capacity INT,
    allocation_date DATE,
    PRIMARY KEY (room_id)
);

-- Task - 10
CREATE TABLE Student_Fee (
    fee_id VARCHAR(15),
    fee_date DATE,
    amount VARCHAR(20),
    student_id VARCHAR(15),
    PRIMARY KEY (fee_id)
);

-- Task - 11
ALTER TABLE Student_Fee
ADD CONSTRAINT student_fk FOREIGN KEY(student_id) REFERENCES Student(student_id)
 ON DELETE CASCADE ON UPDATE CASCADE;

-- Task - 12
ALTER TABLE Classroom
RENAME TO Lecture_Room;

-- Task - 13
ALTER TABLE Student_Fee
MODIFY COLUMN amount DOUBLE;

-- Task - 14
ALTER TABLE Instructor
DROP COLUMN office_address;