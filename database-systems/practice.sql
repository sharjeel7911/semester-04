SET SQL_SAFE_UPDATES = 0;


-- SHOW DATABASES;

-- CREATE DATABASE x;
-- -- DROP DATABASE x;
-- USE x;

-- SELECT DATABASE();

-- CREATE TABLE Cats (
--     name VARCHAR(30),
--     age INT
-- );

-- SHOW TABLES;

-- SHOW COLUMNS FROM Cats;

-- DESC Cats;
-- -- DROP TABLE Cats;
-- -- this is a comment


-- -- 04-inserting data sec

-- INSERT INTO Cats(name, age) VALUES
-- ('Eli', 7),
-- ('Beth', 10);

-- INSERT INTO Cats(name) VALUES("Todd");

-- SELECT * FROM Cats; 

-- CREATE TABLE cat (
--     name VARCHAR(30) NOT NULL,
--     age INT NOT NULL
-- );

-- INSERT INTO cat(name, age) VALUES
-- ();

-- SELECT * FROM cat;


-- CREATE TABLE cat2 (
--     name VARCHAR(30) NOT NULL DEFAULT 'Unnamed',
--     age INT NOT NULL
-- );

-- -- pk is never null so no need to write NOT NULL
-- CREATE TABLE dog (
-- 	id INT AUTO_INCREMENT,
--     name VARCHAR(30) NOT NULL DEFAULT 'Unnamed',
--     age INT NOT NULL,
--     PRIMARY KEY(id)
-- );


-- -- sec-05 crud intro

-- CREATE TABLE cats (
--     cat_id INT AUTO_INCREMENT,
--     name VARCHAR(100),
--     breed VARCHAR(100),
--     age INT,
--     PRIMARY KEY (cat_id)
-- );

-- INSERT INTO cats(name, breed, age) VALUES 
-- ('Ringo', 'Tabby', 4),
-- ('Cindy', 'Maine Coon', 10),
-- ('Dumbledore', 'Maine Coon', 11),
-- ('Egg', 'Persian', 4),
-- ('Misty', 'Tabby', 13),
-- ('George Michael', 'Ragdoll', 9),
-- ('Jackson', 'Sphynx', 7);
-- 	

-- SELECT * FROM cats WHERE age = 4;

-- SELECT cat_id FROM cats;

-- SELECT cat_id, age FROM cats WHERE cat_id = age;

-- SELECT cat_id AS id FROM cats;

-- SELECT * FROM cats WHERE name = 'misty';

-- UPDATE cats 
-- SET 
--     age = 14
-- WHERE
--     name = 'Misty';

-- SELECT * FROM cats;

-- UPDATE cats SET age = 12 WHERE breed = 'Maine Coon';

-- -- delete from cats; del every row
-- DELETE FROM cats WHERE name = 'Egg';


-- -- 06- crud challenge

-- CREATE DATABASE Shirts_db;

-- USE Shirts_db; 

-- CREATE TABLE IF NOT EXISTS shirts (
-- 	shirt_id INT AUTO_INCREMENT,
--     article VARCHAR(50) NOT NULL, 
--     color VARCHAR(20) NOT NULL,
--     shirt_size VARCHAR(5) NOT NULL,
--     last_worn INT NOT NULL,
--     PRIMARY KEY(shirt_id)
-- );

-- INSERT INTO shirts (article, color, shirt_size, last_worn) VALUES
-- ('t-shirt', 'white', 'S', 10),
-- ('t-shirt', 'green', 'S', 200),
-- ('polo shirt', 'black', 'M', 10),
-- ('tank top', 'blue', 'S', 50),
-- ('t-shirt', 'pink', 'S', 0),
-- ('polo shirt', 'red', 'M', 5),
-- ('tank top', 'white', 'S', 200),
-- ('tank top', 'blue', 'M', 15);

-- SELECT * FROM shirts;

-- INSERT INTO shirts (article, color, shirt_size, last_worn) VALUES
-- ('polo shirt', 'purple', 'XXL', 50);

-- SELECT  article, color FROM shirts;

-- SELECT article, color, shirt_size, last_worn FROM shirts WHERE shirt_size = 'M';

-- UPDATE shirts SET shirt_size = 'L' WHERE article = 'polo shirt';

-- UPDATE shirts SET last_worn = 0 WHERE last_worn = 15;

-- UPDATE shirts SET shirt_size = 'XS', color = 'off white' WHERE color = 'white';

-- DELETE FROM shirts WHERE last_worn = 200;

-- DELETE FROM shirts WHERE article = 'tank top';

-- DELETE FROM shirts;

-- DROP DATABASE Shirts_db;


-- 07-string funcs

-- CREATE DATABASE Books_shop;
-- USE Books_shop;

-- CREATE TABLE books 
-- 	(
-- 		book_id INT NOT NULL AUTO_INCREMENT,
-- 		title VARCHAR(100),
-- 		author_fname VARCHAR(100),
-- 		author_lname VARCHAR(100),
-- 		released_year INT,
-- 		stock_quantity INT,
-- 		pages INT,
-- 		PRIMARY KEY(book_id)
-- 	);
--     
--    

-- INSERT INTO books (title, author_fname, author_lname, released_year, stock_quantity, pages)
-- VALUES
-- ('The Namesake', 'Jhumpa', 'Lahiri', 2003, 32, 291),
-- ('Norse Mythology', 'Neil', 'Gaiman',2016, 43, 304),
-- ('American Gods', 'Neil', 'Gaiman', 2001, 12, 465),
-- ('Interpreter of Maladies', 'Jhumpa', 'Lahiri', 1996, 97, 198),
-- ('A Hologram for the King: A Novel', 'Dave', 'Eggers', 2012, 154, 352),
-- ('The Circle', 'Dave', 'Eggers', 2013, 26, 504),
-- ('The Amazing Adventures of Kavalier & Clay', 'Michael', 'Chabon', 2000, 68, 634),
-- ('Just Kids', 'Patti', 'Smith', 2010, 55, 304),
-- ('A Heartbreaking Work of Staggering Genius', 'Dave', 'Eggers', 2001, 104, 437),
-- ('Coraline', 'Neil', 'Gaiman', 2003, 100, 208),
-- ('What We Talk About When We Talk About Love: Stories', 'Raymond', 'Carver', 1981, 23, 176),
-- ("Where I'm Calling From: Selected Stories", 'Raymond', 'Carver', 1989, 12, 526),
-- ('White Noise', 'Don', 'DeLillo', 1985, 49, 320),
-- ('Cannery Row', 'John', 'Steinbeck', 1945, 95, 181),
-- ('Oblivion: Stories', 'David', 'Foster Wallace', 2004, 172, 329),
-- ('Consider the Lobster', 'David', 'Foster Wallace', 2005, 92, 343);

-- SELECT 
--     CONCAT(author_fname, ' ', author_lname)
-- FROM
--     books;

-- SELECT 
--     CONCAT_WS(' ', author_fname, author_lname)
-- FROM
--     books;
--     
--     
--     
--     
--     -- substr == substring
-- -- goes just 5th char    
-- SELECT 
--     SUBSTRING(author_fname, 1, 5)
-- FROM
--     books; 
--     
--     
-- -- goes upto end    
-- SELECT 
--     SUBSTRING(author_fname, 1)
-- FROM
--     books; 
--     
-- -- last char   if  SUBSTRING(author_fname, -1, 2) -> it will print last 2 char
-- SELECT 
--     SUBSTRING(author_fname, - 1)
-- FROM
--     books;     
--     
--     
--     
-- SELECT 
--     CONCAT(SUBSTR(book_name, 1, 10), '...') AS title
-- FROM
--     books;    
--     
--     
--     
-- SELECT 
--     CONCAT(SUBSTR(author_fname, 1, 1),
--             '. ',
--             SUBSTR(author_lname, 1, 1),
--             '.') AS title
-- FROM
--     books;    
--     

-- SELECT REVERSE('HELLO WORLD');    

-- SELECT CHAR_LENGTH('HELLO WORLD'); -- diff from    SELECT LENGTH('HELLO WORLD'); [show byte len]

-- SELECT UPPER('HELLO WORLD');

-- SELECT LOWER('HELLO WORLD');


-- SELECT REPLACE('HELLO WORLD', 'HELLO', 'HEY');    


-- SELECT INSERT('Hello WORLd', 8, 3, 'orl');  -- 8(index), 3 (replace 3 char in the string)



-- SELECT LEFT('Hello World', 5);
-- SELECT RIGHT('Hello World', 5);

-- SELECT REPEAT('Hello World', 5);

-- SELECT TRIM(' hello world             ');
-- SELECT TRIM(LEADING '.' FROM ' ..hello world         ....    ');
-- SELECT TRIM(TRAILING '.' FROM ' ..hello world         ....    ');
-- SELECT TRIM(BOTH '.' FROM ' ..hello world         ....    ');

-- SELECT 
--     CONCAT(SUBSTR(title, 1, 10), '...') AS short_title,
--     CONCAT(author_lname, ',', author_fname) AS author,
--     CONCAT(stock_quantity, ' in stock')
-- FROM
--     books;


-- -------------------------------------------------------------------------------------------




--  08-refining selections


INSERT INTO books (title, author_fname, author_lname, released_year, stock_quantity, pages) VALUES 
('10% Happier', 'Dan', 'Harris', 2014, 29, 256),
('fake_book', 'Freida', 'Harris', 2001, 287, 428),
('Lincoln In The Bardo', 'George', 'Saunders', 2017, 1000, 367);


-- DISTINCT

SELECT DISTINCT
    author_lname
FROM
    books;

SELECT DISTINCT
    CONCAT(author_lname, ', ', author_fname)
FROM
    books;

-- same as above
SELECT DISTINCT
    author_lname, author_fname
FROM
    books;


-- order by

SELECT 
    author_lname, author_fname
FROM
    books
ORDER BY author_lname;   -- or ORDER BY author_lname DESC; for descending

SELECT 
    author_lname, author_fname
FROM
    books
ORDER BY 2;  -- will select 2nd val which is author_fname

SELECT 
    author_lname, author_fname
FROM
    books -- ORDER BY title, released_year DESC;  DESC will only impact released_year not title
ORDER BY title, released_year; -- first will sort by title then released_year


-- LIMIT

SELECT 
    author_lname, author_fname, title, released_year
FROM
    books 
ORDER BY title, released_year LIMIT 5; 


SELECT 
    author_lname, author_fname, title, released_year
FROM
    books 
ORDER BY title, released_year LIMIT 5, 7; -- start from row 5th and show 7 rows not 7th row 




-- LIKE 

SELECT 
    author_lname, author_fname, title, released_year
FROM
    books
WHERE
    title LIKE '%:%'; -- will find on both sides -> have : and some char on both sides
    
SELECT 
    author_fname
FROM
    books
WHERE
    author_fname LIKE '%n'; -- will only find fname which ends with 'n' wont look beyond that [ '%\%%' will find % or \_]

SELECT 
    author_lname, author_fname, released_year
FROM
    books
WHERE
    author_fname LIKE '____'; -- author first name will be 4 char long











-- 09 - Aggregate Functions 


SELECT 
    COUNT(*)
FROM
    books;

SELECT 
    COUNT(DISTINCT(author_fname))
FROM
    books;
    
    
    
    
-- GROUP BY

SELECT 
     released_year, COUNT(*) -- released_year, title (two values wont work)
FROM
    books
GROUP BY released_year; -- will give how many books released in one year 
    




-- min and max


SELECT 
    MIN(released_year)
FROM
    books;
    
    
    
SELECT 
    *
FROM
    books
WHERE
    pages = (SELECT 
            MAX(pages)
        FROM
            books);



SELECT 
    CONCAT(author_fname, ' ', author_lname) AS author
FROM
    books
GROUP BY author;

SELECT 
    author_fname, author_lname, COUNT(*)
FROM
    books
GROUP BY author_fname , author_lname;	


-- year when each author pub. their first book
SELECT 
    CONCAT(author_fname, ' ', author_lname) AS author,
    MIN(released_year)
FROM
    books
GROUP BY author;


-- SUM

SELECT 
    SUM(pages)
FROM
    books;
    
SELECT 
    author_lname, SUM(pages)
FROM
    books
GROUP BY author_lname;


-- average

SELECT 
    AVG(releaased_year)
FROM
    books;


SELECT 
    released_year, COUNT(*), AVG(released_year)
FROM
    books
GROUP BY released_year
ORDER BY released_year;




-- 10 - Revisiting Data Types









-- DATE, TIME, DATETIME
-- CURRDATE(), CURRTIME() , NOW()

-- datetime (1000, 9999)  timestamp(1970, 2038)

CREATE TABLE people (
    name varchar(10),
    bdate DATE,
    btime TIME,
    bdttime DATETIME
);

INSERT INTO people(name, bdate, btime, bdttime) VALUES
('sharjeel', current_date(), current_time(), current_timestamp());

SELECT 
    *
FROM
    people;


SELECT 
    bdate,
    DAY(bdate),
    DAYOFWEEK(bdate),
    DAYOFMONTH(bdate),
    DAYOFYEAR(bdate),
    MONTHNAME(bdate),
    WEEK(bdate),
    HOUR(btime),
    MINUTE(btime),
    SECOND(btime)
FROM
    people;

SELECT 
    DATEDIFF(CURDATE(), bdate)
FROM
    people;


CREATE TABLE post (
    text VARCHAR(1000),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE post2 (
    text VARCHAR(1000),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP ON UPDATE CURRENT_TIMESTAMP 
);



-- 11 - Comparison & Logical Operators





-- != , NOT LIKE , BETWEEN(NOT) , [IN -> select * from table where author_lname IN('Lihari', 'name', ....);] NOT IN

SELECT CAST('09:00:00' AS TIME); -- string to time


SELECT 
    title,
    released_year,
    CASE
        WHEN released_year >= 2000 THEN 'MODERN LIT'
        ELSE '20TH CENTURY'
    END AS GENRE
FROM
    books;
    
    
    
    
 SELECT 
    *
FROM
    books
WHERE
    author_lname IS NULL;   





SELECT 
    title, author_lname
FROM
    books
WHERE
    SUBSTR(author_lname, 1, 1) IN ('C' , 'S');

-- same as above
SELECT 
    title, author_lname
FROM
    books
WHERE
    author_lname LIKE 'C%'
        OR author_lname LIKE 'S%';
        
        
        
        
        
        
        
        -- 12 - Constraints  & ALTER TABLE
        
        
        
        
        
CREATE TABLE companies (
    supplier_id INT AUTO_INCREMENT,
    name VARCHAR(255) NOT NULL,
    phone VARCHAR(15) NOT NULL UNIQUE, -- see unique
    address VARCHAR(255) NOT NULL,
    PRIMARY KEY (supplier_id)
);        



-- check
CREATE TABLE partiers (
    name VARCHAR(50),
    age INT CHECK (age > 18)
);
        
-- consntraint key word
CREATE TABLE partiers2 (
    name VARCHAR(50),
    age INT,
    CONSTRAINT age_under_18 CHECK (age > 18)
);        

        
 
insert into partiers2(name, age) values
('sharjeel', 13);
        
        
        
CREATE TABLE companies (
    supplier_id INT AUTO_INCREMENT,
    name VARCHAR(255) NOT NULL,
    phone VARCHAR(15) NOT NULL UNIQUE,
    address VARCHAR(255) NOT NULL,
    PRIMARY KEY (supplier_id),
    CONSTRAINT name_address UNIQUE (name , address) -- see here name adrees combo must be unique
);        
        
        
        
-- ALTER TABLE

ALTER TABLE companies
ADD COLUMN city VARCHAR(25);        
        
        
RENAME TABLE companies TO suppliers;        
        
ALTER TABLE suppliers
RENAME TO companies;        

        
        
ALTER TABLE suppliers
RENAME COLUMN name TO biz_name;      
  
-- Use MODIFY to change an existing column's type       
ALTER TABLE suppliers
MODIFY biz_name VARCHAR(100);       
       
       
       
       
       
       
-- Use CHANGE to rename a column AND change its data type.
-- This example renames the 'business' column to 'biz_names' AND make its VARCHAR(50)
ALTER TABLE suppliers
CHANGE business biz_names VARCHAR(50);


        
        
CREATE TABLE horses (
supplier_id INT AUTO_INCREMENT,
name VARCHAR(255) NOT NULL,
phone VARCHAR(15) NOT NULL UNIQUE,
address VARCHAR(255) NOT NULL,
PRIMARY KEY (supplier_id),
CONSTRAINT name_address UNIQUE (name , address)
);       


ALTER TABLE horses 
ADD CONSTRAINT whatever CHECK (phone IS NOT NULL);
        
ALTER TABLE horses 
DROP CONSTRAINT whatever;
        
        
        
        
        
        
        
     -- 13 - One to Many & Joins
     
     
     
-- inner , left , right JOINS	
        
        
CREATE TABLE customers (
    customer_id INT,
    fname VARCHAR(15),
    lname VARCHAR(15),
    email VARCHAR(15),
    PRIMARY KEY (customer_id)
);
        
CREATE TABLE orders (
    order_id INT,
    order_date DATE,
    customer_id INT,
    amount DECIMAL(8 , 2 ),
    PRIMARY KEY (order_id),
    CONSTRAINT fk_customer FOREIGN KEY (customer_id)
        REFERENCES customer (customer_id) on DELETE cascade
);



SELECT 
    *
FROM
    customers
        INNER JOIN
    orders ON orders.customer_id = customer.customer_id;
        
        
 SELECT 
    fname, lname, SUM(amount) AS total
FROM
    customers
        INNER JOIN
    orders ON orders.customer_id = customer.customer_id
GROUP BY fname , lname
ORDER BY total;
                
        
-- LEFT JOIN     
        
SELECT 
    fname, lname, amount, order_date
FROM
    customers
        LEFT JOIN
    orders ON orders.customer_id = customer.customer_id; -- it tells customers who never placed an order only shows customers
        
        
       
SELECT 
    fname, lname, amount, IFNULL((amount), 0) AS money_spent
FROM
    customers
        LEFT JOIN
    orders ON orders.customer_id = customer.customer_id
GROUP BY fname , lname;       
        
        
 
        
-- RIGHT JOIN     
        
        
   SELECT 
    fname, lname, amount, order_date
FROM
    customers
        RIGHT JOIN 
    orders ON orders.customer_id = customer.customer_id;         
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        

