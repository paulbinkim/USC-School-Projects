<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
	<title>Form</title>
</head>
<body>
   <div style="color:purple">
			<% String er = (String)request.getAttribute("error");
			if (er != null) {
				out.println(er);
			}
			%>
	</div>
	
     <form action = "FirstServlet" method = "GET">
     
       <label for="fname">First name:</label> <!-- Text -->
	<input type = "text" name = "first_name" /> <br />
	
	<label for="lname">Last name:</label>
       <input type = "text" name = "last_name" /> <br /><br />
       
       <label for="email">Email:</label> <!-- Email. -->
	<input type = "email" id="email" name = "email" /> <br />
	
	<label for="background">Background Information:</label> <!-- Text Area. -->
	<textarea id="background" name="background" rows="5" cols="40">I am a current Sophomore...</textarea>
	
	<p>Grade</p> <!-- Select Box. -->
	<select name="Grade" id="Grade">
    <option value="">--Please choose an option--</option>
    <option value="Freshman">Freshman</option>
    <option value="Sophomore">Sophomore</option>
    <option value="Junior">Junior</option>
    <option value="Senior">Senior</option>
	</select>
	
	<p>Please select your age:</p> <!-- Radio -->
	  <input type="radio" id="age1" name="age" value="1-30">
	  <label for="age1">0 - 30</label><br>
	  <input type="radio" id="age2" name="age" value="31-60">
	  <label for="age2">31 - 60</label><br>  
	  <input type="radio" id="age3" name="age" value="61-100">
	  <label for="age3">61 - 100</label><br>
	  
	  <label for="start">Start month:</label> <!-- Month. -->
		<input type="month" id="start" name="start"
		       min="2021-01" value="2022-02">
		       
	<div> 
		<label for="Confidence">Confidence Level:</label> <!-- Range. -->
	  <input type="range" id="Confidence" name="Confidence"
	         min="0" max="5">
	</div>
	
	<input type = "submit" value = "Submit" /> <!-- Submit -->
	<input type="reset"> <!-- Reset -->
	
     </form>
</body>
</html>



