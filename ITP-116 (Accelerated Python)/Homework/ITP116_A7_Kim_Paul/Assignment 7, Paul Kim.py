# Paul Kim, pbkim@usc.edu
# ITP 116, 10-10:50 AM, Fall 2021
# Assignment 7
# Description:
# Weatherman program that outputs information, utilizes various arithmetic operators,
# utilizes various list techniques, utilize conditional statements, and utilizes
# loops to repeat certain code blocks.

# Assuming the formatting of input is correct

# Initializing Variables
key = ""
TempList = []
MyList = []
while key.lower() != "end": # While Loop that takes input until end is entered (Case-insensitive)
    key = input("Input weather data: ")

    if key.lower() == "end":
        break

    TempList = key.split("|")  # Split function for list
    MyList += TempList
    print("Saved!")

print("---")

IndexList = [item.lower() for item in MyList]  # Used to find index

string = ""
while string.lower() != "exit":  # While loop that accepts user input until exit is entered (Case-insensitive)
    string = input("For what city would you like weather information? ")

    if string.upper() in (name.upper() for name in MyList):  # Case insensitivity (If city exists)
        index = IndexList.index(string.lower())
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

    elif string.lower() == "all":  # Printing all cities
        size = len(MyList)
        SizeLoop = size / 10
        count = 0
        SizeLoopCount = 0

        for i in range(0, int(SizeLoop)):
            print("I do have information about the weather in " + MyList[count] + ":")
            print("The high temperature is " + MyList[count + 3] + " degrees Fahrenheit.")
            print("The low temperature is " + MyList[count + 2] + " degrees Fahrenheit.")
            print("The humidity is " + MyList[count + 4] + "%.")
            print("The pressure is " + MyList[count + 5] + " inHg.")
            print("The visibility is " + MyList[count + 6] + " miles.")
            print("The wind speed is " + MyList[count + 7] + " mph.")
            print("The wind direction is " + MyList[count + 8] + " degrees.")
            print("It is " + MyList[count + 9] + ".")

            if SizeLoopCount != int(SizeLoop - 1):
                print("")
            else:
                print("---")

            count += 10
            SizeLoopCount += 1

    elif string.lower() == "exit":  # If exit is called, program terminates
        print("Goodbye!")
        quit()

    else:  # If city does not exist.
        print("I do not have information about the weather in " + string + ".")
        print("---")