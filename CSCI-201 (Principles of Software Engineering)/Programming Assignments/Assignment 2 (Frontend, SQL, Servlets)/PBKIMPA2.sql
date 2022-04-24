DROP DATABASE IF EXISTS PA2PBKIM;
CREATE DATABASE PA2PBKIM;
USE PA2PBKIM;

CREATE TABLE Users (
	email VARCHAR(64) NOT NULL UNIQUE,
    fullname VARCHAR(64) NOT NULL,
    password VARCHAR(64)
);

CREATE TABLE Restaurant_Details (
	details_id INT PRIMARY KEY NOT NULL,
    image_url VARCHAR(200) NOT NULL,
    address VARCHAR(64) NOT NULL,
    phone_no VARCHAR(64) NOT NULL,
    estimated_price VARCHAR(64),
    yelp_url VARCHAR(500) NOT NULL
);

CREATE TABLE Category (
	category_id INT PRIMARY KEY NOT NULL,
    category_name VARCHAR(64) NOT NULL
);

CREATE TABLE Rating_Details (
	rating_id INT PRIMARY KEY NOT NULL,
    review_count VARCHAR(64) NOT NULL,
    rating VARCHAR(64) NOT NULL
);

CREATE TABLE Restaurant (
	restaurant_id VARCHAR(64) PRIMARY KEY NOT NULL UNIQUE,
    restaurant_name VARCHAR(64) NOT NULL,
    details_id INT NOT NULL,
    rating_id INT NOT NULL,
    category_id INT NOT NULL,
    FOREIGN KEY (details_id) REFERENCES Restaurant_Details(details_id),
	FOREIGN KEY (rating_id) REFERENCES Rating_Details(rating_id),
    FOREIGN KEY (category_id) REFERENCES Category(category_id)
);

SELECT * FROM Restaurant_Details;
SELECT * FROM Category;
SELECT * FROM Rating_Details;
SELECT * FROM Restaurant;
SELECT * from Restaurant WHERE restaurant_name= 'Reimer''s Candies & Gifts';
SELECT * FROM Restaurant, Rating_Details, Category, Restaurant_Details WHERE Restaurant_Details.details_id = 33 AND Rating_Details.rating_id = 33 AND Category.category_id = 33;

