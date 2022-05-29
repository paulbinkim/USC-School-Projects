<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <meta name="google-signin-client_id" content="781478761130-91a5gnruq0k6to9v44938rdbolmoqdct.apps.googleusercontent.com">
    <script src="https://apis.google.com/js/platform.js" async defer></script>
    <script src="https://kit.fontawesome.com/4b6d728af0.js"></script>
    <script type="text/javascript" src="js/google-login.js"></script>
    <link rel="stylesheet" href="css/style.css">
    <title>SalEats</title>
  </head>
  <body>
  	<header>
  		<nav>
  			<a href="home.jsp" class="no-style" id="logo">SalEats!</a>
  			<span id="buttons">
	  			<a href="home.jsp" class="no-style" id="home">Home</a>
	  			<a href="login.jsp" class="no-style">Login / Register</a>
	  			<%
	  				if (null != request.getSession().getAttribute("name")) {
	  					response.sendRedirect("home.jsp");
			   		}
			  	%>
  			</span>
  		</nav>
  	</header>
  	<main>
  		<div class="login-form-container">
  			<div>
	  			<form class="login-form" action="auth" method="POST">
	  				<div>
		  				<h1 class="form-header">Login</h1>
			  			<%
						    if (null != request.getAttribute("loginError")) {
						        out.println(request.getAttribute("loginError"));
						    } else {
						    	out.println("<p class=\"error-message\" style=\"visibility: hidden;\">invisible</p>");
						    }
						%>
		  			</div>
	  				<label>Email</label>
	  				<input type="email" class="textbox" name="email" required>
	  				<label>Password</label>
	  				<input type="password" class="textbox" name="password" autoComplete="current-password" required pattern="\S(.*\S)?">
	  				<button type="submit" name="login" class="login-button"><i class="fas fa-sign-in-alt"></i>Sign In</button>
	  			</form>
	  			<p id="divider"></p>
				<div class="g-signin2" data-onsuccess="onSignIn" data-width="425" data-height="40" data-longtitle="true" data-theme="dark"></div>
  			</div>
  			<form class="login-form" action="auth" method="POST">
	  				<div>
		  				<h1 class="form-header">Register</h1>
			  			<%
						    if (null != request.getAttribute("registerError")) {
						    	out.println(request.getAttribute("registerError"));
						    } else {
						    	out.println("<p class=\"error-message\" style=\"visibility: hidden;\">invisible</p>");
						    }
						%>
		  			</div>
  				<label>Email</label>
  				<input type="text" class="textbox" name="email" required>
  				<label>Name</label>
  				<input type="text" class="textbox" name="name" required pattern="\S(.*\S)?">
  				<label>Password</label>
  				<input type="password" class="textbox" name="password" autoComplete="new-password" required pattern="\S(.*\S)?">
  				<label>Confirm Password</label>
  				<input type="password" class="textbox" name="confirm_pass" autoComplete="new-password" required pattern="\S(.*\S)?">
  				<div>
	  				<label class="terms">
	  					<input type="checkbox" name="terms" class="terms" required>
	  					I have read and agree to all terms and conditions of SalEats.
	  				</label>
  				</div>
  				<button type="submit" name="register" class="login-button"><i class="fas fa-user-plus"></i>Create Account</button>
  			</form>
  		</div>
  	</main>
  	<footer>
  		<p>&copy; 2021 All Rights Reserved.</p>
  	</footer>
  </body>
</html>