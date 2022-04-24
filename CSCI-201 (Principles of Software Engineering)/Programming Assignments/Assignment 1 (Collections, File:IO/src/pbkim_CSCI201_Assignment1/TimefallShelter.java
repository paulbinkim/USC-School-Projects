package pbkim_CSCI201_Assignment1;

import java.io.FileNotFoundException;
import java.util.Collections;

public class TimefallShelter implements Comparable<TimefallShelter> {
	/**
	 * Here: all the needed class members and their getters and setters
	 */
	
	private Integer chiralFrequency = 0;
	private Boolean timefall = false;
	private String guid = "";
	private String name = "";
	private String phone = "";
	private String address = "";
	// Another line is valid (do not print out an error message if so)
	
	public void setChiral(int Chiral) {
		this.chiralFrequency = Chiral;
	}
	
	public void setTimefall(Boolean timefall) {
		this.timefall = timefall;
	}
	
	public void setGuid(String guid) {
		this.guid = guid;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	public void setPhone(String phone) {
		this.phone = phone;
	}
	
	public void setAddress(String address) {
		this.address = address;
	}
	
	public Integer getChiral() {
		return this.chiralFrequency;
	}
	
	public Boolean getTimefall() {
		return this.timefall;
	}
	
	public String getGuid() {
		return this.guid;
	}
	
	public String getName() {
		return this.name;
	}
	
	public String getPhone() {
		return this.phone;
	}
	
	public String getAddress() {
		return this.address;
	}
	

	/**
	 * overriding comparator for sorting
	 */

	@Override
	public int compareTo(TimefallShelter compShelter) {
		/* For Ascending order*/
		// We use this to compare objects by chiralFrequencies
		return this.chiralFrequency - compShelter.chiralFrequency;
		// Can use getters too
	}

	/**
	 * String representation of a shelter
	 */
	@Override
	public String toString() {
		String timefall;
		if (getTimefall() == true) {
			timefall = "Current";
		}
		else {
			timefall = "None";
		}
		String solution = "Shelter information:\n";
		solution += "- Chiral frequency: " + String.valueOf(getChiral()) + "\n"; // We do this cause Chiral is integer
		solution += "- Timefall: " + timefall + "\n";
		solution += "- GUID: " + getGuid() + "\n";
		solution += "- Name: " + getName() + "\n";
		solution += "- Phone: " + getPhone() + "\n";
		solution += "- Address: " + getAddress() + "\n";
		return solution;
	}
}
