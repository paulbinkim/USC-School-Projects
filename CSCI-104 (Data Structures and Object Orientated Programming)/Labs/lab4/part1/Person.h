#include <string>

class Person {
	public:
		Person(std::string name);
		std::string getName();
	protected:
		std::string mName;
		int mAge;
};

class Professor : public Person {
	public:
		Professor(std::string name, std::string department);
		std::string getDepartment();
	private:
		int mSalary;
		std::string mDepartment;
};

class Student : public Person {
	public:
		Student(std::string name, std::string major);
		std::string getMajor();
		void setGPA(double gpa);
	protected:
		std::string mMajor;
		double mGpa;
};

class UscStudent : protected Student { // Since protected, other people (such as a USC student) cannot make changes to GPA
	public:
		UscStudent(std::string name, std::string major, double gpa);
		std::string getUscEmail();
		void printTranscript();
	private:
		int mUscID;
		std::string mUscEmail;
};

// Professor x = new Professor (This is an object, an instantation of a class (such as Professor Cote, Professor Redekopp))
// If trying to access data members here, you need the period syntax