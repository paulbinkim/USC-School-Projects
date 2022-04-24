# Paul Kim, pbkim@usc.edu
# ITP 116, 10-10:50 AM, Fall 2021
# Assignment 8
# Description:
# Weatherman program that outputs information, utilizes various arithmetic operators,
# utilizes various list techniques, utilize conditional statements, utilizes
# loops to repeat certain code blocks, while at the same time, uses function to streamline functionality.

# Assuming the formatting of input is correct

# getWeather function that allows user to input data about weather separated by "|"
# Function 1
def getWeather():
    key = ""
    TempList = []
    MyList = []
    while key.lower() != "end":  # While Loop that takes input until end is entered (Case-insensitive)
        key = input("Input weather data: ")

        if key.lower() == "end":
            break

        TempList = key.split("|")  # Split function for list
        MyList += TempList
        print("Saved!")

    print("---")
    return MyList  # Function that returns a value


# promptUser function that prompts user which city they would like information
# Function 2
def promptUser():
    string = ""
    string = input("For what city would you like weather information? ")
    return string  # Function that returns a value


# Menu function that gets user input on which option he/she would like to pursue
# Function 3
def Menu(UserInput, IndexList, myList):  # Function that takes at least one parameter
    string = input("For what city would you like weather information? ")

    if string.upper() in (name.upper() for name in myList):  # Case insensitivity (If city exists)
        index = IndexList.index(string.lower())
        printOutputs(myList, index)

    elif string.lower() == "all":  # Printing all cities
        size = len(myList)
        SizeLoop = size / 10
        count = 0
        SizeLoopCount = 0

        for i in range(0, int(SizeLoop)):
            printOutputsALL(myList, count)
            count += 10
            SizeLoopCount += 1
        print("---")
        # Minor Change here vs. Assignment 7 is that there is no new line
        # in between the two cities. Therefore, had to take away an if condition.

    elif string.lower() == "exit":  # If exit is called, program terminates
        print("Goodbye!")
        quit()

    else:  # If city does not exist.
        print("I do not have information about the weather in " + string + ".")
        print("---")


# printOutputs function that prints the output strings, taking in two parameters
# Function 4
def printOutputs(MyList, index):  # Function that takes at least one parameter
    print("I do have information about the weather in " + MyList[index] + ":")
    print("The high temperature is " + MyList[index + 3] + " degrees Fahrenheit.")
    print("The low temperature is " + MyList[index + 2] + " degrees Fahrenheit.")
    print("The humidity is " + MyList[index + 4] + "%.")
    print("The pressure is " + MyList[index + 5] + " inHg.")
    print("The visibility is " + MyList[index + 6] + " miles.")
    print("The wind speed is " + MyList[index + 7] + " mph.")
    print("The wind direction is " + MyList[index + 8] + " degrees.")
    print("It is " + MyList[index + 9] + ".")
    print("---")


# printOutputsALL function that prints the output strings when all is called, taking in two parameters
# Function 5
def printOutputsALL(MyList, index):  # Function that takes at least one parameter
    print("I do have information about the weather in " + MyList[index] + ":")
    print("The high temperature is " + MyList[index + 3] + " degrees Fahrenheit.")
    print("The low temperature is " + MyList[index + 2] + " degrees Fahrenheit.")
    print("The humidity is " + MyList[index + 4] + "%.")
    print("The pressure is " + MyList[index + 5] + " inHg.")
    print("The visibility is " + MyList[index + 6] + " miles.")
    print("The wind speed is " + MyList[index + 7] + " mph.")
    print("The wind direction is " + MyList[index + 8] + " degrees.")
    print("It is " + MyList[index + 9] + ".")


# Main Function that makes calls to other functions
def main():
    myList = getWeather()
    IndexList = [item.lower() for item in myList]  # Used to find index
    UserInput = ""
    while UserInput.lower() != "exit":
        Menu(UserInput, IndexList, myList)
    # Main function does not make any calls to input and output
    # Everything is called in a function, and main() merely just makes calls to functions
    # that save variables and passes in to other functions for functionality.


# Call to main()
main()

# All requirements from assignment 7 met
# 6 functions are included and used
# Two functions take at least one parameter
# Two functions return a value
# Main function does not contain any input or output
# Prints exact output
