
public class HourlyEmployee extends Employee{
	public double hourlyRate;
	public double numberHoursPerWeek;
	
	public double getAnnualSalary() {
		return (this.hourlyRate*this.numberHoursPerWeek)*52;
	}
	
	public HourlyEmployee(String firstName, String lastName, String Birthday, int employeeID, String jobTitle, String company, double hourly, double hoursperweek) {
		super.firstName = firstName; 
		super.lastName = lastName;
		super.Birthday = Birthday;
		super.employeeID = employeeID;
		super.jobTitle = jobTitle;
		super.company = company;
		this.hourlyRate = hourly;
		this.numberHoursPerWeek = hoursperweek;
	}
}