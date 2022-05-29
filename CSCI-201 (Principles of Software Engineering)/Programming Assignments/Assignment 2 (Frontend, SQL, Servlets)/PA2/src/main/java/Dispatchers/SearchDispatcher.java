package Dispatchers;

import javax.servlet.annotation.WebServlet;
import javax.servlet.ServletConfig;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import Util.Business;
import Util.RestaurantDataParser;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.Serial;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * Servlet implementation class SearchDispatcher
 */
@WebServlet("/SearchDispatcher")
public class SearchDispatcher extends HttpServlet {
    @Serial
    private static final long serialVersionUID = 1L;
    String db = "jdbc:mysql://localhost/PA2PBKIM";
	String user = "root";
	String pwd = "root";
	boolean parseddata = false;
    /**
     * Default constructor.
     */
    public SearchDispatcher() {
    }

    @Override
    public void init(ServletConfig config) throws ServletException {
        super.init(config);
        ServletContext servletContext = getServletContext();
        // TODO get json file as stream, Initialize FakeYelpAPI by calling its initalize
        //InputStream stream = servletContext.getResourceAsStream("restaurant_data.json");

        // method
    }

    /**
     * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse
     *      response)
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
        throws ServletException, IOException {
        // TODO
    	if (parseddata == false) {
    		String path = this.getServletContext().getRealPath("/WEB-INF/restaurant_data.json"); 
            RestaurantDataParser.Init(path);
    		parseddata = true;
    	}
    	try {
			Class.forName("com.mysql.cj.jdbc.Driver");
		} 
    	catch (ClassNotFoundException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
    	HttpSession session = request.getSession();
    	String Option = request.getParameter("option");
    	String Input = request.getParameter("restaurant");
    	String Radio = request.getParameter("Sort");
    	
    	// Input is a String, Radio is [Price, Rating, Review], Option is [Name, Category]
    	ArrayList<Business> sol = RestaurantDataParser.getBusinesses(Input, Radio, Option);
		request.setAttribute("data", sol);
		request.getRequestDispatcher("/home.jsp").forward(request, response); 	
    }

    /**
     * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse
     *      response)
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // TODO Auto-generated method stub
        doGet(request, response);
    }
}