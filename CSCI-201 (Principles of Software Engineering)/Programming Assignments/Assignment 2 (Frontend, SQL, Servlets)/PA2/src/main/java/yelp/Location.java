package yelp;

import java.io.Serializable;

/**
 * Represents a restaurant address
 */
public class Location implements Serializable {

	private static final long serialVersionUID = -2155740990206958341L;

	private String address1;
	private String city;
	private String zip_code;
	
	@Override
	public String toString() {
		return address1 + ", " + city + ", " + zip_code;
	}
}
