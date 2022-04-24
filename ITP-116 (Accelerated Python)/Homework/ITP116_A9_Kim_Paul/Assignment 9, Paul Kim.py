# Paul Kim, pbkim@usc.edu
# ITP 116, 10-10:50 AM, Fall 2021
# Assignment 9
# Description:
# From Greece to France program that outputs information, utilizes various arithmetic operators,
# utilizes various list techniques, utilize conditional statements, utilizes
# loops to repeat certain code blocks, while at the same time, uses function to streamline functionality.

# All inputs are case insensitive
# We need to validate user input
# Create at least 4 functions (including main)
# Use lists

import math  # Including for Sqrt Function


def GetInput():  # Function that gets user input and returns a list with all the values
    response = ""
    InputList = []

    while response.lower() != "end":  # Loop until "end" is called (Case-Insensitive)
        TempList = []
        response = input("What's the name of the location? ")

        if response.lower() == "end":
            break

        InputList.append(response)

        coordinates = input("What are the X and Y coordinates? ")
        TempList = coordinates.split(" ")
        flag = checkUserInput(TempList)

        if flag == 1:  # If Input is Valid
            InputList.append(TempList[0])
            InputList.append(TempList[1])
            print("Saved!")

        elif flag == 0 or flag == 2:  # If Input is Invalid
            while flag == 0 or flag == 2:
                coordinates = input("What are the X and Y coordinates? ")
                TempList = coordinates.split(" ")
                flag = checkUserInput(TempList)
                if flag != 0 and flag != 2:
                    break
            InputList.append(TempList[0])
            InputList.append(TempList[1])
            print("Saved!")

    print("--------")
    return InputList  # Returns List


def checkUserInput(TempList):  # Function that checks for the validity of User Input
    try:
        count = 0
        for i in TempList:
            x = float(i)
            count += 1
        if count != 2:
            print("Please enter two numeric values for the X and Y coordinates.")
            return 2
        else:
            return 1  # Returns 1 if Valid, and Returns other values if something is wrong
    except ValueError:
        print("Please only enter numeric values for the X and Y coordinates.")
        return 0


def outputLocations(List):  # Function that prints menu of all locations
    print("Available locations:")
    size = len(List)
    count = 1
    for i in range(0, size - 1, 3):
        print("\t" + str(count) + ". " + List[i])
        count += 1


def getPick(place):  # Function that prompts users of the Location to pick
    x = input("Please pick the " + place + " location: ")
    if x.lower() == "exit":
        print("Goodbye friend!")
        quit()
    return x


def validatePick(Location, ListSize):  # Function that validates the User's pick, if it falls into the range etc.
    AvailableLocations = ListSize / 2
    if Location.isalpha():
        print(Location + " is not a valid location!")
        return 0
    elif int(Location) < 1 or int(Location) > AvailableLocations:
        print(Location + " is not a valid location!")
        return 0
    else:
        return 1


def EuclideanDistance(TempList, Location1, Location2):  # Function that calculates the Euclidean Distance
    TempList2 = []
    for item in TempList:
        if not item.isalpha():
            TempList2.append(item)

    listFloat = [float(x) for x in TempList2]

    Loc1Index = (int(Location1) - 1) * 2
    Loc2Index = (int(Location2) - 1) * 2
    x1 = listFloat[Loc1Index]
    y1 = listFloat[Loc1Index + 1]
    x2 = listFloat[Loc2Index]
    y2 = listFloat[Loc2Index + 1]
    Distance = math.sqrt(((x2 - x1) ** 2 + (y2 - y1) ** 2))
    print("The Euclidean distance between USC and UCLA is " + "{:.{}f}".format(Distance, 6))


def ManhattanDistance(TempList, Location1, Location2):  # Function that calculates the Manhattan Distance
    TempList2 = []
    for item in TempList:
        if not item.isalpha():
            TempList2.append(item)

    listFloat = [float(x) for x in TempList2]

    Loc1Index = (int(Location1) - 1) * 2
    Loc2Index = (int(Location2) - 1) * 2
    x1 = listFloat[Loc1Index]
    y1 = listFloat[Loc1Index + 1]
    x2 = listFloat[Loc2Index]
    y2 = listFloat[Loc2Index + 1]
    Distance = abs(x2-x1) + abs(y2 - y1)
    print("The Manhattan distance between USC and UCLA is " + "{:.{}f}".format(Distance, 7))
    print("--------")


def main():  # Main Function that makes calls to all the sub-functions
    Location1 = ""
    List = GetInput()
    ListSize = len(List)
    while Location1.lower() != "exit":
        outputLocations(List)
        Location1 = getPick("first")
        flag = validatePick(Location1, ListSize)
        if flag == 0:
            while flag == 0:
                Location1 = getPick("first")
                flag = validatePick(Location1, ListSize)

        Location2 = getPick("second")
        flag = validatePick(Location2, ListSize)
        if flag == 0:
            while flag == 0:
                Location2 = getPick("second")
                flag = validatePick(Location2, ListSize)

        EuclideanDistance(List, Location1, Location2)
        ManhattanDistance(List, Location1, Location2)


main()  # Call to main

# Prompts Users for name and coordinates
# Displays error messages for all three instances of errors
# Continues to prompt the user until "end" is called (case-insensitive)
# Displays appropriate menu
# Validates menu input
# Calculates Distances Correctly
# More than four functions used
# No input/output in main function
