
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.WebServlet;

@WebServlet("/FirstServlet")
public class FirstServlet extends HttpServlet {

   private String message;

   public void init() throws ServletException {
      // Do required initialization
      message = "Form Page";
   }

   public void doGet(HttpServletRequest request, HttpServletResponse response)
      throws ServletException, IOException {

      // Set response content type
      response.setContentType("text/html");
      
      

      // Actual logic goes here.
//      PrintWriter out = response.getWriter();
//      out.println("<h1>" + message + "</h1>");
      
      String error = "";

	String fna = request.getParameter("first_name");
	String lna = request.getParameter("last_name");
	
	String email = request.getParameter("email");
	String background = request.getParameter("background");
	String grade = request.getParameter("Grade");
	String age = request.getParameter("age");
	String start = request.getParameter("start");
	String confidence = request.getParameter("Confidence");
	
	if (fna.contentEquals("") || lna.contentEquals("")) {
		error += "<p>Name is missing!</p>";
	}
	if (email.contentEquals("")) {
		error +="<p>Email is missing!</p>";
	}
	if (background.contentEquals("")) {
		error += "<p>Background info is missing!</p>";
	}
	if (grade.contentEquals("")) {
		error += "<p>Grade is missing!</p>";
	}
	if (age == null) {
		error += "<p>Age is missing!</p>";
	}
	if (start.contentEquals("")) {
		error += "<p>Start data(month) is missing!</p>";
	}
	if (confidence.contentEquals("")) {
		error += "<p>Confidence Level is missing!</p>";
	}
	
	if (error.equals("")) {
		request.getRequestDispatcher("Submitted.jsp").forward(request, response);
	}
	else
		request.setAttribute("error", error);
		request.getRequestDispatcher("formpage.jsp").include(request, response);
   	}
   

   public void destroy() {
      // do nothing.
   }
}


