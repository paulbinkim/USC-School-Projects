# Paul Kim, Spring 2022, pbkim@usc.edu, HW 11 - Food, 1723717002, Tuesday 7PM Section

from flask import Flask, redirect, render_template, request, session, url_for
import os
import sqlite3 as sl

"""
Tasked with creating a user management web application allowing users to get and set their favorite food.
Interact and manipulate a backend database, as well as using templated html files for the frontend.

Presented with a login page 
    If correct user credentials are supplied (based on DB query) the appropriate user should 
    be displayed, which contains favorite foods. 
        Users can set a new favorite food based on a database mutation statement to the "userfoods" table
    
    If correct admin account logs in, a list of all users is displayed (userfoods) table
        The admin can remove users (database mutation to credentials and userfoods)
        The admin can add a new user (database mutation to credentials and userfoods)
        
    *If not credentials are supplied, the client is presented with the login page again.
    
* Can also log out.
    
    
<!-- When "username" == "admin" -->

Do not need to edit the HTML templates.
Manipulate the Database, so if you somehow corrupt it, can always re-download.

"""

app = Flask(__name__)
db = 'favouriteFoods.db'


# Completed (Home Dispatcher)
@app.route("/")
def home():
    if not session.get("logged_in"):  # Which means it is false
        if not session.get("message"):
            message1 = "Please login to continue"
        else:
            message1 = session.get("message")
        return render_template("login.html", message=message1)  # Repeat to login page
    # We know here that a login was successful
    temp = session["username"]

    if not session.get("messageAdmin"):
        message1 = "Welcome back."
    else:
        message1 = session.get("messageAdmin")

    if temp == "admin":
        userList = db_get_user_list()
        return render_template("admin.html", username=temp, message=message1,
                               result=userList)  # Go to admin page
    else:
        return render_template("user.html", username=temp, fav_food=db_get_food(temp))  # Go to user page


# Create User function that manipulates database
@app.route("/action/createuser", methods=["POST", "GET"])
def create_user():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        if username == "" or password == "":
            session["messageAdmin"] = "Invalid Username or Password"
            return redirect(url_for('home'))
        db_create_user(username, password)
        session["messageAdmin"] = "Welcome back."
    return redirect(url_for('home'))


# Remove User function that manipulates database
@app.route("/action/removeuser", methods=["POST", "GET"])
def remove_user():
    if request.method == "POST":
        conditional = request.form.get("username")
        if not conditional:
            session["messageAdmin"] = "Choose Radio Button for a User (if it exists)"
            return redirect(url_for('home'))
        username = request.form["username"]
        db_remove_user(username)
        session["messageAdmin"] = "Welcome back."
    return redirect(url_for('home'))


# Function that sets favorite food for user
@app.route("/action/setfood", methods=["POST", "GET"])
def set_food():
    if request.method == "POST":
        username = session["username"]
        food = request.form["set_fav_food"]
        db_set_food(username, food)
    return redirect(url_for('home'))


# Completed
# Login Action (Take Username and Password from HTML, check if username exists in database)
@app.route("/login", methods=["POST", "GET"])
def login():
    if request.method == "POST":
        username = request.form["username"]  # Get the username
        password = request.form["password"]  # Get the password
        if username == "" or password == "":
            session["logged_in"] = False
            session["message"] = "Invalid Arguments, Please Try Again"
            return redirect(url_for("home"))
        condition = db_check_creds(username, password)
        if condition is True:
            session["username"] = username
            session["logged_in"] = True
        else:
            session["logged_in"] = False
            session["message"] = "Invalid Username or Password"
    return redirect(url_for("home"))


# Completed
# Logout Function, removes all attributes
@app.route("/logout", methods=["POST", "GET"])
def logout():
    if request.method == 'POST':
        session['logged_in'] = False
        session.pop('username', None)
        session.pop('message', None)
        session.pop('messageAdmin', None)
    return redirect(url_for('home'))


# Completed
# Retrieves User List as Dictionary
def db_get_user_list():
    getList = "SELECT * FROM userfoods"
    conn = sl.connect(db)
    curs = conn.cursor()
    data = curs.execute(getList)
    Dict = {}
    for item in data:
        Dict[item[0]] = item[1]

    getUser = "SELECT * FROM credentials"
    conn = sl.connect(db)
    curs = conn.cursor()
    data = curs.execute(getUser)
    for item in data:
        print(item)

    return Dict


# Completed
# Creates/Inserts user into tables
def db_create_user(un, pw):
    createUser = "INSERT INTO credentials (username, password) values (?,?)"
    createUser2 = "INSERT INTO userfoods (username, food) values (?,?)"
    conn = sl.connect(db)
    curs = conn.cursor()

    # Add into credentials
    binding = (un, pw,)  # Stack Overflow Reference (for SQL binding problem)
    curs.execute(createUser, binding)

    # Add into userfoods
    binding = (un, "Nothing so far!",)
    curs.execute(createUser2, binding)
    conn.commit()
    conn.close()
    return


# Completed
# Removes user from tables
def db_remove_user(un):
    removeUser = "DELETE FROM credentials WHERE `username` = ?"
    removeUser2 = "DELETE FROM userfoods WHERE `username` = ?"
    conn = sl.connect(db)
    curs = conn.cursor()
    binding = (un,)  # Stack Overflow Reference (for SQL binding problem)
    curs.execute(removeUser, binding)
    curs.execute(removeUser2, binding)
    conn.commit()
    conn.close()
    return


# Completed
# Retrieves favorite food from user
def db_get_food(un):
    getFood = "SELECT food FROM userfoods WHERE `username` = ?"
    conn = sl.connect(db)
    curs = conn.cursor()
    binding = (un,)  # Stack Overflow Reference (for SQL binding problem)
    data = curs.execute(getFood, binding)
    food = ""
    for item in data:
        food = item
    return food[0]


# Completed
# Sets favorite food for user
def db_set_food(un, ff):
    setFood = "UPDATE userfoods SET `food` = ? WHERE `username` = ?"
    conn = sl.connect(db)
    curs = conn.cursor()
    binding = (ff, un)  # Stack Overflow Reference (for SQL binding problem)
    curs.execute(setFood, binding)
    conn.commit()
    conn.close()
    return


# Completed
# Check if password matches between user (official) and input.
def db_check_creds(un, pw):
    # "admin" and "passwords" @Piazza 183
    if un == "admin" and pw == "passwords":
        return True
    findUser = "SELECT password FROM credentials WHERE `username` = ?"
    conn = sl.connect(db)
    curs = conn.cursor()
    binding = (un,)  # Stack Overflow Reference (for SQL binding problem)
    validationPassword = curs.execute(findUser, binding)
    realPassword = ""
    for record in validationPassword:
        realPassword = record
    if realPassword == "":
        return False

    if realPassword[0] == pw:
        return True
    else:
        return False


# Completed
# Main Call
if __name__ == "__main__":
    app.secret_key = os.urandom(12)
    # app.run(debug=True)
    app.run(host=os.getenv('IP', '0.0.0.0'),
            port=int(os.getenv('PORT', 4444)),
            debug=True)

# Fully Functional on my end. Pass all grading checks. :)