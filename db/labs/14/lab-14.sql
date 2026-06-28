SET SQL_SAFE_UPDATES = 0;

-- ------------------------------------------------
-- Task 1
-- ------------------------------------------------

CREATE DATABASE WeddingDress_0506;
USE WeddingDress_0506;

-- ------------------------------------------------
-- Task 2	
-- ------------------------------------------------

CREATE TABLE Customer_0506 (
    customer_id INT PRIMARY KEY,
    c_name VARCHAR(10) NOT NULL,
    c_age INT NOT NULL,
    c_addrs VARCHAR(20) NOT NULL,
    c_contact_number VARCHAR(25)
);

-- ------------------------------------------------
-- Task 3
-- ------------------------------------------------

INSERT INTO Customer_0506 (customer_id, c_name, c_age, c_addrs, c_contact_number) VALUES
(1, 'Ayesha', 24, 'Johar Town', '0300-1234567'),
(4, 'Ahmad', 29, 'Wapda Town', '0333-1234567'),
(6, 'Rameen', 27, 'DHA', NULL),
(2, 'Amina', 20, 'Model Town', '0321-1234567'),
(3, 'Kashif', 18, 'Gulberg', '0313-1234567');
 
-- ------------------------------------------------
-- Task 4
-- ------------------------------------------------

CREATE TABLE Designer_0506 (
    designer_id INT PRIMARY KEY,
    d_name VARCHAR(15) NOT NULL,
    d_category VARCHAR(20) NOT NULL,
    d_contact_number VARCHAR(25)
);
 
-- ------------------------------------------------
-- Task 5
-- ------------------------------------------------

INSERT INTO Designer_0506 (designer_id, d_name, d_category, d_contact_number) VALUES
(100, 'MariaB', 'Unstitched Ladies', '0300-7654321'),
(101, 'Charcoal', 'Men Dressing', '0333-7654321'),
(102, 'Sana Safinaz', 'Unstitched Ladies', '0321-7654321'),
(103, 'Khaadi', 'Unstitched Ladies', '0345-7654321'),
(104, 'Oxford', 'Warm Cloths', '0310-7654321');

-- ------------------------------------------------
-- Task 6
-- ------------------------------------------------

CREATE TABLE CustomerDesigner_0506 (
    cd_id INT AUTO_INCREMENT PRIMARY KEY,
    customer_id INT NOT NULL,
    designer_id INT NOT NULL,
    dress_type VARCHAR(20) NOT NULL,
    priority VARCHAR(25) DEFAULT 'Normal',
    FOREIGN KEY (customer_id) REFERENCES Customer_0506(customer_id),
    FOREIGN KEY (designer_id) REFERENCES Designer_0506(designer_id)
);
 
-- ------------------------------------------------
-- Task 7
-- ------------------------------------------------

INSERT INTO CustomerDesigner_0506 (customer_id, designer_id, dress_type, priority) VALUES
(1, 103, 'Sari', 'Normal'),
(1, 102, 'Fancy Suit', 'Normal'),
(1, 103, 'Fancy Suit', 'Urgent'),
(4, 101, 'Waistcoat', 'Urgent'),
(4, 104, 'Sweater', 'Urgent'),
(6, 100, 'Fancy Suit', 'Normal'),
(2, 100, 'Winter Suit', 'Normal'),
(6, 100, 'Winter Suit', 'Urgent'),
(3, 104, 'Kurta', 'Normal'),
(3, 104, 'Sweater', 'Normal');
 
-- ------------------------------------------------
-- Task 8
-- ------------------------------------------------

SELECT COUNT(*) AS total_orders 
FROM CustomerDesigner_0506;

-- ------------------------------------------------
-- Task 9
-- ------------------------------------------------

SELECT customer_id, COUNT(*) AS total_orders 
FROM CustomerDesigner_0506 
GROUP BY customer_id;

-- ------------------------------------------------
-- Task 10
-- ------------------------------------------------

SELECT designer_id, COUNT(*) AS orders_taken 
FROM CustomerDesigner_0506 
GROUP BY designer_id;

-- ------------------------------------------------
-- Task 11
-- ------------------------------------------------

SELECT COUNT(*) AS normal_priority_orders 
FROM CustomerDesigner_0506 
WHERE priority = 'Normal';

-- ------------------------------------------------
-- Task 12
-- ------------------------------------------------

SELECT c.c_name 
FROM Customer_0506 c
JOIN CustomerDesigner_0506 cd ON c.customer_id = cd.customer_id
GROUP BY c.customer_id, c.c_name
HAVING COUNT(cd.cd_id) > 1;

-- ------------------------------------------------
-- Task 13
-- ------------------------------------------------

SELECT d.d_name 
FROM Designer_0506 d
JOIN CustomerDesigner_0506 cd ON d.designer_id = cd.designer_id
GROUP BY d.designer_id, d.d_name
HAVING COUNT(cd.cd_id) = (
    SELECT MAX(order_count) 
    FROM (SELECT COUNT(*) AS order_count FROM CustomerDesigner_0506 GROUP BY designer_id) AS counts
);

-- ------------------------------------------------
-- Task 14
-- ------------------------------------------------

SELECT c.c_name 
FROM Customer_0506 c
JOIN CustomerDesigner_0506 cd ON c.customer_id = cd.customer_id
GROUP BY c.customer_id, c.c_name
HAVING COUNT(cd.cd_id) = (
    SELECT MIN(order_count) 
    FROM (SELECT COUNT(*) AS order_count FROM CustomerDesigner_0506 GROUP BY customer_id) AS counts
);

-- ------------------------------------------------
-- Task 15
-- ------------------------------------------------

SELECT d_name 
FROM Designer_0506 
ORDER BY d_name ASC 
LIMIT 1;

-- ------------------------------------------------
-- Task 16
-- ------------------------------------------------

SELECT c.c_name, d.d_name 
FROM CustomerDesigner_0506 cd
JOIN Customer_0506 c ON cd.customer_id = c.customer_id
JOIN Designer_0506 d ON cd.designer_id = d.designer_id
ORDER BY cd.cd_id ASC 
LIMIT 1;

-- ------------------------------------------------
-- Task 17
-- ------------------------------------------------

SELECT c.c_name, cd.dress_type 
FROM Customer_0506 c
JOIN CustomerDesigner_0506 cd ON c.customer_id = cd.customer_id;

-- ------------------------------------------------
-- Task 18
-- ------------------------------------------------

SELECT c.c_name AS customer_name, d.d_name AS designer_name, cd.priority 
FROM CustomerDesigner_0506 cd
JOIN Customer_0506 c ON cd.customer_id = c.customer_id
JOIN Designer_0506 d ON cd.designer_id = d.designer_id;

-- ------------------------------------------------
-- Task 19
-- ------------------------------------------------

ALTER TABLE Designer_0506 
MODIFY COLUMN d_category VARCHAR(35) NOT NULL;

-- ------------------------------------------------
-- Task 20
-- ------------------------------------------------

UPDATE Designer_0506 
SET d_category = 'Unstitched Ladies Suit' 
WHERE d_category = 'Unstitched Ladies';

-- ------------------------------------------------
-- Task 21
-- ------------------------------------------------

SELECT c.c_name, cd.dress_type, cd.priority 
FROM CustomerDesigner_0506 cd
JOIN Customer_0506 c ON cd.customer_id = c.customer_id
JOIN Designer_0506 d ON cd.designer_id = d.designer_id
WHERE d.d_name = 'MariaB';

-- ------------------------------------------------
-- Task 22
-- ------------------------------------------------

DELETE FROM CustomerDesigner_0506 
WHERE customer_id = (SELECT customer_id FROM Customer_0506 WHERE c_name = 'Kashif');

DELETE FROM Customer_0506 
WHERE c_name = 'Kashif';

-- ------------------------------------------------
-- Task 23
-- ------------------------------------------------

UPDATE Designer_0506 
SET d_contact_number = '0300-1111111' 
WHERE d_name = 'Khaadi';

-- ------------------------------------------------
-- Task 24
-- ------------------------------------------------

SELECT DISTINCT d.d_name, d.d_contact_number 
FROM Designer_0506 d
JOIN CustomerDesigner_0506 cd ON d.designer_id = cd.designer_id
WHERE cd.priority = 'Urgent';