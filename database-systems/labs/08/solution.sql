SET SQL_SAFE_UPDATES = 0;

CREATE DATABASE SMCIS;
USE SMCIS;

-- Basic DDL

CREATE TABLE User (
    user_id INT AUTO_INCREMENT,
    username VARCHAR(20),
    email VARCHAR(20) UNIQUE,
    password VARCHAR(20),
    dob DATE,
    profile_type VARCHAR(20),
    PRIMARY KEY(user_id)
); 

CREATE TABLE Post (
    post_id INT AUTO_INCREMENT,
    content VARCHAR(100),
    media_url VARCHAR(20) UNIQUE,
    created_at DATE,
    visibility VARCHAR(20),
    user_id INT,
    PRIMARY KEY (post_id),
	CONSTRAINT fk_user FOREIGN KEY (user_id)
		REFERENCES User (user_id) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE Story (
    story_id INT AUTO_INCREMENT,
    media_url VARCHAR(20) UNIQUE,
    created_at DATE,
    expiry_time TIME,
    user_id INT,
    PRIMARY KEY (story_id),
	CONSTRAINT fk_user FOREIGN KEY (user_id)
		REFERENCES User (user_id) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE Comment (
    comment_id INT AUTO_INCREMENT,
    text VARCHAR(100),
    comment_date DATE,
    user_id INT,
    post_id INT,
    PRIMARY KEY (comment_id , user_id, post_id),
    CONSTRAINT fk_user FOREIGN KEY (user_id)
        REFERENCES User (user_id) ON DELETE CASCADE ON UPDATE CASCADE,
	CONSTRAINT fk_post FOREIGN KEY (post_id)
		REFERENCES Post (post_id) ON DELETE CASCADE ON UPDATE CASCADE    
); 

CREATE TABLE Reaction (
    reaction_id INT AUTO_INCREMENT,
    type VARCHAR(20),
    reaction_date DATE,
    user_id INT,
    post_id INT,
    PRIMARY KEY (reaction_id , user_id, post_id),
    CONSTRAINT fk_user FOREIGN KEY (user_id)
        REFERENCES User (user_id) ON DELETE CASCADE ON UPDATE CASCADE,
   CONSTRAINT fk_post FOREIGN KEY (post_id)
		REFERENCES Post (post_id) ON DELETE CASCADE ON UPDATE CASCADE      
); 

CREATE TABLE Follow (
    follow_id INT,
    follow_date DATE,
    follower_id INT,
    following_id INT,
    PRIMARY KEY (follow_id, follower_id, following_id),
    CONSTRAINT fk_follower FOREIGN KEY (follower_id)
        REFERENCES User (user_id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_following FOREIGN KEY (following_id)
        REFERENCES User (user_id) ON DELETE CASCADE ON UPDATE CASCADE    
); 

-- 01
ALTER TABLE User
ADD COLUMN bio varchar(150);

-- 02
ALTER TABLE Post
MODIFY COLUMN content TEXT;

-- 03
ALTER TABLE Reaction
RENAME TO Post_Reaction;

-- 04
ALTER TABLE Story
DROP COLUMN media_url;

-- ---------------------------------------------------------------------------------------\\

-- Basic DML

-- 01
SELECT username FROM User
WHERE profile_type = 'public';

-- 02
SELECT * FROM User;

-- 03
SELECT email FROM User
WHERE profile_type = 'private';

-- 04
SELECT DISTINCT profile_type
FROM User;

-- 05
SELECT * FROM Post;

-- 06
UPDATE User 
SET email = 'xyz@gmail.com'
WHERE user_id = 1;

-- -----------------------------------------------------------------------