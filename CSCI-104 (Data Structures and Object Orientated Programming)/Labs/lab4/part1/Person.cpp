#include "Person.h"
#include <iostream>

using namespace std;

Person::Person(std::string name) {
	mName = name;
}

std::string Person::getName() {
	return mName;
}

Professor::Professor(std::string name, std::string department) : Person(name) { // Person(name) is the explicit call to constructor
	mName = name;
}

std::string Professor::getDepartment() {
	return mDepartment;
}

Student::Student(std::string name, std::string major) : Person(name) {
	mName = name;
}

void Student::setGPA(double gpa) {
	mGpa = gpa;
}

std::string Student::getMajor() {
	return mMajor;
}

UscStudent::UscStudent(std::string name, std::string major, double gpa) : Student(name, major) {
	mName = name;
	mMajor = major;
	setGPA(gpa);
}

void UscStudent::printTranscript() {
	std::cout << "Student Name: " << mName << std::endl; // Since we are calling the UscStudent object declared in tests, this works (no need period)
	std::cout << "Student GPA: " << mGpa << std::endl;
	std::cout << "Student Major: " << mMajor << std::endl;
}

// Dynamic vs Static Binding