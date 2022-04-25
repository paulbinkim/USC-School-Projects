DROP DATABASE IF EXISTS lab7;
CREATE DATABASE lab7;

USE lab7;

DROP TABLE IF EXISTS Department;
DROP TABLE IF EXISTS Course;
DROP TABLE IF EXISTS Student;
DROP TABLE IF EXISTS Enrollment;
DROP TABLE IF EXISTS Faculty;
DROP TABLE IF EXISTS TaughtBy;

CREATE TABLE Department (
  deptPrefix VARCHAR(4) PRIMARY KEY NOT NULL, 
  deptName VARCHAR(25) UNIQUE 
);
INSERT INTO Department (deptPrefix, deptName) VALUES 
('CS', 'Computer Science'),
('MATH', 'Mathematics'),
('CHEM', 'Chemistry'),
('EDUC', 'Education'),
('ACCT', 'Accounting'),
('BIOL', 'Biology');

CREATE TABLE Course(
  courseId VARCHAR(5) PRIMARY KEY NOT NULL,
  courseTitle VARCHAR (50) NOT NULL
);

INSERT INTO Course VALUES 
('11111', 'Intro to Java I'),
('11112', 'Intro to Java II'),
('11113', 'Database Systems'),
('11114', 'Rapid Java Application'),
('11115', 'Calculus I'),
('11116', 'Calculus II'),
('11117', 'Reading'),
('11118', 'Database Administration');

CREATE TABLE Enrollment (
  ssn VARCHAR(9) NOT NULL, 
  courseId VARCHAR(5) NOT NULL,
  dateRegistered date,
  grade VARCHAR(2),
  CONSTRAINT pkEnrollment PRIMARY KEY (ssn, courseId)
);

INSERT INTO Enrollment VALUES 
('444111110', '11111', now(), 'A'),
('444111110', '11112', now(), 'B'),
('444111110', '11113', now(), 'C'),
('444111111', '11111', now(), 'D'),
('444111111', '11112', now(), 'F'),
('444111111', '11113', now(), 'A'),
('444111112', '11111', now(), 'A'),
('444111112', '11112', now(), 'B'),
('444111112', '11114', now(), 'B'),
('444111112', '11115', now(), 'C'),
('444111112', '11116', now(), 'D'),
('444111113', '11111', now(), 'F'),
('444111113', '11113', now(), 'F'),
('444111114', '11115', now(), 'C'),
('444111115', '11115', now(), 'B'),
('444111115', '11116', now(), 'W'),
('444111116', '11111', now(), 'IN'),
('444111117', '11111', now(), 'MG'),
('444111118', '11111', now(), 'P'),
('444111118', '11112', now(), 'NP'),
('444111118', '11113', now(), 'IX');

CREATE TABLE Faculty(
  SSN VARCHAR(9) PRIMARY KEY NOT NULL, 
  firstName VARCHAR(25), 
  mi VARCHAR(1), 
  lastName VARCHAR(25), 
  ranking VARCHAR(20), 
  deptPrefix VARCHAR(4)
);

INSERT INTO Faculty VALUES 
('111221110', 'Patty', 'R', 'Smith', 'Full Professor', 'MATH'),
('111221111', 'George', 'P', 'Franklin', 'Associate Professor', 'CS'),
('111221112', 'Jean', 'D', 'Yao', 'Full Professor', 'MATH'),
('111221113', 'Frank', 'E', 'Goldman', 'Assistant Professor', 'ACCT'),
('111221114', 'Steve', 'T', 'Templeton', 'Assistant Professor', 'ACCT'),
('111221115', 'Alex', 'T', 'Bedat', 'Full Professor', 'CS'),
('111221116', 'Judy', 'T', 'Woo', 'Full Professor', 'MATH'),
('111221117', 'Joe', 'R', 'Chang', 'Full Professor', 'EDUC'),
('111221118', 'Francis', 'R', 'Chin', 'Full Professor', 'BIOL'),
('111221119', 'Ray', 'R', 'Smith', 'Full Professor', 'CHEM');

/* Create the Student and TaughtBy tables */

CREATE TABLE Student (
	SSN VARCHAR(9) PRIMARY KEY NOT NULL, 
	firstName VARCHAR(25), 
	mi VARCHAR(1), 
	lastName VARCHAR(25), 
	deptPrefix VARCHAR(4)
);

CREATE TABLE TaughtBy (
	ID INT PRIMARY KEY AUTO_INCREMENT,
	courseID VARCHAR (5) NOT NULL,
    SSN VARCHAR(9)  NOT NULL
);

/* Insert data values from instructions into Student and 
   TaughtBy tables */
   
INSERT INTO Student VALUES
	('444111110', 'Jacob', 'R', 'Smith', 'BIOL'),
	('444111111', 'John', 'K', 'Stevenson', 'BIOL'),
	('444111112', 'George', 'R', 'Heintz', 'CS'),
	('444111113', 'Frank', 'E', 'Jones', 'BIOL'),
	('444111114', 'Jean', 'K', 'Smith', 'CHEM'),
	('444111115', 'Josh', 'R', 'Woo', 'CHEM'),
	('444111116', 'Josh', 'R', 'Smith', 'BIOL'),
	('444111117', 'Joy', 'P', 'Kennedy', 'CS'),
	('444111118', 'Toni', 'R', 'Peterson', 'MATH'),
	('444111119', 'Patrick', 'R', 'Stoneman', 'MATH'),
	('444111120', 'Rick', 'R', 'Carter', 'BIOL');
    
INSERT INTO TaughtBy (courseID, SSN) VALUES
	('11111', '111221111'),
    ('11112', '111221111'),
    ('11113', '111221111'),
    ('11114', '111221115'),
    ('11115', '111221110'),
    ('11116', '111221115'),
    ('11117', '111221116'),
    ('11118', '111221112');

/* a) Print all of the CONCATENATED firstnames, mi, & lastnames as a column 
      called "Full Name" */
      
SELECT CONCAT(s.firstName, ', ', s.mi, ', ', s.lastName) as "Full Name"
	FROM Student s;

/* b) Print the count of students in each department */

SELECT d.deptName AS "Department" , COUNT(s.firstName) AS "Student Count"
	FROM Student s
    LEFT JOIN Department d
		ON s.deptPrefix = d.deptPrefix
        GROUP BY d.deptName;
        
/* c) Print all of the student firstnames and lastnames whose firstnames    
      start with 'J' from 'Student' */

SELECT CONCAT(s.firstName, ', ', s.lastName) as "J's FirstName"
	FROM Student s
    WHERE firstName LIKE 'J%';

/* d) Print the firstname, middle initial, lastname, ranking and courseID 
      taught by each faculty member (you MUST use the INNER JOIN keyword) and 
      ORDER BY firstName */
      
SELECT f.firstName, f.mi, f.lastName, f.ranking, t.courseID
	FROM Faculty f
	INNER JOIN TaughtBy t ON f.SSN = t.SSN
	ORDER BY f.firstName;

/* e) Print all of the course titles and grades for George using his 
      SSN 444111112 (you may NOT use the INNER JOIN keyword)  */

SELECT c.courseTitle, e.grade
	FROM Course c, Enrollment e
    WHERE e.SSN = '444111112'
    AND c.courseID = e.courseID;

/* f) Print all enrolled students firstnames, mi, and lastnames, course title, 
      date registered for course, and grade in course. (HINT: This is an INNER 
      JOIN with three tables)  */
      
	SELECT s.firstName, s.mi, s.lastName, c.courseTitle, e.dateRegistered, e.grade
		FROM Student s
        INNER JOIN Enrollment e ON s.SSN = e.ssn
        INNER JOIN Course c ON c.courseID = e.courseID;
        
/* g) Delete Jacob R Smith from 'Student' using his SSN: 444111110 */

SELECT CONCAT(s.firstName, ', ', s.mi, ', ', s.lastName) as "Student's Full Name"
	FROM Student s;

DELETE FROM Student WHERE SSN = '444111110';

SELECT CONCAT(s.firstName, ', ', s.mi, ', ', s.lastName) as "Student's Full Name"
	FROM Student s;
