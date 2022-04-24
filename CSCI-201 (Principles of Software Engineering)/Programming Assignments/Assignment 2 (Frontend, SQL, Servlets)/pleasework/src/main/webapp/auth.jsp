<!-- Iniitalize -->
<%@ page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1" %>
<%String Error = "arbitrary";%>

<!-- HTML -->
<!DOCTYPE html>
<html>
<head>
	<!-- API's and Style Sheets  -->
    <meta charset="UTF-8">
    <meta name="google-signin-client_id" content="189547254231-ok17s0v0cav9998imruslq5o9a88odof.apps.googleusercontent.com">
    <script src="https://apis.google.com/js/platform.js" async defer></script>
    <script>	
    	// Google Sign in Function (Referenced Stack Overflow and Cited)
    	function onSignIn(googleUser) {	
            /* console.log("I am clicked");    */
            var profile = googleUser.getBasicProfile();		  
			var name = profile.getName();
			var email = profile.getEmail();
			
			var auth2 = gapi.auth2.getAuthInstance();
			auth2.disconnect();
			
			gapi.auth2.getAuthInstance().disconnect(); // Someone said to do this on Stack (idk if this does anything)
			googleUser.disconnect(); // One of these
            
            console.log('ID: ' + profile.getId()); // Do not send to your backend! Use an ID token instead.
			console.log('Name: ' + name);
			console.log('Email: ' + email); // This is null if the 'email' scope is not present.
			
			// Create a Dynamic Form (referenced online source cited below) using DOM
			//https://stackoverflow.com/questions/34127450/dynamically-add-forminput-textbox-in-jsp)
			//https://www.geeksforgeeks.org/how-to-create-a-form-dynamically-with-the-javascript/
			
			var form1 = document.createElement("form");
			form1.setAttribute("action", "LoginDispatcher");
		    form1.setAttribute("method", "GET")
		    
		    var input1 = document.createElement("input");
			input1.setAttribute("type", "text");
			input1.setAttribute("name", "GoogleName");
			input1.setAttribute("value", name);
			form1.appendChild(input1);
			
			var input2 = document.createElement("input");
			input2.setAttribute("type", "email");
			input2.setAttribute("name", "GoogleEmail");
			input2.setAttribute("value", email);
			form1.appendChild(input2);
			
			document.body.appendChild(form1);
			form1.submit();	
          }

	</script>
    
    <title>Login / Register</title>
    
    <link href="https://fonts.googleapis.com" rel="preconnect">
    <link href="https://fonts.gstatic.com" rel="preconnect">
    <link href="https://fonts.googleapis.com/css2?family=Lobster&family=Roboto:wght@300&display=swap" rel="stylesheet">
    <script src="https://kit.fontawesome.com/3204349982.js"></script> 
    <link href="https://fonts.googleapis.com/css?family=Roboto" rel="stylesheet" type="text/css">
    <link rel="stylesheet" href="style.css" >
	<!-- Format -->
    <meta name="viewport" content="width=device-width, initial-scale=1" /> 
    

    <style>
    .Login {	
    	/* border: 1px solid black; */
	   	width: 50%;
	   	float: left;
	   	padding: 20px;
	   	font-size: 13px;
    }
    .Register {
    	/* border: 1px solid black; */
    	width: 50%;
    	float: left;
    	padding: 20px;
    	font-size: 13px;
    }
    .CenterLogin {
    	display: flex;
    	padding: 100px;
   }
  	/*  Found this on Stack Overflow to center Google Button (Referenced) */
   	.g-signin2{
	  width: 100%;
	}
	.g-signin2 > div{
	  margin: 0 auto;
	}
   	.authButton {
   		background-color: #DF0000;
		color: white;
		height: 30px;
		width: 100%;
		border: none;
		border-radius: 3px;
		cursor: pointer;
		font-size: 16px;
   	}
    input[type=email], input[type=text], input[type=password] {
    	width: 100%;
		padding: 4px 4px;
		margin: 6px 0;
		display: inline-block;
		border: 0.5px solid black;
		border-radius: 4px;
		box-sizing: border-box;
   	}
   	#termsandConditions {
		font-size: small;
   	}
   	#box {
   		margin-top: 20px;
   		margin-bottom: 20px;
   	}
   	.ErrorBanner {
   		position: static;
   		background-color: pink;
   		width: 100%;
   		margin: 0;
   		padding: 0;
   		height: 60px;
   		display: flex;
	   	justify-content: center;
	   	align-items: center;
	   	font-size:12px;
	   	text-decoration: none;
   		color: grey;
   	}
    </style>
        
    <%
    	// For Red Error Bar On Top
		if (request.getSession().getAttribute("error") == null) {
			Error = "";
		}
		else if (request.getSession().getAttribute("error") == "someError"){
			Error = "Invalid email, password, bad Google login, or unregistered user. Please try again.";
			if ((String)session.getAttribute("name") != null) {
				session.removeAttribute("name");
				session.removeAttribute("email");
				session.removeAttribute("password");
			}
		}
		else if (request.getSession().getAttribute("error") == "Duplicate"){
			Error = "User Email Already Exists";
			if ((String)session.getAttribute("name") != null) {
				session.removeAttribute("name");
				session.removeAttribute("email");
				session.removeAttribute("password");
			}
		}
		else if (request.getSession().getAttribute("error") == "SQL") {
			Error = "SQL Error.";
			if ((String)session.getAttribute("name") != null) {
				session.removeAttribute("name");
				session.removeAttribute("email");
				session.removeAttribute("password");
			}
		}
		else if (request.getSession().getAttribute("error") == "passwordError"){
			Error = "Passwords do not match. Please try again.";
			if ((String)session.getAttribute("name") != null) {
				session.removeAttribute("name");
				session.removeAttribute("email");
				session.removeAttribute("password");
			}
		}
	%>
	

</head>
	<body>
			
		<header>
		
		<%
			if (Error != "") {
				out.println("<a class=\"ErrorBanner\">" + Error + "</a>");
				request.getSession().removeAttribute("error");
			} 
		
		%>
			<nav class = "navBar">
				<a href="home.jsp" id="SalEatsLogo" class="NavFormat" >SalEats!</a>
				<span id="buttonlinks">
		  			<a href="home.jsp" id="home" class="NavFormat">Home</a>
		  			<a href="auth.jsp" id="login" class="NavFormat">Login / Register</a>	  	
	  			</span>
			</nav>
		</header>
		
		<div class = "CenterLogin">
	
			<div class = "Login">
				<form class="loginInput" action="LoginDispatcher" method="GET">
					<h2 class="header">Login</h2>	
					<label>Email</label>
					<input type="email" class="LoginInput" name="email" required>
					<label>Password</label>
					<input type="password" class="LoginInput" name="password" required>
					<button type="submit" name = "SignIn" class ="authButton"><i class="fa fa-sign-in"> Sign In</i></button>
				</form>
				
				<!-- Google Sign In Button has fixed width parameters (does allow us to style... tried my best to format) -->
				<!-- Simplest Solution I found on Stack... data-theme = dark -->
				<div class="g-signin2" data-onfailure="onFailure" data-onsuccess="onSignIn" data-width="200px" data-theme="dark" data-longtitle="true"></div>
			
			</div>
			
			<div class = "Register">
				<form class="registerInput" action="RegisterDispatcher" method="GET">
					<h2 class="header">Register</h2>

					<!-- VALIDATE INPUT -->
					<label>Email</label>
					<input type="email" class="LoginInput" name="email" required>
					<label>Name</label>
					<input type="text" class="LoginInput" name="name" required>
					<label>Password</label>
					<input type="password" class="LoginInput" name="password" required>
					<label>Confirm Password</label>
					<input type="password" class="LoginInput" name="confirmpassword" required>
					
					<div id = "box">
						<Label id="termsandConditions"> 
							<input type="checkbox" name="termsConditions" required> I have read and agree to all terms and conditions of SalEats.
						</Label>
					</div>
					
					<button type="submit" name = "Register" class ="authButton"><i class="fas fa-user-plus"> Create Account</i></button>
				</form>
			</div>
		</div>
		
	</body>
</html>