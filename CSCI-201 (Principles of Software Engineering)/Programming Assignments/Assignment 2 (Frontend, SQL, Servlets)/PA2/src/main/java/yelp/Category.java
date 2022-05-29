package yelp;

import java.io.Serializable;

/**
 * Represents a food category for a Yelp restaurant.
 */
public class Category implements Serializable {

	private static final long serialVersionUID = 1595109626124665225L;

	private String alias;
	private String title;
	
	public String getAlias() {
		return alias;
	}
	
	public String getTitle() {
		return title;
	}
}
