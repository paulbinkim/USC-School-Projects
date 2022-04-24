package Util;

import java.util.Collection;
import java.util.Scanner;
import java.util.*;

import com.google.gson.*;
import com.google.gson.reflect.TypeToken;
import com.google.gson.stream.JsonReader;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonParseException;
import com.google.gson.reflect.TypeToken;
import com.google.gson.stream.JsonReader; // Tool that I found online

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.Reader;
import java.lang.reflect.Type;
import java.net.URISyntaxException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import com.google.gson.JsonObject;


import java.sql.*;

/**
 * A class that pretends to be the Yelp API
 */
public class RestaurantDataParser {
	private static Boolean ready = false;

	/**
	 * Initializes the Database with JSON data
	 *
	 * @param responseString the Yelp JSON string
	 */
	public static void Init(String response) {
		String db = "jdbc:mysql://localhost/PA2PBKIM";
		String user = "root";
		String pwd = "root";
		boolean ready = false;
		if (ready) {
			return;
		}
		// Connect to SQL
		try {
			Class.forName("com.mysql.cj.jdbc.Driver");
		} 
		catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		
		ready = true;
		
		// Read in JSON File
		Reader read = null;
		try {
			read = new FileReader(response);
		} 
		catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		
		ArrayList<Business> Businesses;
			
		// TODO Get Business Data from JSON
		// "How to Read JSON from a File using GSON" (Online Documentation) (Copy Paste PA1)
		try {
			JsonReader file = new JsonReader(read);
			Businesses = new Gson().fromJson(file, new TypeToken<ArrayList<Business>>() {
	        }.getType());
			Connection conn = DriverManager.getConnection(db, user, pwd);
			String checkPop = "SELECT restaurant_name FROM Restaurant";
			Statement st1 = conn.createStatement();
			ResultSet rs1 = st1.executeQuery(checkPop);
			if (rs1.next()) {
				return;
			}
			for (int i = 0; i < Businesses.size(); i++) {	
				String id = Businesses.get(i).getID();
				String alias = Businesses.get(i).getAlias();
				String name = Businesses.get(i).getName();
				String image_url = Businesses.get(i).getimageURL();
				boolean is_closed = Businesses.get(i).getClosed();
				String url = Businesses.get(i).getURL();
				int reviewCount = Businesses.get(i).getReviewCount();
				ArrayList<HashMap<String, String>> categories = Businesses.get(i).getCatergories();
				double rating = Businesses.get(i).getRating();
				HashMap<String, Double> coordinates = Businesses.get(i).getCoordinates();
				ArrayList<String> transactions = Businesses.get(i).getTransactions();
				String price = Businesses.get(i).getPrice();
				HashMap<String, Object> location = Businesses.get(i).getLocation();
				String phone = Businesses.get(i).getPhone();
				String display_phone = Businesses.get(i).getDisplayPhone();
				double distance = Businesses.get(i).getDistance();
				
				String DisplayLocation = String.valueOf(location.get("display_address"));
				//System.out.println(DisplayLocation);
				
				String CategoryName = String.valueOf(categories.get(0).get("title")); // JUST GET THE FIRST TITLE
				//System.out.println(CategoryName);
				
				String INSERT1 = "INSERT INTO Restaurant(restaurant_id, restaurant_name, details_id, rating_id, category_id) VALUES (?,?,?,?,?)";
				String INSERT2 = "INSERT INTO Restaurant_Details(details_id, image_url, address, phone_no, estimated_price, yelp_url) VALUES (?,?,?,?,?,?)";
				String INSERT3 = "INSERT INTO Category(category_id, category_name) VALUES (?,?)";
				String INSERT4 = "INSERT INTO Rating_Details(rating_id, review_count, rating) VALUES (?,?,?)";
				
				// TODO iterate the businessHelper array and insert every business into the DB
				
				PreparedStatement ps;
				// Populate Restaurant Details Table
				ps = conn.prepareStatement(INSERT2);
				ps.setString(1, String.valueOf(i+1));
				ps.setString(2, image_url);
				ps.setString(3, DisplayLocation);
				ps.setString(4, phone);
				ps.setString(5, price);
				ps.setString(6, url);
				ps.executeUpdate();			
				
				//Populate Categories Table
				ps = conn.prepareStatement(INSERT3);
				ps.setString(1, String.valueOf(i+1));
				ps.setString(2, CategoryName);
				ps.executeUpdate();	
				
				// Populate Rating_Detail
				ps = conn.prepareStatement(INSERT4);
				ps.setString(1, String.valueOf(i+1));
				ps.setString(2, String.valueOf(reviewCount));
				ps.setString(3, String.valueOf(rating));
				ps.executeUpdate();	
			
				// Insert into Database (SQL JDBC)
				ps = conn.prepareStatement(INSERT1);
				ps.setString(1, id);
				ps.setString(2, name);
				ps.setString(3, String.valueOf(i+1));
				ps.setString(4, String.valueOf(i+1));
				ps.setString(5, String.valueOf(i+1));
				ps.executeUpdate();
			} 
		} 
		catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public static Business getBusiness(String id) {
		try {
			Class.forName("com.mysql.jdbc.Driver");

		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		// TODO return business based on id
		String Query = "SELECT restaurant_id FROM Restaurant WHERE restaurant_id = " + "\"" + id + "\"" ;
		
		return null;
	}

	/**
	 * @param keyWord    the search keyword
	 * @param sort       the sort option (price, review count, rating)
	 * @param searchType search in category or name
	 * @return the list of business matching the criteria
	 */
	public static ArrayList<Business> getBusinesses(String keyWord, String sort, String searchType) {
		ArrayList<Business> busisnesses = new ArrayList<Business>();
		try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		String db = "jdbc:mysql://localhost/PA2PBKIM";
		String user = "root";
		String pwd = "root";
		// TODO get list of business based on the param
		String Query = "";
		String Query2 = "";
		Connection conn;
		try {
			conn = DriverManager.getConnection(db, user, pwd);
			if (searchType == "Name") {
				// Query for Name
				Query = "SELECT * from Restaurant WHERE restaurant_name= " + "\"" + keyWord + "\"" ;
				Statement st1 = conn.createStatement();
				ResultSet rs1 = st1.executeQuery(Query);
				int number = rs1.getInt("details_id");
				String id = String.valueOf(number);
				Query2 = "SELECT * FROM Restaurant, Rating_Details, Category, Restaurant_Details WHERE Restaurant_Details.details_id = " + "\"" + id + "\"" + " AND Rating_Details.rating_id = " + "\"" + id + "\"" + " AND Category.category_id = " + "\"" + id + "\"";
				if (rs1.next()) { // Means Existed
					// Unfinished
					//Business temp = new Business(rs1.getString("restaurant_id"), rs1.getString("alias"), rs1.getString("restaurant_name"), rs1.getString("image_url"), ready, rs1.getString("yelp_url"), rs1.getInt("review_count"), rs1.getArray("")), 0, null, null, Query, null, Query, Query, 0);
				}
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return busisnesses;

	}
}

//Code adapted from https://stackoverflow.com/questions/23070298/get-nested-json-object-with-gson-using-retrofit
class BusinessDeserializer implements JsonDeserializer<Business> {
	@Override
	public Business deserialize(JsonElement je, Type type, JsonDeserializationContext jdc)
			throws JsonParseException {
		JsonElement content = je.getAsJsonObject();
		
		// Holds Json File in an Array
		HashMap<String, Object> businessArray = new Gson().fromJson(content, HashMap.class);		
		return new Gson().fromJson(content, Business.class);
	}
}