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
  		<h1 id="results-header"><%= request.getAttribute("search")%></h1>
  		<div id="results-container">
  			<div class="result" id="detail">
				<a href="${restaurant.url}" target="_blank">
					<img src="${restaurant.image_url}" alt="Image of ${restaurant.name}" id="yelp-image">
				</a>
				<div class="result-info">
					<p>Address: ${restaurant.location}</p>
					<p>${restaurant.phone}</p>
					<p>Categories: 
						<c:forEach var="category" items="${restaurant.categories}" varStatus="loop">
							${category.title}<c:if test="${!loop.last}">, </c:if>
						</c:forEach>
					</p>
					<p>Price: ${restaurant.price}</p>
					<p>Rating: 
						<c:forEach begin="0" end="${restaurant.rating}" varStatus="loop">&#9733; </c:forEach> 
					</p>
				</div>
			</div>
			<form action="favorites" method="POST">
				<input type="hidden" name="id" value="${restaurant.id}">
				<%
		  			if (null != request.getSession().getAttribute("name")) {
		  				if (null != request.getAttribute("isFavorited")) {
		  					out.println();
					        out.println("<button type=\"submit\" class=\"favorite-button\" id=\"unfavorite\">");
					        out.println("<i class=\"fas fa-minus-circle\"></i> Remove from Favorites");
					        out.println("</button>");
		  				} else {
		  					out.println("<input type=\"hidden\" name=\"add\" value=\"true\">");
					        out.println("<button type=\"submit\" class=\"favorite-button\">");
					        out.println("<i class=\"fas fa-star\"></i> Add to Favorites");
					        out.println("</button>");
		  				}
				   	}
				%>
			</form>
		</div>
  	</main>
  	<footer>
  		<p>&copy; 2021 All Rights Reserved.</p>
  	</footer>
  </body>
</html>