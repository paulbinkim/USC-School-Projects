package Dispatchers;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;




import java.io.IOException;
import java.io.Serial;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

/**
 * Server implementation class LoginDispatcher
 * This server handles both requests whether it is login or Google
 */

@WebServlet("/LoginDispatcher")
public class LoginDispatcher extends HttpServlet {
    @Serial
    private static final long serialVersionUID = 1L;
    private static final String db = "jdbc:mysql://localhost/PA2PBKIM";
    String user = "root";
	String pwd = "root";

    /**
     * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse
     * response)
     *  GET method is the default method to pass information from browser to web server
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        //TODO
    	
    	try {
    		Class.forName("com.mysql.cj.jdbc.Driver");
		} 
    	catch (ClassNotFoundException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
    	
    	String EmailVALID = "^(?=.{1,64}@)[A-Za-z0-9_-]+(\\.[A-Za-z0-9_-]+)*@" 
    	        + "[^-][A-Za-z0-9-]+(\\.[A-Za-z0-9-]+)*(\\.[A-Za-z]{2,})$"; // Regex Pattern found on Stack Overflow
    	response.setContentType("text/html;charset=UTF-8");
    	HttpSession session = request.getSession();
    	
    	// If, Else because we only get to this page if we successfully click a button, and all the fields are required
    	
    	if (request.getParameter("GoogleEmail") != null) {
    		String email = request.getParameter("GoogleEmail");
    		String fullname = request.getParameter("GoogleName");
    		// Check if email already exists in Database
    		String INSERT = "INSERT INTO Users(email, fullname) VALUES (?,?)"; // (email, fullname)
    		//String CHECKEMAIL = "SELECT email FROM Users WHERE email =" + request.getParameter("GoogleEmail");
    		String CHECKREGISTERED = "SELECT email, password FROM Users WHERE email =" + "\"" + email + "\"";
    		
    		try (Connection conn = DriverManager.getConnection(db, user, pwd);
				Statement st1 = conn.createStatement();){
				ResultSet rs1 = st1.executeQuery(CHECKREGISTERED);
				// Need to Validate and Store their Emails
				if(rs1.next()) {
					if (rs1.getString("email") != null) { // Means email existed
						if (rs1.getString("password") == null) { // Registered Google Accounts stored no passwords (Prevent same account if registered with Google)
							session.setAttribute("name", request.getParameter("GoogleName"));
							session.setAttribute("email", request.getParameter("GoogleEmail"));	
							request.getRequestDispatcher("/home.jsp").forward(request, response);
						} // If there is a password, then the account was originially registered
						session.setAttribute("error", "someError");
						request.getRequestDispatcher("/auth.jsp").forward(request, response);
					}
				}
				else {
					PreparedStatement ps = conn.prepareStatement(INSERT);
					// This might be a bug because USERS TABLE HAS 3 PARAMETERS
					ps.setString(1, email);
					ps.setString(2, fullname);
					ps.executeUpdate();
					
					// Upon Successful Sign up, User should automatically be logged in and redirected
			    	// Redirect to Home Page, now logged in as a user.
			    	session.setAttribute("name", fullname);
					session.setAttribute("email", email);	
					request.getRequestDispatcher("/home.jsp").forward(request, response);
				}
	    	}
	    	catch (SQLException e) {
				System.out.println ("SQLException: " + e.getMessage());
				session.setAttribute("error", "SQL");
				request.getRequestDispatcher("/auth.jsp").forward(request, response);
			}
    		// Names of values from Google API
    		session.setAttribute("name", request.getParameter("GoogleName"));
    		session.setAttribute("email", request.getParameter("GoogleEmail"));
    		request.getRequestDispatcher("/home.jsp").forward(request, response);

    	}
    	else if (request.getParameter("SignIn") != null) {
    		String email = request.getParameter("email");
    		String password = request.getParameter("password");
    		String name = "";
    		boolean Error = false;
    		
    		
    		// Email Validation
    		if (email.matches(EmailVALID) == false) {
    			Error = true; // Some error exists in Email Format
    		}
    	
    		// VALIDATE in the SQL Database if User is Registered
    		String CHECKREGISTERED = "SELECT fullname, email, password FROM Users WHERE email ='" + email + "' AND password =" + password;
			try (Connection conn = DriverManager.getConnection(db, user, pwd);
				Statement st1 = conn.createStatement();){
				ResultSet rs1 = st1.executeQuery(CHECKREGISTERED);
				if (!rs1.next()) {
					Error = true;
				}
				else {
					name = rs1.getString("fullname");
					if (rs1.getString("email") != null) { // Means email existed
						if (rs1.getString("password") == null){
							Error = true;
						}
					}
					else {
						Error = true;
					}
				}
	    	}
	    	catch (SQLException e) {
				System.out.println ("SQLException: " + e.getMessage());
				session.setAttribute("error", "someError");
				request.getRequestDispatcher("/auth.jsp").forward(request, response);
			}
    		// If there is an INVALID attempt, display RED Border on top with error message and refresh the page
    		if (Error == true) {
    			session.setAttribute("error", "someError");
    			request.getRequestDispatcher("/auth.jsp").forward(request, response);
    		}
    		else {
    			// Set Session Attributes
        		session.setAttribute("name", name);
        		session.setAttribute("email", email);
        		
        		// Redirect to Home Page, now logged in as a user.
        		request.getRequestDispatcher("/home.jsp").forward(request, response);
    		}
    	}
    }

    /**
     * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse
     * response)
     *
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doGet(request, response);
    }
}

