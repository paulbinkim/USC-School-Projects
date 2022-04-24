package Dispatchers;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import java.io.IOException;
import java.io.Serial;

/**
 *  Server Side implementation class LogoutDispatcher
 */
@WebServlet("/LogoutDispatcher")
public class LogoutDispatcher extends HttpServlet {
    @Serial
    private static final long serialVersionUID = 1L;

    /**
     * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse
     * response)
     */
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException {
        // TODO Remove userID cookie
    	
    	response.setContentType("text/html;charset=UTF-8");
    	HttpSession session = request.getSession();
    	if ((String)session.getAttribute("name") != null) {
    		session.removeAttribute("name");
    		session.removeAttribute("email");
    		session.removeAttribute("password");
    		request.getRequestDispatcher("home.jsp").forward(request, response);
    	}
    	// Manually Sign Out * Just IN CASE GOOGLE SIGN OUT DOESN'T WORK
    	//location.href = "https://accounts.google.com/Logout?&continue=http://localhost:8080/temp/home.jsp";
    }

    /**
     * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse
     * response)
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException {
        doGet(request, response);
    }
}