CREATE DATABASE IF NOT EXISTS sal_eats;

CREATE TABLE IF NOT EXISTS `sal_eats`.`users` (
  `email` VARCHAR(45) NOT NULL UNIQUE,
  `name` VARCHAR(45) NOT NULL,
  `password` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`email`) 
);

CREATE TABLE `favorites` (
  `email` varchar(45) NOT NULL,
  `restaurant` varchar(45) NOT NULL,
  `id` int NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`)
);