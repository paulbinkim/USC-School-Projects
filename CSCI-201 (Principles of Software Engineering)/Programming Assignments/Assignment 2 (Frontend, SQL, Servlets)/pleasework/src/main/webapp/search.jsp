<!-- Initialize -->
<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
         pageEncoding="ISO-8859-1" %>
<%String temp;%>
<%String name = "";%>
<%Boolean UserLogged = false;%>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Search</title>
    
    <!-- Helps with web page format -->
    <meta name="viewport" content="width=device-width, initial-scale=1" /> 
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link
            href="https://fonts.googleapis.com/css2?family=Lobster&family=Roboto:wght@300&display=swap"
            rel="stylesheet">
    <link rel="stylesheet" href="style.css">
    <script src="https://kit.fontawesome.com/3204349982.js"
            crossorigin="anonymous"></script>   
    <script src="https://kit.fontawesome.com/fc9e0b3bed.js" ></script> <!-- fa-search magnyfing glass --> 
    <%
		if (null != request.getSession().getAttribute("name")) { 
			temp = "Logout";
			name = String.valueOf(request.getSession().getAttribute("name"));
			UserLogged = true;
       	} 
		else if (request.getSession().getAttribute("error") != null) {
			temp = "Login / Register";
			UserLogged = false;
		}
		else {
			temp = "Login / Register";
			UserLogged = false;
   		}
	%>   
</head>
<body>
	<header>
		<nav class = "navBar">
			<a href="home.jsp" id="SalEatsLogo" class="NavFormat" >SalEats!</a>
			<%
				if (UserLogged == true) {
  					String nameBar = "Hi " + name + "!";
					out.println("<a class=\"Namebar\">" + nameBar + "</a>"); 
				}
			%>
			<span id="buttonlinks">
	  			<a href="home.jsp" id="home" class="NavFormat">Home</a>
	  				
	  			<%
	  				if (null != request.getSession().getAttribute("name")) {
			        	out.println("<a href=\"LogoutDispatcher\" class=\"NavFormat\" >Logout</a>");
			   		} 
	  				else {		
			        	out.println("<a href=\"auth.jsp\" class=\"NavFormat\">Login / Register</a>");
	  				}
			  	%>
			 
  			</span>
		</nav>
	</header>
	
	<!-- Form -->
	<div class = "center" style="margin-top: 20px;">
		<form action="SearchDispatcher" method="GET">
		
			<div class = "SearchBar">
				<select name = "option">
					<option value = "Name">Name</option>
					<option value = "Category">Category</option>
				</select>
				<input type="text" placeholder="Restaurant Name/Category" name="restaurant" size="100%" style="background-color:#BAE5FD;">
				<button type= "submit" value = "Submit" class="SubmitButton">
					<i class="fa-solid fa-magnifying-glass"></i>
				</button>
			</div>
			
			<div class = "RadioButtons" style="margin-top: 10px;">
				<input type="radio" id="Price" name="Sort" value="Price">
				<label for="Price">Price</label><br>
				<input type="radio" id="Rating" name="Sort" value="Rating">
				<label for="Rating">Rating</label><br>
				<input type="radio" id="ReviewCount" name="Sort" value="Review Count">
				<label for="javascript">Review Count</label>
			</div>
			
		</form>
	</div>
</body>
</html>