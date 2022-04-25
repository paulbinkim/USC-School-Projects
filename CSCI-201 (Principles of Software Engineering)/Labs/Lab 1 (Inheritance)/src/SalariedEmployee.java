
public class SalariedEmployee extends Employee {
	public double annualSalary;
	
	public double getAnnualSalary() {
		return this.annualSalary;
	}
	public SalariedEmployee(String firstName, String lastName, String Birthday, int employeeID, String jobTitle, String company, double annual) {
		super.firstName = firstName; 
		super.lastName = lastName;
		super.Birthday = Birthday;
		super.employeeID = employeeID;
		super.jobTitle = jobTitle;
		super.company = company;
		this.annualSalary = annual;
	}
}
