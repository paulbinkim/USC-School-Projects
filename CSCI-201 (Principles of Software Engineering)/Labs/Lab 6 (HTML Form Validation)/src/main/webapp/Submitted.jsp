<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<style>
table, th, td {
  border:1px solid black;
}
</style>
<head>
<meta charset="ISO-8859-1">
<title>Submitted Form</title>
</head>
<body>
<body>
      <h1>Submitted Data</h1>
      <table style="width:100%">
		  <tr>
		    <th>Name</th>
		    <th>Email</th>
		    <th>Background Information</th>
		    <th>Grade</th>
		    <th>Age</th>
		    <th>Start</th>
		    <th>Confidence</th>
		  </tr>
		  <tr>
		    <td><%= request.getParameter("first_name")%> <%= request.getParameter("last_name")%></td>
		    <td><%= request.getParameter("email")%></td>
		    <td><%= request.getParameter("background")%></td>
		    <td><%= request.getParameter("Grade")%></td>
		    <td><%= request.getParameter("age")%></td>
		    <td><%= request.getParameter("start")%></td>
		    <td><%= request.getParameter("Confidence")%></td>
		  </tr>
		</table>
      	
</body>
</html>