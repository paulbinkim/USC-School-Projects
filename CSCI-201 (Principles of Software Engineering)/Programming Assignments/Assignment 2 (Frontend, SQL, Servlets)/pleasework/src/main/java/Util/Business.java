package Util;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * The class used to model a business
 */
public class Business {
	private String id;
	private String alias;
	private String name;
	private String image_url;
	private boolean is_closed;
	private String url;
	private int review_count;
	private ArrayList<HashMap<String, String>> categories;
	private double rating;
	private HashMap<String, Double> coordinates;
	private ArrayList<String> transactions;
	private String price;
	private HashMap<String, Object> location;
	private String phone;
	private String display_phone;
	private double distance;
	
    public Business(String id, String alias, String name, String image_url, boolean is_closed, String url, int reviewCount, ArrayList<HashMap<String, String>> categories, double rating, HashMap<String, Double> coordinates, ArrayList<String> transactions, String price, HashMap<String, Object> location, String phone, String display_phone, double distance) {
        //TODO Initialization code
    	this.id = id;
    	this.alias = alias;
    	this.name = name;
    	this.image_url = image_url;
    	this.is_closed = is_closed;
    	this.url = url;
    	this.review_count = reviewCount;
    	this.categories = categories;
    	this.rating = rating;
    	this.coordinates = coordinates;
    	this.transactions = transactions;
    	this.price = price;
    	this.location = location;
    	this.phone = phone;
    	this.display_phone = display_phone;
    	this.distance = distance;
    }

    //TODO Add Getters (No Setters as the business does not change in our assignment once constructed)
	public String getID() {
		return this.id;
	}
	public String getAlias() {
		return this.alias;
	}
	public String getName() {
		return this.name;
	}
	public String getPhone() {
		return this.phone;
	}
	public String getimageURL() {
		return this.image_url;
	}
	public boolean getClosed() {
		return this.is_closed;
	}
	public String getURL() {
		return this.url;
	}
	public ArrayList<HashMap<String, String>> getCatergories() {
		return this.categories;
	}
	public int getReviewCount() {
		return this.review_count;
	}
	public double getRating() {
		return this.rating;
	}
	public HashMap<String, Double> getCoordinates () {
		return this.coordinates;
	}
	public ArrayList<String> getTransactions() {
		return this.transactions;
	}
	public String getPrice() {
		return this.price;
	}
	public HashMap<String, Object> getLocation() {
		return this.location;
	}
	public String getDisplayPhone() {
		return this.display_phone;
	}
	public double getDistance() {
		return this.distance;
	}
}	

