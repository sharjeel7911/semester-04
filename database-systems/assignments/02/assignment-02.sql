
SET SQL_SAFE_UPDATES = 0;

CREATE DATABASE IF NOT EXISTS Assignment_02;
USE Assignment_02;
SELECT DATABASE();

-- ----------------------------------------

-- Question - 01 --

-- 1. Actor table
CREATE TABLE Actor (
    act_id INT NOT NULL AUTO_INCREMENT,
    act_name VARCHAR(50) NOT NULL,
    act_gender CHAR(1) NOT NULL CHECK (act_gender IN ('M' , 'F')),
    PRIMARY KEY (act_id)
);

-- 2. Director table
CREATE TABLE Director (
    dir_id INT NOT NULL AUTO_INCREMENT,
    dir_name VARCHAR(50) NOT NULL,
    dir_phone VARCHAR(15) UNIQUE,
    PRIMARY KEY (dir_id)
);

-- 3. Movie table
CREATE TABLE Movie (
    mov_id INT NOT NULL AUTO_INCREMENT,
    mov_title VARCHAR(50) NOT NULL,
    mov_year INT NOT NULL CHECK (mov_year >= 1900 AND mov_year <= 2030),
    mov_lang VARCHAR(20) NOT NULL DEFAULT 'English',
    mov_type VARCHAR(20),
    dir_id INT NOT NULL,
    PRIMARY KEY (mov_id),
    CONSTRAINT fk_movie_director FOREIGN KEY (dir_id)
        REFERENCES Director (dir_id)
        ON DELETE CASCADE ON UPDATE CASCADE
);

-- 4. Movie_Cast table
CREATE TABLE Movie_Cast (
    cast_role VARCHAR(50) NOT NULL, act_id INT NOT NULL, mov_id INT NOT NULL,
    PRIMARY KEY (act_id , mov_id , cast_role),
    CONSTRAINT fk_cast_actor FOREIGN KEY (act_id) REFERENCES Actor (act_id) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT fk_cast_movie FOREIGN KEY (mov_id) REFERENCES Movie (mov_id) ON DELETE CASCADE ON UPDATE CASCADE
);

-- 5. RATING table
CREATE TABLE Rating (
    rating_id INT AUTO_INCREMENT, mov_id INT,
    rev_stars DECIMAL(2 , 1 ) CHECK(rev_stars >= 0 AND rev_stars <= 5.0),
    PRIMARY KEY (rating_id),
    CONSTRAINT fk_rating_movie FOREIGN KEY (mov_id) REFERENCES Movie (mov_id) ON DELETE CASCADE ON UPDATE CASCADE
);

-- ----------------------------------------

-- Question - 02 --

-- 1. Actor table
INSERT INTO Actor(act_name, act_gender) VALUES
('Cary Grant', 'M'), ('Grace Kelly', 'F'), ('James Stewart', 'M'), ('Kim Novak', 'F'), ('Tippi Hedren', 'F'),
('Tom Hanks', 'M'), ('Meryl Streep', 'F'), ('Harrison Ford', 'M'), ('Meg Ryan', 'F'), ('Richard Dreyfuss', 'M'),
('Denzel Washington', 'M'), ('Sandra Bullock', 'F'), ('Brad Pitt', 'M'), ('Angelina Jolie', 'F'), ('Leonardo DiCaprio', 'M'),
('Kate Winslet', 'F'), ('Johnny Depp', 'M'), ('Helena Carter', 'F'), ('Will Smith', 'M'), ('Cameron Diaz', 'F'),
('Keanu Reeves', 'M'), ('Jennifer Aniston', 'F'), ('Robert Downey Jr.', 'M'), ('Scarlett Johansson', 'F'), ('Chris Evans', 'M'),
('Cate Blanchett', 'F'), ('Sam Neill', 'M'), ('Laura Dern', 'F'), ('Joseph Gordon', 'M'), ('Embeth Dave', 'F');

-- 2. Director table
INSERT INTO Director(dir_name, dir_phone) VALUES
('Alfred Hitchcock', '0300-1000001'), ('Steven Spielberg', '0300-1000002'), ('Martin Scorsese', '0300-1000003'),
('Quentin Tarantino', '0300-1000004'), ('Christopher Nolan', '0300-1000005'), ('James Cameron', '0300-1000006'),
('Ridley Scott', '0300-1000007'), ('David Fincher', '0300-1000008'), ('Denis Villeneuve', '0300-1000009'),
('Wes Anderson', '0300-1000010'), ('Joel Coen', '0300-1000011'), ('Ethan Coen', '0300-1000012'),
('Paul Thomas', '0300-1000013'), ('Darren Aronofsky', '0300-1000014'), ('Duncan Jones', '0300-1000015'),
('Michel Gondry', '0300-1000016'), ('Charlie Kaufman', '0300-1000017'), ('Tony Scott', '0300-1000018'),
('Michael Mann', '0300-1000019'), ('Spike Lee', '0300-1000020'), ('Kathryn Bigelow', '0300-1000021'),
('Peter Jackson', '0300-1000022'), ('Francis Coppola', '0300-1000023'), ('Stanley Kubrick', '0300-1000024'),
('George Lucas', '0300-1000025'), ('Satyajit Ray', '0300-1000026'), ('Akira Kurosawa', '0300-1000027'),
('Roman Polanski', '0300-1000028'), ('Elia Kazan', '0300-1000029'), ('Billy Wilder', '0300-1000030');

-- 3. Movie table
INSERT INTO Movie(mov_title, mov_year, mov_lang, mov_type, dir_id) VALUES
('Vertigo', 1958, 'English', 'Thriller', 1), ('Rear Window', 1954, 'English', 'Thriller', 1), 
('Psycho', 1960, 'English', 'Horror', 1), ('The Birds', 1963, 'English', 'Horror', 1),
('Rope', 1948, 'English', 'Thriller', 1), ('Jaws', 1975, 'English', 'Thriller', 2),
('Jurassic Park', 1993, 'English', 'Adventure', 2), ('E.T. the Extra-Terrestrial', 1982, 'English', 'Sci-Fi', 2),
('War Horse', 2011, 'English', 'Drama', 2), ('Saving Private Ryan', 1998, 'English', 'War', 2),
('Taxi Driver', 1976, 'English', 'Drama', 3), ('Raging Bull', 1980, 'English', 'Drama', 3),
('The Irishman', 2019, 'English', 'Crime', 3), ('Goodfellas', 1990, 'English', 'Crime', 3),
('The Wolf of Wall Street', 2013, 'English', 'Drama', 3), ('Pulp Fiction', 1994, 'English', 'Crime', 4),
('Kill Bill Vol. 1', 2003, 'English', 'Action', 4), ('Inglourious Basterds', 2009, 'English', 'War', 4),
('The Hateful Eight', 2015, 'English', 'Thriller', 4), ('Django Unchained', 2012, 'English', 'Western', 4),
('Inception', 2010, 'English', 'Sci-Fi', 5), ('Interstellar', 2014, 'English', 'Sci-Fi', 5),
('The Dark Knight', 2008, 'English', 'Action', 5), ('Titanic', 1997, 'English', 'Romance', 6),
('Avatar', 2009, 'English', 'Sci-Fi', 6), ('Blade Runner 2049', 2017, 'English', 'Sci-Fi', 7),
('Gladiator', 2000, 'English', 'Action', 7), ('The Social Network', 2010, 'English', 'Drama', 8),
('Gone Girl', 2014, 'English', 'Thriller', 8), ('Dune', 2021, 'English', 'Sci-Fi', 9);

-- 4. Movie_Cast table
INSERT INTO Movie_Cast(cast_role, act_id, mov_id) VALUES
('hero', 1, 1), ('heroine', 2, 1), ('brother', 3, 1), ('friend', 4, 1), ('hero', 3, 2), ('heroine', 2, 2), ('brother', 1, 2),
('friend', 5, 2), ('hero', 1, 3), ('heroine', 2, 3), ('brother', 3, 3), ('friend', 4, 3), ('hero', 5, 4), ('heroine', 2, 4), 
('brother', 1, 4), ('friend', 3, 4), ('hero', 3, 5), ('heroine', 2, 5), ('brother', 4, 5), ('friend', 1, 5), ('hero', 10, 6),
('heroine', 9, 6), ('brother', 6, 6), ('friend', 7, 6), ('hero', 8, 7), ('heroine', 26, 7), ('brother', 27, 7), ('friend', 28, 7),
('hero', 6, 8), ('heroine', 12, 8), ('brother', 11, 8), ('friend', 13, 8);

-- 5. RATING table
INSERT INTO Rating(mov_id, rev_stars) VALUES
(1, 4.5), (1, 5.0), (1, 4.8), (2, 4.7), (2, 4.5), (3, 4.8), (3, 4.6), (4, 4.5), (4, 4.7), (5, 4.3), 
(6, 4.5), (6, 4.6), (7, 4.4), (7, 4.5), (8, 4.8), (8, 4.7), (8, 4.5), (9, 4.2), (10, 4.6), (10, 4.7),
(11, 4.5), (12, 4.7), (13, 4.3), (14, 4.8), (15, 4.6), (20, 4.9), (21, 4.8), (22, 4.5), (28, 4.7), (30, 4.6);

-- ----------------------------------------

-- Question - 03 --

SELECT mov_title
FROM Movie
WHERE dir_id = (SELECT dir_id FROM Director WHERE dir_name = 'Alfred Hitchcock');

-- ----------------------------------------

-- Question - 04 --

SELECT mov_title, act_name
FROM Movie, Actor
WHERE act_id IN (SELECT act_id FROM Movie_Cast WHERE mov_id = Movie.mov_id);	

-- ----------------------------------------

-- Question - 05 --

SELECT COUNT(*) AS brother_count 
FROM Movie_Cast
WHERE cast_role = 'brother';

-- ----------------------------------------

-- Question - 06 --

SELECT mov_title FROM Movie
WHERE mov_id IN 
	(SELECT mov_id FROM Movie_Cast WHERE act_id IN 
		(SELECT act_id FROM Movie_Cast GROUP BY act_id HAVING COUNT(mov_id) >= 2));

-- ----------------------------------------

-- Question - 07 --

SELECT act_name
FROM Actor
WHERE 
act_id IN 
    (SELECT act_id FROM Movie_Cast WHERE mov_id IN
        (SELECT mov_id FROM Movie WHERE mov_year < 2021))
AND 
act_id IN 
    (SELECT act_id FROM Movie_Cast WHERE mov_id IN
        (SELECT mov_id FROM Movie WHERE mov_year > 2023));

-- ----------------------------------------

-- Question - 08 --

SELECT mov_title
FROM Movie
WHERE 
	mov_id IN (SELECT mov_id FROM Movie_Cast WHERE act_id IN 
		(SELECT act_id FROM Actor WHERE act_name IN 
			(SELECT dir_name FROM Director))
);

-- ----------------------------------------

-- Question - 09 --

SELECT dir_name
FROM Director
WHERE
    dir_id IN (SELECT dir_id FROM Movie WHERE (mov_year >= 2020 AND mov_year <= 2024)
	GROUP BY dir_id HAVING COUNT(mov_id) > 5);

-- ----------------------------------------

-- Question - 10 --

	SELECT mov_title, (SELECT MAX(rev_stars) FROM Rating WHERE Rating.mov_id = Movie.mov_id) AS highest_stars FROM Movie
	WHERE mov_id IN (SELECT mov_id FROM Rating) ORDER BY mov_title;

-- ----------------------------------------

-- Question - 11 --

SELECT (SELECT mov_title FROM Movie WHERE Movie.mov_id = Rating.mov_id) AS mov_title, AVG(rev_stars) AS avg_rating
FROM Rating GROUP BY mov_id;

-- ----------------------------------------

-- Question - 12 --

SELECT mov_title
FROM Movie
WHERE dir_id = (SELECT dir_id FROM Director WHERE dir_name = 'Steven Spielberg');

-- ----------------------------------------

-- Question - 13 --

ALTER TABLE Movie_Cast
ADD COLUMN is_lead BOOLEAN NOT NULL DEFAULT 0;

UPDATE Movie_Cast
SET is_lead = 1 WHERE cast_role IN ('hero', 'heroine');

-- ----------------------------------------

-- Question - 14 --

SELECT * FROM Movie
WHERE mov_type = 'Kids';

-- ----------------------------------------

-- Question - 15 --

SELECT * FROM Movie
WHERE mov_type = 'Animated' AND mov_year > 2022 AND mov_id IN (SELECT mov_id FROM Rating WHERE rev_stars >= 3.5);

-- ----------------------------------------

-- Question - 16 --

SELECT * FROM Movie
WHERE mov_type = 'Action';