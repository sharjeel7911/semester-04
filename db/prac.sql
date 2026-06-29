drop database prac;
CREATE DATABASE prac;
use prac;
-- 1. Create Tables
CREATE TABLE Student (
    student_id INT PRIMARY KEY,
    name VARCHAR(50),
    section VARCHAR(1),
    marks INT,
    city VARCHAR(50)
);

CREATE TABLE Courses (
    course_id INT PRIMARY KEY,
    course_name VARCHAR(50),
    credit_hours INT
);

CREATE TABLE Enrollments (
    enroll_id INT PRIMARY KEY,
    student_id INT,
    course_id INT,
    grade VARCHAR(2),
    FOREIGN KEY (student_id) REFERENCES Student(student_id),
    FOREIGN KEY (course_id) REFERENCES Courses(course_id)
);

-- 2. Insert Data into Student Table
INSERT INTO Student VALUES 
(1, 'Ali', 'A', 88, 'Lahore'), (2, 'Sana', 'B', 76, 'Karachi'),
(3, 'Ahmed', 'A', 92, 'Islamabad'), (4, 'Zain', 'C', 54, 'Lahore'),
(5, 'Mariam', 'B', 67, 'Karachi'), (6, 'Usman', 'A', 45, 'Multan'),
(7, 'Hira', 'C', 81, 'Lahore'), (8, 'Bilal', 'B', 59, 'Islamabad'),
(9, 'Ayesha', 'C', 73, 'Karachi'), (10, 'Farrukh', 'A', 98, 'Lahore'),
(11, 'Nimra', 'B', 63, 'Islamabad'), (12, 'Arsalan', 'C', 87, 'Multan'),
(13, 'Saad', 'A', 72, 'Lahore'), (14, 'Rabia', 'B', 50, 'Karachi'),
(15, 'Hamza', 'C', 69, 'Islamabad');

-- 3. Insert Data into Courses Table
INSERT INTO Courses VALUES 
(101, 'Programming', 3), 
(102, 'Database Systems', 4), 
(103, 'Data Structures', 3),
(104, 'Operating Systems', 4),
(105, 'AI Fundamentals', 3),
(106, 'Computer Networks', 3),
(107, 'Software Engg', 4),
(108, 'Machine Learning', 3),
(109, 'Web Engineering', 3),
(110, 'Cyber Security', 4);

-- 4. Insert Data into ENROLLMENTS Table
INSERT INTO Enrollments VALUES 
(1, 1, 102, 'A'), (2, 1, 103, 'B+'), (3, 2, 101, 'A-'),
(4, 2, 103, 'B'), (5, 3, 102, 'A+'), (6, 3, 104, 'A'),
(7, 4, 101, 'C'), (8, 4, 107, 'B'), (9, 5, 103, 'C+'),
(10, 6, 101, 'D'), (11, 7, 104, 'B+'), (12, 7, 110, 'A'),
(13, 8, 102, 'B'), (14, 9, 106, 'B-'), (15, 9, 107, 'A-'),
(16, 10, 108, 'A+'), (17, 11, 105, 'B'), (18, 12, 109, 'A'),
(19, 13, 104, 'B+'), (20, 14, 101, 'C'), (21, 15, 110, 'B+');

-- 1
select * from students where id in 
(select id from enrollment where couid =
(select couid from course where couname = 'Database'));

-- 2
select name from student where marks > any
(select marks from student where section = 'B');

-- 3
select name from student where marks > all
(select marks from student where city = 'Karachi');

-- 4
select * from student where id not in
(select id from enrollment);
select * from student where not exists
(select 1 from enrollments where s.id = e.id);	

-- 5
select * from student where exists
(select 1 from enrollments where s.id = e.id);	

-- 6
select name, (select max(marks) from Student) from Student;

-- 7
select couname from course where crhour >
(select avg(crhour) from course);

-- 8
select couname from course where couid in
(select couid from enrollment where sid in
(select sid from student where name = 'zain'));

-- 9
select name from student where id in
(select id from enrollment where grade in('a','a+'));

-- 10
SELECT name from course where id in 
(select id from enrollment GROUP BY id
having count(sid) > 3);

-- 11
SELECT * from stuent s1 where marks >
(select avg(marks) from student s2 where  s.section = s2.section);

-- 12
SELECT marks from student where marks =
(select max(marks) from student where marks < 
(select max(marks) from student));
SELECT * FROM Courses WHERE credit_hours = 
(SELECT MAX(credit_hours) FROM Courses WHERE credit_hours < 
(SELECT MAX(credit_hours) FROM Courses));

-- 13
select * from student WHERE city in
(select city from student where sid in
(SELECT sid from enrollment where couid = 104));

-- 14
select * from stuent where sid in
(select sid from enrollment where cid in 
(select cid from course where crhour = 
(select max(crhour) from course)));

-- 15
select name , (SELECT count(*) from enrollment where s1.id = e.id) from student s1;
SELECT s.name, COUNT(e.enroll_id) AS total_courses
FROM Student s
LEFT JOIN ENROLLMENTS e ON s.student_id = e.student_id
GROUP BY s.student_id, s.name;

-- advanced & corellated

-- 1
select * from student s1 where marks =
(select max(marks) from student s2 where s1.sec = s2.sec);

-- 2	
select * from Student s where exists
(select 1 FROM Enrollments e join Courses c ON e.course_id = c.course_id
where e.student_id = s.student_id and c.credit_hours > 3
);

-- 3
select distinct cname from course where cid in
(select cid from enrollment where sid in
(select marks from student where marks >
(select avg(marks) from student )));

-- 4
select * from student where 
(select count(*) from enrollent where e.student_id = s.student_id) >
(select avg(encount) from (select count(*) as encount from enrollment group by sid));

-- 5 
SELECT * from student where marks > any
(select min(marks) from student where sec = 'a') and
marks < any(select max(marks) from student where sec = 'c');

-- Multi-Level Nested Subqueries

-- 1 1. Find all students enrolled in the course with the third highest credit_hours.
select * from student where id IN
(select id from enroll where cid in 
(select id from course where crhour =
(SELECT MAX(credit_hours) FROM Courses WHERE credit_hours < 
(SELECT MAX(credit_hours) FROM Courses WHERE credit_hours < 
(SELECT MAX(credit_hours) FROM Courses)))));

-- 2
select cname from course where cid in
(select cid from enroll where sid = 
(SELECT sid from student where city = 'karachi' and  marks = 
(select max(marks) from student where city = 'karachi')));

-- 3
select * from student where marks > 
(select max(marks) from student where sid in
(select sid from enroll where cid = 
(select cid from course where name like '%ai%' or name like '%machine%')));

-- 4
select name from course where cid not in
(select cid from enroll where sid in
(select sid from student where marks < 60));

select name from course where not exists 
(SELECT 1 from enroll where e.course_id = c.course_id and exists
(select 1 from student where s.sid = e.sid and marks < 60));

-- 5
select * from student where sid in 
(SELECT sid FROM enroll GROUP BY sid HAVING COUNT(*) = 
(select count(*) from enroll where sid =
(select sid from student where marks = 
(select max(marks) from sudent))));

-- Section 4: Complex EXISTS / NOT EXISTS Subqueries (Page 4)

-- 1
select * from student where sid != 1 and sid IN
(select sid from enroll WHERE cid IN 
(SELECT course_id FROM enroll WHERE student_id = 1)
 group by sid having COUNT(DISTINCT course_id) = 
 (SELECT COUNT(*) FROM enroll WHERE student_id = 1)
);
  









