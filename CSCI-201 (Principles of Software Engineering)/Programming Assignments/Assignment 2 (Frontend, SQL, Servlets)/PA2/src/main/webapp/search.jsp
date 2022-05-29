<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <script src="https://kit.fontawesome.com/4b6d728af0.js"></script>
    <link rel="stylesheet" href="css/style.css">
    <title>SalEats</title>
  </head>
  <body>
  	<header>
  		<nav>
  			<a href="home.jsp" class="no-style" id="logo">SalEats!</a>
  			<span id="buttons">
	  			<a href="home.jsp" class="no-style" id="home">Home</a>
	  			<%
	  				if (null != request.getSession().getAttribute("name")) {
			        	out.println("<a href=\"favorites\" class=\"no-style\" id=\"favorites\">Favorites</a>");
			        	out.println("<a href=\"auth\" class=\"no-style\">Logout</a>");
			   		} else {
			        	out.println("<a href=\"login.jsp\" class=\"no-style\">Login / Register</a>");
			    	}
			  	%>
  			</span>
  		</nav>
  	</header>
  	<main>
  		<div>
	  		<form action="search" method="GET">
	  			<div class="form-container">
	  				<div class="column">
				  		<input type="text" placeholder="Restaurant Name" name="restaurant" class="textbox" required><br/>
				  		<input type="text" placeholder="Location" name="location" class="textbox" required>
			  		</div>
			  		<div class="column">
			  			<div>
				  			<button type="submit" id="search_button">
							    <i class="fas fa-search"></i>
							</button>
						</div>
						<div class="radio-buttons-container">
							<div>
					            <label class="radio-element">
					              <input type="radio" value="best_match" name="sort" checked="checked"/>
					              Best Match
					            </label>
					            <br/>
					            <label class="radio-element">
					              <input type="radio" value="rating" name="sort" />
					              Rating
					            </label>
					        </div>
				            <div>
					            <label class="radio-element">
					              <input type="radio" value="review_count" name="sort" />
					              Review Count
					            </label>
					            <br/>
					            <label class="radio-element">
					              <input type="radio" value="distance" name="sort" />
					              Distance
					            </label>
				            </div>
						</div>
					</div>
				</div>
	  		</form>
  		</div>
  		<h1 id="results-header">Results for <%= request.getAttribute("search")%></h1>
  		<div id="results-container">
			<c:forEach var="restaurant" items="${data}">
				<div class="result">
					<a href="details?id=${restaurant.id}">
						<img src="${restaurant.image_url}" alt="Image of ${restaurant.name}" id="yelp-image">
					</a>
					<div>
						<h2>${restaurant.name}</h2>
						<p>${restaurant.location}</p>
						<a href="${restaurant.url}" target="_blank" class="yelp-link" id="underline">Yelp Link</a>
					</div>
				</div>
			</c:forEach>
		</div>
  	</main>
  	<footer>
  		<p>&copy; 2021 All Rights Reserved.</p>
  	</footer>
  </body>
</html>