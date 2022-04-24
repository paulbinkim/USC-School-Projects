package Dispatchers;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import java.sql.*;

import java.io.IOException;
import java.io.Serial;

/**
 * Servlet implementation class RegisterDispatcher
 */
@WebServlet("/RegisterDispatcher")
public class RegisterDispatcher extends HttpServlet {
    @Serial
    private static final long serialVersionUID = 1L;
    String db = "jdbc:mysql://localhost/PA2PBKIM";
	String user = "root";
	String pwd = "root";
    /**
     * Default constructor.
     */
    public RegisterDispatcher() { 	
    }

    /**
     * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse
     * response)
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        //TODO
    	Connection conn = null;
    	
    	try {
			Class.forName("com.mysql.cj.jdbc.Driver");
		} 
    	catch (ClassNotFoundException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
    	
    	response.setContentType("text/html;charset=UTF-8");
    	HttpSession session = request.getSession();
    	
    	String password = request.getParameter("password");
    	String Checkpassword = request.getParameter("confirmpassword");
    	String email = request.getParameter("email");
    	
    	// Password Validation
    	if (!password.equals(Checkpassword)) { // Means passwords do not match
    		session.setAttribute("error", "passwordError");
			request.getRequestDispatcher("/auth.jsp").forward(request, response);
    	}
    	
    	String INSERT = "INSERT INTO Users(email, fullname, password) VALUES (?,?,?)"; // (email, fullname, password)
    	String CHECKEMAIL = "SELECT email FROM Users WHERE email = " + "\"" + email + "\"";
   
    	// JDBCTest4 Lecture Referenced
    	
    	// Want to Check if Email (unique) already exists in the database
    	// STEPS: 1, CHECK IF EMAIL EXISTS IN DATABASE
    	try {
    		conn = DriverManager.getConnection(db, user, pwd);
			Statement st1 = conn.createStatement();
			ResultSet rs1 = st1.executeQuery(CHECKEMAIL);
			if (rs1.next()) {
				session.setAttribute("error", "Duplicate");
				request.getRequestDispatcher("/auth.jsp").forward(request, response);
			}
			// Insert into Database (SQL JDBC)
			PreparedStatement ps = conn.prepareStatement(INSERT);
			ps.setString(1, request.getParameter("email"));
			ps.setString(2, request.getParameter("name"));
			ps.setString(3, request.getParameter("password"));
			System.out.println(ps);
			ps.executeUpdate();
			
			// Upon Successful Sign up, User should automatically be logged in and redirected
	    	// Redirect to Home Page, now logged in as a user.
			session.setAttribute("name", request.getParameter("name"));
			session.setAttribute("email", request.getParameter("email"));	
			request.getRequestDispatcher("/home.jsp").forward(request, response);
    	}
    	catch (SQLException e) {
			System.out.println ("SQLException1: " + e.getMessage());
			session.setAttribute("error", "SQL");
			request.getRequestDispatcher("/auth.jsp").forward(request, response);
		}	 
    }

    /**
     * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse
     * response)
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // TODO Auto-generated method stub
        doGet(request, response);
    }

}
