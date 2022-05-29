package servlets;

import java.io.IOException;
import java.util.List;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import yelp.Restaurant;
import yelp.YelpAPIParser;

/**
 * Handles searching for restaurants using YelpAPI queries.
 * @author Thomas Peters
 */
@WebServlet("/search")
public class SearchServlet extends HttpServlet {

	private static final long serialVersionUID = 3901610548642762613L;
	
	/**
	 * Request a search result from YelpAPI.
	 */
	public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String restaurant = request.getParameter("restaurant");
		String location = request.getParameter("location");
		String sort = request.getParameter("sort");
		
		// Validate that all fields are filled out
		if (restaurant.isBlank() | location.isBlank() | sort == null) {
			request.getRequestDispatcher("/home.jsp").forward(request, response); 
			return;
		}
		
		// Search for top 10 matching restaurants
		List<Restaurant> restaurants = YelpAPIParser.searchRestaurants(restaurant, location, sort);
		request.setAttribute("search", restaurant);
		request.setAttribute("data", restaurants);
		request.getRequestDispatcher("/search.jsp").forward(request, response);
	}
}
