<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
         pageEncoding="ISO-8859-1" %>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Details</title>
    <meta name="viewport" content="width=device-width, initial-scale=1" /> 
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Lobster&family=Roboto:wght@300&display=swap"
            rel="stylesheet">
    <script src="https://kit.fontawesome.com/3204349982.js" crossorigin="anonymous"></script>
    <link rel="stylesheet" href="style.css">
</head>

<body>

<header>
		<nav class = "navBar">
			<a href="home.jsp" id="SalEatsLogo" class="NavFormat" >SalEats!</a>
			<span id="buttonlinks">
	  			<a href="home.jsp" id="home" class="NavFormat">Home</a>
	  			
	  			
	  			
	  			<%
	  				if (null != request.getSession().getAttribute("name")) {
	  					
	  					
			        	out.println("<a href=\"auth\" class=\"NavFormat\" >Logout</a>");
			        	
			        	
			   		} 
	  				else {
	  					
	  					
			        	out.println("<a href=\"auth.jsp\" class=\"NavFormat\">Login / Register</a>");
			        	
			        	
			    	}
			  	%>
			  	
			  	
  			</span>
		</nav>
	</header>
	
	<!-- findData Form -->
	<div class = "center">
	<form action="findData" method="GET">
		<div class = "SearchBar">
			<select name = "option">
				<option value = "Name">Name</option>
				<option value = "Category">Category</option>
			</select>
			<input type="text" placeholder="Restaurant Name/Category" name="restaurant" size="50%" style="background-color:#c5f9fa;">
			<input type= "submit" value = "Submit" class="SubmitButton"/>
		</div>
		
		<div class = "RadioButtons">
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