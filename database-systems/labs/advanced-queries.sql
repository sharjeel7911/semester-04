DROP DATABASE IF EXISTS practice;
CREATE DATABASE practice;
USE prac;

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
);


-- -------------------------------------------------------------------------------------

-- =============================================================================
-- SECTION 1: General Subqueries 
-- =============================================================================

-- 1. Write a query to find names of students who are enrolled in the course "Database Systems" using a subquery.
SELECT name
FROM Student
WHERE student_id IN (
    SELECT student_id
    FROM Enrollments
    WHERE course_id = (
        SELECT course_id
        FROM Courses
        WHERE course_name = 'Database Systems'
    )
);

-- 2. Display the names of students whose marks are greater than the marks of any student in section 'B'.
SELECT name
FROM Student
WHERE marks > ANY (
    SELECT marks
    FROM Student
    WHERE section = 'B'
);

-- 3. Find the student(s) whose marks are greater than all students living in Karachi.
SELECT *
FROM Student
WHERE marks > ALL (
    SELECT marks
    FROM Student
    WHERE city = 'Karachi'
);

-- 4. Write a query to list students who have never enrolled in any course.
SELECT *
FROM Student s
WHERE NOT EXISTS (
    SELECT 1
    FROM Enrollments e
    WHERE e.student_id = s.student_id
);

-- 5. Display all students who have at least one enrollment record (use EXISTS).
SELECT *
FROM Student s
WHERE EXISTS (
    SELECT 1
    FROM Enrollments e
    WHERE e.student_id = s.student_id
);

-- 6. Write a query to show student names along with the maximum marks in the entire class (use a scalar subquery).
SELECT name,
       (SELECT MAX(marks) FROM Student) AS max_marks
FROM Student;

-- 7. Find all courses whose credit hours are greater than the average credit hours of all courses.
SELECT *
FROM Courses
WHERE credit_hours > (
    SELECT AVG(credit_hours)
    FROM Courses
);

-- 8. Write a query to display the course name in which student "Zain" is enrolled.
SELECT course_name
FROM Courses
WHERE course_id IN (
    SELECT course_id
    FROM Enrollments
    WHERE student_id IN (
        SELECT student_id
        FROM Student
        WHERE name = 'Zain'
    )
);

-- 9. List the names of students who have obtained grade A or A+ (use IN inside the subquery).
SELECT name
FROM Student
WHERE student_id IN (
    SELECT student_id
    FROM Enrollments
    WHERE grade IN ('A', 'A+')
);

-- 10. Find the course(s) in which more than 3 students are enrolled (use GROUP BY inside subquery).
SELECT *
FROM Courses
WHERE course_id IN (
    SELECT course_id
    FROM Enrollments
    GROUP BY course_id
    HAVING COUNT(student_id) > 3
);

-- 11. Write a query to find students who scored higher than the average marks of their own section (correlated subquery).
SELECT *
FROM Student s1
WHERE marks > (
    SELECT AVG(marks)
    FROM Student s2
    WHERE s2.section = s1.section
);

-- 12. Find the second highest credit_hours course using a subquery.
SELECT *
FROM Courses
WHERE credit_hours = (
    SELECT MAX(credit_hours)
    FROM Courses
    WHERE credit_hours < (
        SELECT MAX(credit_hours)
        FROM Courses
    )
);

-- 13. Display students whose city matches any city of students enrolled in course ID 104 (use nested subqueries).
SELECT *
FROM Student
WHERE city IN (
    SELECT city
    FROM Student
    WHERE student_id IN (
        SELECT student_id
        FROM Enrollments
        WHERE course_id = 104
    )
);

-- 14. Find the names of students enrolled in the maximum credit hour course.
SELECT name
FROM Student
WHERE student_id IN (
    SELECT student_id
    FROM Enrollments
    WHERE course_id IN (
        SELECT course_id
        FROM Courses
        WHERE credit_hours = (
            SELECT MAX(credit_hours)
            FROM Courses
        )
    )
);

-- 15. Write a query to show each student with the number of courses they are enrolled in, using a subquery in the SELECT clause.
SELECT name,
       (SELECT COUNT(*)
        FROM Enrollments e
        WHERE e.student_id = s.student_id) AS total_courses
FROM Student s;


-- =============================================================================
-- SECTION 2: Advanced & Correlated Subqueries 
-- =============================================================================

-- 1. Find the top-ranking student (highest marks) from each section using a correlated subquery.
SELECT *
FROM Student s1
WHERE marks = (
    SELECT MAX(marks)
    FROM Student s2
    WHERE s2.section = s1.section
);

-- 2. Display students who are enrolled in at least one course that has more than 3 credit hours (use EXISTS with JOIN inside subquery).
SELECT *
FROM Student s
WHERE EXISTS (
    SELECT 1
    FROM Enrollments e
    JOIN Courses c ON e.course_id = c.course_id
    WHERE e.student_id = s.student_id
      AND c.credit_hours > 3
);

-- 3. List the course names taken by students whose marks are above the class average.
SELECT DISTINCT c.course_name
FROM Courses c
WHERE c.course_id IN (
    SELECT e.course_id
    FROM Enrollments e
    WHERE e.student_id IN (
        SELECT s.student_id
        FROM Student s
        WHERE s.marks > (
            SELECT AVG(marks)
            FROM Student
        )
    )
);

-- 4. Find students whose total number of enrollments is less than the average enrollments of all students.
SELECT *
FROM Student s
WHERE (
    SELECT COUNT(*)
    FROM Enrollments e
    WHERE e.student_id = s.student_id
) < (
    SELECT AVG(enrollment_count)
    FROM (
        SELECT COUNT(*) AS enrollment_count
        FROM Enrollments
        GROUP BY student_id
    ) AS temp
);

-- 5. Write a query to show students whose marks are greater than the marks of at least one student in section 'A' but less than one student in section 'C' (use two subqueries).
SELECT *
FROM Student
WHERE marks > (
    SELECT MIN(marks)
    FROM Student
    WHERE section = 'A'
)
AND marks < (
    SELECT MAX(marks)
    FROM Student
    WHERE section = 'C'
);


-- =============================================================================
-- SECTION 3: Multi-Level Nested Subqueries  
-- =============================================================================

-- 1. Find all students enrolled in the course with the third highest credit_hours.
SELECT *
FROM Student
WHERE student_id IN (
    SELECT student_id
    FROM Enrollments
    WHERE course_id IN (
        SELECT course_id
        FROM Courses c1
        WHERE 2 = (
            SELECT COUNT(DISTINCT credit_hours)
            FROM Courses c2
            WHERE c2.credit_hours > c1.credit_hours
        )
    )
);

-- 2. Find the course(s) taken by the student who has the highest marks among students who live in Karachi.
SELECT *
FROM Courses
WHERE course_id IN (
    SELECT course_id
    FROM Enrollments
    WHERE student_id = (
        SELECT student_id
        FROM Student
        WHERE city = 'Karachi'
          AND marks = (
              SELECT MAX(marks)
              FROM Student
              WHERE city = 'Karachi'
          )
    )
);

-- 3. List students whose marks are higher than the highest marks of students enrolled in AI-related courses (AI-related courses = course names containing 'AI' or 'Machine').
SELECT *
FROM Student
WHERE marks > (
    SELECT MAX(s.marks)
    FROM Student s
    JOIN Enrollments e ON s.student_id = e.student_id
    JOIN Courses c ON e.course_id = c.course_id
    WHERE c.course_name LIKE '%AI%' OR c.course_name LIKE '%Machine%'
);

-- 4. Find courses that no student with marks below 60 has enrolled in.
SELECT *
FROM Courses c
WHERE NOT EXISTS (
    SELECT 1
    FROM Enrollments e
    JOIN Student s ON e.student_id = s.student_id
    WHERE e.course_id = c.course_id
      AND s.marks < 60
);

-- 5. Find the student(s) who have the same number of enrollments as the student with the highest marks.
SELECT *
FROM Student s
WHERE (
    SELECT COUNT(*)
    FROM Enrollments e
    WHERE e.student_id = s.student_id
) = (
    SELECT COUNT(*)
    FROM Enrollments e2
    WHERE e2.student_id = (
        SELECT student_id
        FROM Student
        WHERE marks = (SELECT MAX(marks) FROM Student)
        LIMIT 1
    )
);


-- =============================================================================
-- SECTION 4: Complex EXISTS / NOT EXISTS Subqueries  
-- =============================================================================

-- 1. Find students who have enrolled in every course that student_id = 1 has enrolled in (relational division style using NOT EXISTS).
SELECT *
FROM Student s
WHERE s.student_id <> 1
  AND NOT EXISTS (
    SELECT e1.course_id
    FROM Enrollments e1
    WHERE e1.student_id = 1
      AND NOT EXISTS (
        SELECT 1
        FROM Enrollments e2
        WHERE e2.student_id = s.student_id
          AND e2.course_id = e1.course_id
      )
);

-- 2. List all courses such that no A-grade student has ever enrolled in them.
SELECT *
FROM Courses c
WHERE NOT EXISTS (
    SELECT 1
    FROM Enrollments e
    WHERE e.course_id = c.course_id
      AND e.grade IN ('A', 'A+')
);

-- 3. Display students for whom there exists no other student in the same section with higher marks (section topper using NOT EXISTS).
SELECT *
FROM Student s1
WHERE NOT EXISTS (
    SELECT 1
    FROM Student s2
    WHERE s2.section = s1.section
      AND s2.marks > s1.marks
);

-- 4. List students who have enrolled only in courses whose credit_hours are above the average credit_hours, using NOT EXISTS.
SELECT *
FROM Student s
WHERE EXISTS (
    SELECT 1 FROM Enrollments e WHERE e.student_id = s.student_id
) AND NOT EXISTS (
    SELECT 1
    FROM Enrollments e
    JOIN Courses c ON e.course_id = c.course_id
    WHERE e.student_id = s.student_id
      AND c.credit_hours <= (
          SELECT AVG(credit_hours)
          FROM Courses
      )
);

-- 5. Find students for whom every grade they received is higher than the average grade length (length of grade string) of their own section.
SELECT *
FROM Student s
WHERE EXISTS (
    SELECT 1 FROM Enrollments e WHERE e.student_id = s.student_id
) AND NOT EXISTS (
    SELECT 1
    FROM Enrollments e
    WHERE e.student_id = s.student_id
      AND LENGTH(e.grade) <= (
          SELECT AVG(LENGTH(e2.grade))
          FROM Enrollments e2
          JOIN Student s2 ON e2.student_id = s2.student_id
          WHERE s2.section = s.section
      )
);


-- =============================================================================
-- SECTION 5: Subqueries Using ANY  
-- =============================================================================

-- 1. Find students whose marks are greater than ANY marks of students in section 'B'.
SELECT *
FROM Student
WHERE marks > ANY (
    SELECT marks
    FROM Student
    WHERE section = 'B'
);

-- 2. List courses whose credit hours are less than ANY credit hours of AI-related courses.
SELECT *
FROM Courses
WHERE credit_hours < ANY (
    SELECT credit_hours
    FROM Courses
    WHERE course_name LIKE '%AI%' OR course_name LIKE '%Machine%'
);

-- 3. Show students whose marks are greater than ANY marks of students living in Lahore.
SELECT *
FROM Student
WHERE marks > ANY (
    SELECT marks
    FROM Student
    WHERE city = 'Lahore'
);

-- 4. Find students whose marks are less than ANY marks of students in section 'C'.
SELECT *
FROM Student
WHERE marks < ANY (
    SELECT marks
    FROM Student
    WHERE section = 'C'
);

-- 5. Display students whose marks are equal to ANY marks returned by a subquery.
SELECT *
FROM Student
WHERE marks = ANY (
    SELECT marks
    FROM Student
    WHERE section = 'A'
);


-- =============================================================================
-- SECTION 6: Subqueries Using ALL  
-- =============================================================================

-- 1. Find students whose marks are greater than ALL marks of students in section 'A'.
SELECT *
FROM Student
WHERE marks > ALL (
    SELECT marks
    FROM Student
    WHERE section = 'A'
);

-- 2. Show students whose marks are less than ALL marks of students in section 'C'.
SELECT *
FROM Student
WHERE marks < ALL (
    SELECT marks
    FROM Student
    WHERE section = 'C'
);

-- 3. List courses whose credit hours are greater than ALL credit hours of courses taken by student_id = 3.
SELECT *
FROM Courses
WHERE credit_hours > ALL (
    SELECT c.credit_hours
    FROM Courses c
    JOIN Enrollments e ON c.course_id = e.course_id
    WHERE e.student_id = 3
);

-- 4. Find students whose marks are greater than ALL marks of students from Karachi.
SELECT *
FROM Student
WHERE marks > ALL (
    SELECT marks
    FROM Student
    WHERE city = 'Karachi'
);

-- 5. Find courses having credit hours less than ALL credit hours offered in semester 1 (assuming course IDs 101, 102, 103 represent semester 1).
SELECT *
FROM Courses
WHERE credit_hours < ALL (
    SELECT credit_hours
    FROM Courses
    WHERE course_id IN (101, 102, 103)
);


-- =============================================================================
-- SECTION 7: Subqueries in FROM Clause  
-- =============================================================================

-- 1. Select each course with its total enrollment count using a subquery in FROM.
SELECT c.course_name, temp.enroll_count
FROM Courses c
JOIN (
    SELECT course_id, COUNT(*) AS enroll_count
    FROM Enrollments
    GROUP BY course_id
) AS temp ON c.course_id = temp.course_id;

-- 2. Find students whose enrollment count (generated from a subquery table) is greater than 2.
SELECT s.*
FROM Student s
JOIN (
    SELECT student_id, COUNT(*) AS enroll_count
    FROM Enrollments
    GROUP BY student_id
) AS temp ON s.student_id = temp.student_id
WHERE temp.enroll_count > 2;

-- 3. List top 3 students with highest marks using a subquery table.
SELECT temp.student_id, temp.name, temp.marks
FROM (
    SELECT student_id, name, marks
    FROM Student
    ORDER BY marks DESC
    LIMIT 3
) AS temp;

-- 4. Display the average marks per section using a subquery as a derived table.
SELECT temp.section, temp.avg_marks
FROM (
    SELECT section, AVG(marks) AS avg_marks
    FROM Student
    GROUP BY section
) AS temp;

-- 5. Join students with a subquery showing course-wise student counts.
SELECT s.name, e.course_id, counts.total_enrolled
FROM Student s
JOIN Enrollments e ON s.student_id = e.student_id
JOIN (
    SELECT course_id, COUNT(*) AS total_enrolled
    FROM Enrollments
    GROUP BY course_id
) AS counts ON e.course_id = counts.course_id;


-- =============================================================================
-- SECTION 8: Subqueries in DELETE   
-- =============================================================================

-- 1. Delete enrollments of students whose marks are below class average.
DELETE FROM Enrollments
WHERE student_id IN (
    SELECT student_id
    FROM Student
    WHERE marks < (SELECT AVG(marks) FROM Student)
);

-- 2. Delete students who have no enrollments using NOT EXISTS.
DELETE FROM Student
WHERE NOT EXISTS (
    SELECT 1
    FROM Enrollments
    WHERE Enrollments.student_id = Student.student_id
);

-- 3. Delete courses that no student has ever enrolled in.
DELETE FROM Courses
WHERE course_id NOT IN (
    SELECT DISTINCT course_id
    FROM Enrollments
);

-- 4. Delete enrollments of students living in Karachi.
DELETE FROM Enrollments
WHERE student_id IN (
    SELECT student_id
    FROM Student
    WHERE city = 'Karachi'
);

-- 5. Delete students whose marks are less than ALL marks of section 'A'.
DELETE FROM Student
WHERE marks < ALL (
    SELECT marks
    FROM Student
    WHERE section = 'A'
);
