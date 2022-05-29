# Paul Kim, Spring 2022, ITP 216, pbkim@usc.edu, Final Project Engine

# Import Useful Libraries
from flask import Flask, redirect, render_template, request, session, url_for
import os
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import datetime as dt
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.neural_network import MLPClassifier
import sqlite3 as sl

"""
Details:

Data Analysis and Visualization for extracting useful information and making decisions.
Create a web app which manipulates and visualizes a Big Data dataset.
*Use Flask, Pandas, Scikit-Learn, and Matplot Lib.

Big Data:
- Lyft and Uber dataset from Boston, MA
- 1000+ Datapoint
- Mostly numerical data.
- Stored as CSV

Endpoints:
- At least 2 endpoints used for GET requests.
- At least 1 of these should be dynamic created from a client POST request.
- At least 2 endpoints used for POST requests.

Scientific Computation:
- Do some sort of computation with the Big Data dataset.
- Needs to compute something meaningful.

Machine Learning:
- Make predictions based on the given Big Data dataset. (Use ML to make predictions)
- Predictions of how a particular property will change over time.

Data Visualization:
- At least 1 plot should visualize the data without any ML processing.
- At least 1 plot should visualize the ML-processed prediction.
"""

# Initialize Tools
app = Flask(__name__)

# Methods used to use images when using Flask Application
# https://stackoverflow.com/questions/46785507/python-flask-display-image-on-a-html-page
UberImage = os.path.join('static', 'images')
app.config['Images'] = UberImage


# Completed
# (Home Page) App Route
@app.route("/")
def home():
    # This method is the get the Images when using a Flask Application
    uber = os.path.join(app.config['Images'], 'uberimg.jpeg')
    lyft = os.path.join(app.config['Images'], 'lyft.png')
    backgroundImage = os.path.join(app.config['Images'], 'background.jpeg')
    # If user inputs a name and/or personalized message.
    if session.get("logged_in"):
        return render_template("Homepage.html", uberimage=uber, lyftimage=lyft, background=backgroundImage,
                               message=session["name"], message1=session["message"])
    return render_template("Homepage.html", uberimage=uber, lyftimage=lyft, background=backgroundImage)


# Completed
# Uber Action (Redirect to Uber Page from a POST request)
@app.route("/Uber", methods=["POST", "GET"])
def Uber():
    if request.method == "POST":
        uber = os.path.join(app.config['Images'], 'uberimg.jpeg')
        uberGraph = os.path.join(app.config['Images'], 'UberGraph.jpg')
        if session.get("logged_in"):
            return render_template("Uber.html", uberimage=uber, uberGraph=uberGraph, message=session["name"], message1=session["message"])
        return render_template("Uber.html", uberimage=uber, uberGraph=uberGraph)


# Completed
# Lyft Function (Redirect to Lyft Page from a POST request)
@app.route("/Lyft", methods=["POST", "GET"])
def Lyft():
    if request.method == 'POST':
        lyft = os.path.join(app.config['Images'], 'lyft.png')
        lyftGraph = os.path.join(app.config['Images'], 'LyftGraph.jpg')
        if session.get("logged_in"):
            return render_template("Lyft.html", lyftimage=lyft, lyftGraph=lyftGraph, message=session["name"], message1=session["message"])
        return render_template("Lyft.html", lyftimage=lyft, lyftGraph=lyftGraph)


# Completed
# Return to Home Function (Redirect to Homepage from Uber/Lyft Page from a POST Request)
@app.route("/ReturnHome", methods=["POST", "GET"])
def ReturnHome():
    if request.method == 'POST':
        uber = os.path.join(app.config['Images'], 'uberimg.jpeg')
        lyft = os.path.join(app.config['Images'], 'lyft.png')
        backgroundImage = os.path.join(app.config['Images'], 'background.jpeg')
        if session.get("logged_in"):
            return render_template("Homepage.html", uberimage=uber, lyftimage=lyft, background=backgroundImage,
                                   message=session["name"], message1=session["message"])
        return render_template("Homepage.html", uberimage=uber, lyftimage=lyft, background=backgroundImage)


# Completed
# Function that takes in the input from homepage, and saves the values into sessions
# Redirects to homepage.
@app.route("/ProvideUsername", methods=["POST", "GET"])
def HelloUser():
    if request.method == "POST":
        name = request.form["username"]  # Get the name of user (input)
        message = request.form["message"]
        session["name"] = name
        session["message"] = message
        session["logged_in"] = True  # There is no input validation needed here so this is fine.
    return redirect(url_for("home"))


# Methods that are not used, but included to show how I generated the Uber and Lyft Graphs using Pandas and Matplot

# Function that is used to Generate General Uber Graph
def GenerateUberGraph():
    # Method that Prints Uber Graph

    # Read CSV
    df = pd.read_csv("uber-lyftDataset.csv")

    # Validate Data (get rid of Null Values)
    dfValid = df[pd.notnull(df['cab_type'])]

    # Capture only Uber values
    dfValid = dfValid.loc[dfValid['cab_type'] == 'Uber']

    # Convert Date to just date, rather than date with times
    dfValid["datetime"] = pd.to_datetime(dfValid["datetime"]).dt.date

    # Get X Axis in dfX (dates), and the count of rides per date in dfValid
    dfX = dfValid['datetime'].sort_values().drop_duplicates()
    dfValid = dfValid['datetime'].value_counts().sort_index()

    # Matplot Methods
    plt.bar(dfX, dfValid, width=0.5, color="blue")
    plt.xticks(dfX, fontsize=5, rotation=35)
    plt.xlabel('Dates', fontsize=8, color="black")
    plt.ylabel("Number of Rides")
    plt.title("Uber Rides from 11/26/18 - 12/18/18")
    temp = ['Number of Rides']
    plt.legend(temp, loc=1)
    # plt.show()
    # Saving Figure to File
    plt.savefig('static/images/uberGraph.jpg')
    return


# Function that is used to Generate General Lyft Graph
def GenerateLyftGraph():
    # Method that Prints Lyft Graph

    # Read CSV
    df = pd.read_csv("uber-lyftDataset.csv")

    # Validate Data (get rid of Null Values)
    dfValid = df[pd.notnull(df['cab_type'])]

    # Capture only Lyft values
    dfValid = dfValid.loc[dfValid['cab_type'] == 'Lyft']

    # Convert Date to just date, rather than date with times
    dfValid["datetime"] = pd.to_datetime(dfValid["datetime"]).dt.date

    # Get X Axis in dfX (dates), and the count of rides per date in dfValid
    dfX = dfValid['datetime'].sort_values().drop_duplicates()
    dfValid = dfValid['datetime'].value_counts().sort_index()

    # Matplot Methods
    # Saving Figure to File
    plt.bar(dfX, dfValid, width=0.5, color="blue")
    plt.xticks(dfX, fontsize=5, rotation=35)
    plt.xlabel('Dates', fontsize=8, color="black")
    plt.ylabel("Number of Rides")
    plt.title("Lyft Rides from 11/26/18 - 12/18/18")
    temp = ['Number of Rides']
    plt.legend(temp, loc=1)
    # plt.show()
    plt.savefig('static/images/LyftGraph.jpg')
    return


# To-Do After Finals (No Time)
# # Method that uses ML to generate an Uber Prediction
# @app.route("/GenerateUberPrediction", methods=["POST", "GET"])
# def GenerateUberPrediction():
#     print()
#
#
# # Method that uses ML to generate a Lyft Prediction
# @app.route("/GenerateLyftPrediction", methods=["POST", "GET"])
# def GenerateLyftPrediction():
#     print()


# Completed
# Main Call that creates and runs Flask Application
if __name__ == "__main__":
    app.secret_key = os.urandom(12)
    # app.run(debug=True)
    app.run(host=os.getenv('IP', '0.0.0.0'),
            port=int(os.getenv('PORT', 4444)),
            debug=True)

# Fully Functional on my end
# If it doesn't work, please email me at pbkim@usc.edu
