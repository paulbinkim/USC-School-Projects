package data;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.SQLIntegrityConstraintViolationException;
import java.util.ArrayList;
import java.util.List;

import yelp.Restaurant;
import yelp.YelpAPIParser;

/**
 * Handles interacts with the MySQL database.
 * @author Thomas Peters
 */
public class Database {
	
	private static String DRIVER = "com.mysql.cj.jdbc.Driver";
	private static String ADDRESS = "jdbc:mysql://localhost:3306/sal_eats";
	private static String USER = "root";
	private static String PASSWORD = "password";
	
	/**
	 * Adds a user object to the authentication table
	 * @return Statement result integer.
	 */
	public int registerUser(User user) throws SQLIntegrityConstraintViolationException {
		String INSERT_USERS_SQL = "INSERT INTO users (email, name, password) VALUES (?, ?, ?)";
		int result = 0;
		try {
			// Connect to database
			Class.forName(DRIVER);
			Connection conn = DriverManager.getConnection(ADDRESS, USER, PASSWORD);
			
			// Insert new user to database
			PreparedStatement statement = conn.prepareStatement(INSERT_USERS_SQL);
			statement.setString(1, user.getEmail());
			statement.setString(2, user.getName());
			statement.setString(3, user.getPassword());
			result = statement.executeUpdate();
			conn.close();
		} catch (SQLException | ClassNotFoundException e) {
			if (e instanceof SQLIntegrityConstraintViolationException) {
				throw new SQLIntegrityConstraintViolationException();
			}
		}
		return result;
	}
	
	/**
	 * Validates a email and password pair for login.
	 * @return true if validated.
	 */
	public boolean validate(String email, String password) {
		String SELECT_USERS_SQL = "SELECT * FROM users WHERE email = ? AND password = ?";
		boolean status = false;
		try {
			// Connect to database
			Class.forName(DRIVER);
			Connection conn = DriverManager.getConnection(ADDRESS, USER, PASSWORD);
			
			// Check if email and password match 
			PreparedStatement statement = conn.prepareStatement(SELECT_USERS_SQL);
			statement.setString(1, email);
			statement.setString(2, password);
	
			ResultSet rs = statement.executeQuery();
			status = rs.next();
			conn.close();
		} catch (SQLException | ClassNotFoundException e) {
			e.printStackTrace();
		}
		return status;
	}
	
	/**
	 * Access the name associated with a specified email.
	 * @return Queried name or "Username" if null.
	 */
	public String getName(String email) {
		String SELECT_NAME_SQL = "SELECT name FROM users WHERE email = ?";
		String result = "User";
		try {
			// Connect to database
			Class.forName(DRIVER);
			Connection conn = DriverManager.getConnection(ADDRESS, USER, PASSWORD);
			
			// Grab queried name
			PreparedStatement statement = conn.prepareStatement(SELECT_NAME_SQL);
			statement.setString(1, email);
			ResultSet rs = statement.executeQuery();
			rs.next();
			result = rs.getString("name");
			conn.close();
		} catch (SQLException | ClassNotFoundException e) {
			e.printStackTrace();
		}
		return result;
	}
	
	/**
	 * Adds a restaurant ID to the favorites list.
	 * @return Statement result integer.
	 */
	public int addFavorite(String email, String restaurantID) {
		String INSERT_FAVORITE_SQL = "INSERT INTO favorites (email, restaurant) VALUES (?, ?)";
		int result = 0;
		try {
			// Connect to database
			Class.forName(DRIVER);
			Connection conn = DriverManager.getConnection(ADDRESS, USER, PASSWORD);
			
			// Insert new user to database
			PreparedStatement statement = conn.prepareStatement(INSERT_FAVORITE_SQL);
			statement.setString(1, email);
			statement.setString(2, restaurantID);
			result = statement.executeUpdate();
			conn.close();
		} catch (SQLException | ClassNotFoundException e) {
			e.printStackTrace();
		}
		return result;
	}
	
	/**
	 * Removes a restaurant ID from the favorites list.
	 * @return Statement result integer.
	 */
	public int removeFavorite(String email, String restaurantID) {
		String DELETE_FAVORITE_SQL = "DELETE FROM favorites WHERE email = ? AND restaurant = ?";
		int result = 0;
		try {
			// Connect to database
			Class.forName(DRIVER);
			Connection conn = DriverManager.getConnection(ADDRESS, USER, PASSWORD);
			
			// Insert new user to database
			PreparedStatement statement = conn.prepareStatement(DELETE_FAVORITE_SQL);
			statement.setString(1, email);
			statement.setString(2, restaurantID);
			result = statement.executeUpdate();
			conn.close();
		} catch (SQLException | ClassNotFoundException e) {
			e.printStackTrace();
		}
		return result;
	}
	
	/**
	 * Checks if restaurant is in favorites list
	 * @return true if restaurant ID is in favorite's list
	 */
	public boolean isFavorited(String email, String restaurantID) {
		String CHECK_FAVORITED_SQL = "SELECT * FROM favorites WHERE email = ? AND restaurant = ?";
		boolean status = false;
		try {
			// Connect to database
			Class.forName(DRIVER);
			Connection conn = DriverManager.getConnection(ADDRESS, USER, PASSWORD);
			
			// Check if email and password match 
			PreparedStatement statement = conn.prepareStatement(CHECK_FAVORITED_SQL);
			statement.setString(1, email);
			statement.setString(2, restaurantID);
	
			ResultSet rs = statement.executeQuery();
			status = rs.next();
			conn.close();
		} catch (SQLException | ClassNotFoundException e) {
			e.printStackTrace();
		}
		return status;
	}

	/**
	 * Access the list of favorites associated with a specified email.
	 * @return Queried list of favorite restaurants.
	 */
	public List<Restaurant> getFavorites(String email) {
		String SELECT_FAVORITES_SQL = "SELECT restaurant FROM favorites WHERE email = ? ORDER BY id DESC";
		List<Restaurant> favorites = new ArrayList<Restaurant>();
		try {
			// Connect to database
			Class.forName(DRIVER);
			Connection conn = DriverManager.getConnection(ADDRESS, USER, PASSWORD);
			
			// Grab queried name
			PreparedStatement statement = conn.prepareStatement(SELECT_FAVORITES_SQL);
			statement.setString(1, email);
			
			ResultSet rs = statement.executeQuery();
			while (rs.next()) {
				Restaurant restaurant = YelpAPIParser.getRestaurant(rs.getString("restaurant"));
				if (restaurant != null) {
					favorites.add(restaurant);
				}
			}
			conn.close();
		} catch (SQLException | ClassNotFoundException e) {
			e.printStackTrace();
		}
		return favorites;
	}
}
