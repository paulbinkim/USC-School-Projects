package servlets;

import java.io.IOException;
import java.util.List;

import data.Database;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import yelp.Restaurant;
import yelp.YelpAPIParser;

/**
 * Handles adding and removing restaurants to the favorites list.
 * @author Thomas Peters
 */
@WebServlet("/favorites")
public class FavoritesServlet extends HttpServlet {
	
	private static final long serialVersionUID = -2309693395591887433L;
	private Database db;
	
	public void init() throws ServletException {
		db = new Database();
	}
	
	public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		List<Restaurant> restaurants = db.getFavorites((String) request.getSession().getAttribute("email"));
		request.setAttribute("data", restaurants);
		request.getRequestDispatcher("/favorites.jsp").forward(request, response);
	}
	
	/**
	 * Adds a new restaurant to the favorites list
	 */
	public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String email = (String) request.getSession().getAttribute("email");
		String id = request.getParameter("id");
		
		// Validate that email and ID exists
		if (id == null || id.isBlank() || email == null || email.isBlank()) {
			request.getRequestDispatcher("/home.jsp").forward(request, response); 
			return;
		}
		
		if (null != request.getParameter("add")) {
			// Add ID to database
			db.addFavorite(email, id);
			request.setAttribute("isFavorited", "true");
		} else {
			// Remove ID from database
			db.removeFavorite(email, id);
		}
		
		// Get restaurant from ID
		Restaurant restaurant = YelpAPIParser.getRestaurant(id);
		request.setAttribute("search", restaurant.getName());	
		request.setAttribute("restaurant", restaurant);
		request.getRequestDispatcher("/details.jsp").forward(request, response);
	}
	
	/**
	 * Removes a restaurant from the favorites list
	 */
	public void doDelete(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

	}

}
