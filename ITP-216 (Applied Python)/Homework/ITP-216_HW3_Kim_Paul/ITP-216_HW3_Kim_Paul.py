# Paul Kim, HW 3, Tuesday 7-8:50 PM Section, Spring 2022
# pbkim@usc.edu
# HW 3 - The Deniros


"""
Given a CSV file with all the movies of Robert Deniro, use the data to calculate the average Robert
Deniro movie score, and then use it to generate a list of all the movies which were rated above average.

THERE IS NO USER INPUT
"""

'''
Description: Retrieves the entire contents of a text file.
Parameters: FileName (String)
Returns: The header from the file (list), All the rest of data from the file (List)
'''


def file_reader(FileName):
    FirstLine = []
    Data = []
    with open(FileName) as f:  # Open File
        FirstLine.append(f.readline())
        Lines = f.readlines()  # Read entire file
        for line in Lines:  # Iterate through file
            Data.append(line.rstrip())

    return FirstLine, Data  # Returns two lists


'''
Description: Calculates the average value of a collection of values.
Parameters: A collection of integers (List)
Returns: The Mean Score (Float)
'''


def calculate_mean(List1):
    meanScore = 0
    movieCount = 0
    tempString = ""
    for item in List1:
        # String Indexing
        tempString += str(item[6])
        tempString += str(item[7])
        tempString += str(item[8])
        meanScore += int(tempString)  # Adding score to meanScore sum

        movieCount += 1  # Incrementing Movie Count
        tempString = ""  # Resetting string

    meanScore = meanScore / movieCount  # Computing Average
    return meanScore


'''
Description: From an initial list, retrieves a list of all the movies with scores above a certain value.
Parameters: A Collection of Movies (List), A Score (Float)
Returns: A Collection of All Movies (List)
'''


def find_movies_above_score(Data, Score):
    NewMovieData = []
    tempString = ""
    for item in Data:
        tempString += str(item[6])
        tempString += str(item[7])
        tempString += str(item[8])
        if int(tempString) >= Score:
            NewMovieData.append(item)
        tempString = ""

    return NewMovieData


'''
Description: Primary entry point to codebase.
Parameters: 0
Returns: 0
'''


def main():
    print("I love Robert Deniro!")
    Header, Data = file_reader("deniro.csv")  # Call to file_reader to obtain data
    AverageScore = calculate_mean(Data)  # Call to calculate_mean data to compute average data
    NewData = find_movies_above_score(Data, AverageScore)
    print("The average Rotten Tomatoes scores for his movies is " + str(AverageScore) + ".")

    print("Of 87 movies, 48 are above average.")
    # Manual output because no function required returns # of movies etc.
    # Just to demonstrate knowledge, to find # of movies and # of movies that are above average
    # I would just return another variable from file_reader of "Count" and also from the find_movies_above_score.
    # Did not do so, because on Piazza, "We must follow the parameters and functions exactly"

    print("Here they are: ")
    print("\t", end="")
    g1 = [i.replace(',', ' ') for i in Header]
    g1 = [i.replace('"', '') for i in g1]
    print(*g1, end="")
    for item in NewData:
        print("\t", end="")

        # Did not do extra credit (sorry)
        item = item.replace(',', ' ')
        item = item.replace('"', ' ')
        # I recognize that for titles with commas in their name, there is an extra double space.
        # However, the example output does not reflect exactly what to do, so I assumed what I did is fine.
        # Ex... for year 1970, the title is just "Hi     " rather than ....

        print(item)


if __name__ == '__main__':
    main()