Paul Kim, pbkim@usc.edu, 1723717002, Spring 2022 ITP 216

Final Project Details: Uber and Lyft Dataset Boston, MA

     The data set I propose to use for the Final Project for ITP 216, is data about Uber and Lyft trips in Boston, MA.
     I attached appropriate links below, and to sum, I plan on doing something very similar to the "idea" link where I will analyze
     Uber/Lyft Trips in Boston, to provide a graphical representations of the number of trips in a given day, using a CSV file.
     Problems I may run into is that most Uber/Lyft rides and its data are private (These companies will never be 
     willing to share their data to competitors for public use). As a result, the dataset I attached from Kaggle only 
     uses limited information from the scope 11/26/2018-12/18/2018 that is publicly provided, but it still has thousands of data points
     to analyze using Pandas.

     Links:
         Dataset Provided By:
         https://www.kaggle.com/datasets/brllrb/uber-and-lyft-dataset-boston-ma?select=rideshare_kaggle.csv,
         Idea Provided By:
         https://thecleverprogrammer.com/2021/04/21/uber-trips-analysis-using-python/
     
    *Requirement:
         Dataset must contain at least 1000 data-points. (Good)
         At least half of the data must be numeric. (Analzying Date and Trips, however, most data is numeric)

    Grading:
        Functionality and User Interfaces
            1.) The root endpoint displays an input section for client-supplied data. (Good)
                - Rather than asking for a "string" input of either Uber or Lyft (easily could've done this), I thought 
                    it would be more nicer and more convenient to create images that are clickable and redirects using
                    POST methods to go to its specific pages. 
                - I also have an input section for "Name" and "Personalized Message" that displays on User input.
            2.) Client shall be able to select a query of existing data, or a prediction based on existing data. (Good)
                - Choice to either look at Uber/Lyft, that provides a query of existing data.
                - This definition was a little vague, but the user has a choice to analyze the two companies.
            3.) Clients are able to submit query information, generating a POST Request. (Good)
                - A click on the Logos generate a POST request. (x2)
                - Query information generates a POST request.
            4.) Clients are able to see queried information on returned pages. (Good)
                - A click redirects to returned pages, that have queried information using Matplot.
        4/4 Points

        General Code
            1.) Code shall contain no global objects other than those provided. (Good)
                - I don't use global objects in the code, other than an image folder that is used to store
                    the Lyft/Uber Logo, Background Image, and MatplotLib Images.
                - https://stackoverflow.com/questions/50728328/python-how-to-show-matplotlib-in-flask  
                    - Matplot images need to be saved before rendered by the HTML and the method attached is a way to work
                        around the problem.
            2.) Functions only contain code related to the view function itself. (Good)
                - I seperate all code into its own function depending on its functionality.
        2/2 Points

        Web App
            1.) Flask shall be used to create the Web Framework routing using endpoints and view functions. (Good)
                - Used Flask for Web App.
            2.) The web app shall query and manipulate the dataset. (Good)
                - Queries and manipulates CSV file using PANDAS (Pre-Processed).
                    - Attached Methods
            3.) Web app contains at least 2 GET Endpoints (1/2)
                - Used 2 GET Endpoints for "Name" and "Personalized Message" Input Fields
                - I do not have a Dynamic Get (-1 Point). 
                    - What I can do is that I can allow User input to choose date ranges given the graph.
            4.) Web App Contains at least 2 POST Endpoints (2 points)
                - Homepage -> Uber/Lyft Redirect
                - Uber/Lyft -> Homepage Redirect
        5/6 Points

        Scientific Computation
            1.) Pandas shall be used for maniupatlion of the Data. (Good)
            2.) The app calculates some sort of meaningful aggregation. (Good)
                - Given the the dataset with 100000+ Data, I aggregate the number of Lyft/Uber rides on the given day. 
        2/2 Points

        Data Visualization
            1.) Matplotlib is used to visualize the data. (Good)
            2.) Figures have a title. (Good)
            3.) Plot Axes Shall be Labeled. (Good)
            4.) Plots shall contain a legend, and datasets plotted shall be named in the legend. (Good)
            5.) Plot axes have values clearly visible. (Good)
            6.) A distinction is made for plots that represent existing data, or predictive data. (Good)
                - I clearly display (Non-ML)
        6/6 Points

        Documentation and Formatting
            1.) Consise and useful commenting. (Good)
            2.) Descriptions of major sections in code. (Good)
            3.) Code is generally clear and readable. (Good)
        3/3 Points

        Error Handling
            1.) The web app runs with no errors. (Good)
                - Runs perfectly on my end. Please email me at pbkim@usc.edu if it does not.
            2.) The web app reroutes appropriately when given a nonsensical request. (Good)
                - I don't think I have any cases where I would run into this issue.
                - The only case where I would run into this is in my homepage for name and personalized message
                    however, I designed the functionality/design such that it is OK if the user does not enter anything
                    in these fields.
        2/2 Points

        Extra Points
        +3

        Total Points: 27/30

        * Skipped ML (0/2), 
        * Skipped Database 
        (Time Restraints, Sorry!)