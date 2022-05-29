package servlets;

import java.io.IOException;

import data.Database;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import yelp.Restaurant;
import yelp.YelpAPIParser;

/**
 * Handles searching for restaurant details by Yelp ID.
 */
@WebServlet("/details")
public class DetailsServlet extends HttpServlet {

	private static final long serialVersionUID = 9089740197565786040L;
	private Database db;
	
	public void init() throws ServletException {
		db = new Database();
	}

	/**
	 * Request a search result from YelpAPI.
	 */
	public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String id = request.getParameter("id");
		
		// Validate that ID exists
		if (id == null || id.isBlank()) {
			request.getRequestDispatcher("/home.jsp").forward(request, response); 
			return;
		}
		
		// Get restaurant from ID
		Restaurant restaurant = YelpAPIParser.getRestaurant(id);
		request.setAttribute("search", restaurant.getName());	
		request.setAttribute("restaurant", restaurant);
		
		// Check if favorited
		if (db.isFavorited((String) request.getSession().getAttribute("email"), id)) {
			request.setAttribute("isFavorited", "true");
		}
		
		request.getRequestDispatcher("/details.jsp").forward(request, response);
	}
}
