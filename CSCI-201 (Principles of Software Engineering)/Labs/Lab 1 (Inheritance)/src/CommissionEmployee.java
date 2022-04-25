
public class CommissionEmployee extends SalariedEmployee {
	public double salesTotal;
	public double commissionPercentage;
	
	@Override
	public double getAnnualSalary() {
		return super.annualSalary + (this.salesTotal*this.commissionPercentage);
	}
	
	public CommissionEmployee(String firstName, String lastName, String Birthday, int employeeID, String jobTitle, String company, double base, double salesTotal, double commission) {
		super(firstName, lastName, Birthday, employeeID, jobTitle, company, base);
		this.salesTotal = salesTotal;
		this.commissionPercentage = commission;
	}
}