
public abstract class Employee extends Person {
	public int employeeID;
	public String jobTitle;
	public String company;
	
	public abstract double getAnnualSalary();
	
	public int getEmployeeID() { // INT is OKAY?
		return employeeID;
	}
	public String getJobTitle() {
		return jobTitle;
	}
	public String getCompany() {
		return company;
	}
	
}
