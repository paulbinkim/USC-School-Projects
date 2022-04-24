<!-- Initializing -->
<%@ page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1" %>
<%@ page import = "java.io.*,java.util.*" %>
<%String temp;%>
<%String name = "";%>
<%Boolean UserLogged = false;%>

<!-- HTML -->
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8"> 
    <title>Home</title>
    
    <!-- Importing Lobster Font from Google Fonts and Style Sheet CSS-->
    <link rel="preconnect" href="https://fonts.googleapis.com"> 
	<link rel="preconnect" href="https://fonts.gstatic.com"> 
	<link href="https://fonts.googleapis.com/css2?family=Lobster&display=swap" rel="stylesheet">
	<link rel="stylesheet" href="style.css">
	<script src="https://kit.fontawesome.com/fc9e0b3bed.js" ></script> <!-- fa-search magnyfing glass -->
	
	<!-- Helps with web page format -->
    <meta name="viewport" content="width=device-width, initial-scale=1" /> 
    
    
    <!-- Checks if User is Registered -->
    <!-- Rubric way to implement solution is not specifically graded: Chose this way rather than using Cookies -->
	<%
		if (null != request.getSession().getAttribute("name")) { /*  */
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
				<a href="home.jsp" id="SalEatsLogo" class="NavFormat">SalEats!</a>
				<%
					if (UserLogged == true) {
	  					String nameBar = "Hi " + name + "!";
						out.println("<a class=\"Namebar\">" + nameBar + "</a>"); 
					}
				%>
				
				<div id="buttonlinks">
		  			<a href="home.jsp" id="home" class="NavFormat">Home</a>
		  			<% 
			  			if (UserLogged == true) {
			  				out.println("<a href=\"LogoutDispatcher\" class=\"NavFormat\">" + temp + "</a>");
						}
			  			else {
			  				out.println("<a href=\"auth.jsp\" class=\"NavFormat\">" + temp + "</a>");
			  			}
		  			%>
	  			</div>
	  			
			</nav>
		</header>
		
		<img src="images/banner.jpeg" height="480" width="93%" id="image"/> 
		
		<!-- Form -->
		<div class = "center">
			<form action="search.jsp" method="GET">
			
				<div class = "SearchBar">
					<select name = "option">
						<option value = "Name">Name</option>
						<option value = "Category">Category</option>
					</select>
					<input type="text" placeholder="Restaurant Name/Category" name="restaurant" size="80%" style="background-color:#BAE5FD;">
					<button type= "submit" value = "Submit" class="SubmitButton">
						<i class="fa-solid fa-magnifying-glass"></i>
					</button>
				</div>
				
				<div class = "RadioButtons">
					<!-- Radio Buttons are grouped by the same "name" attribute -->
					<input type="radio" id="Price" name="Sort" value="Price">
					<label for="Price">Price</label><br>
					<input type="radio" id="Rating" name="Sort" value="Rating">
					<label for="Rating">Rating</label><br>
					<input type="radio" id="ReviewCount" name="Sort" value="Review Count">
					<label for="Review Count">Review Count</label>
				</div>
				
			</form>
		</div>
		
	</body>
</html>
