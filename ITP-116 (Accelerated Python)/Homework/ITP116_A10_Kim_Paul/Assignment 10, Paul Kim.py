# Paul Kim, pbkim@usc.edu
# ITP 116, 10-10:50 AM, Fall 2021
# Assignment 10
# Description:
# Portfolio Tracker that outputs information, utilizes arithmetic operators, utilizes various list
# techniques, utilizes conditional statements, utilizes File I/O to read and write files, utilizes
# loops to repeat certain code blocks, and utilizes functions to streamline logic and code.

import os  # Library used to file writing operation


def main():  # Main function that calls sub-functions and uses loops
    fileName = prompt()
    my_dict = dictionary(fileName)
    userInput = 0
    while userInput != 8:  # While loop of menu until (8) is called
        printMenu()
        userInput = input("Choice: ")
        if userInput == "1":
            userInput1(my_dict)
        elif userInput == "2":
            userInput2(my_dict)
        elif userInput == "3":
            userInput3(my_dict)
        elif userInput == "4":
            userInput4(my_dict)
        elif userInput == "5":
            userInput5(my_dict)
        elif userInput == "6":
            userInput6(my_dict)
        elif userInput == "7":
            temp = fileName
            fileName = userInput7(temp, my_dict)
            my_dict = userInput7extra(fileName)
        elif userInput == "8":
            userInput8(fileName, my_dict)


def prompt():  # Prompt Function that prompts a user if he/she wants to read file or start from scratch
    condition = input("Would you like to read from a previously save file? (y/n) ")
    if condition == "y" or condition == "Y":
        fileName = input("What is the name of the file? ")
        # Assume that the file exists and the format is valid
        return fileName
    else:
        return "empty"


def dictionary(filename):  # Dictionary function that creates/returns a dictionary given response from prompt
    if filename == "empty":
        my_dict = {}
        print("--------")
    else:
        my_dict = readFile(filename)
        print("File read!")
        print("--------")
    return my_dict


def userInput1(my_dict):  # Function that prints entire portfolio
    if len(my_dict) == 0:  # If empty
        print("--------")
        print("Your portfolio is currently empty.")
        print("--------")
    else:
        print("--------")
        print("Here is your current portfolio:")
        dictionary_items = my_dict.items()
        for item in dictionary_items:
            ticker = item[0]
            value = item[1]
            print("\t- " + ticker + ": " + value)
        print("--------")


def userInput2(my_dict):  # Function that prints individual asset details.
    print("--------")
    assets = input("About what assets would you like to inquire? ")
    # We assume only valid tickers (not specified by prompt or sample output)
    AssetsList = assets.split(",")
    print("Here is the requested data:")
    for item in AssetsList:
        print("\t- " + item + ": " + my_dict[item])
    print("--------")


def userInput3(my_dict):  # Function that adds a new asset to portfolio
    print("--------")
    condition = False
    asset = input("What is the new asset you'd like to add? ")
    while not condition:
        if asset in my_dict:  # Error Checking
            print("Sorry, this asset already exists!")
            asset = input("What is the new asset you'd like to add? ")
        else:
            value = input("How much of it do you own? ")
            my_dict[asset] = value
            print("Added " + value + " " + asset + " to your portfolio!")
            condition = True
            print("--------")


def userInput4(my_dict):  # Function that edits an existing asset
    print("--------")
    condition = False
    asset = input("Which asset would you like to edit? ")
    while not condition:
        if asset not in my_dict:  # Error checking
            print("Sorry, this asset is not a part of your portfolio.")
            asset = input("Which asset would you like to edit? ")
        else:
            value = input("You currently own " + my_dict[asset] + " " + asset + ". Enter the new value: ")
            my_dict[asset] = value
            print("You currently own " + value + " " + asset + ".")
            condition = True
            print("--------")


def userInput5(my_dict):  # Function that removes an existing asset
    print("--------")
    condition = False
    asset = input("Which asset would you like to remove? ")
    while not condition:
        if asset not in my_dict:  # Error checking
            print("Sorry, this asset is not a part of your portfolio.")
            asset = input("Which asset would you like to remove? ")
        else:
            value = input("You currently own " + my_dict[asset] + " " + asset + ". Proceed to remove? (y/n) ")
            if value == "y" or value == "Y":
                del my_dict[asset]
                print("--------")
            else:
                print("--------")
            condition = True


def userInput6(my_dict):  # Function that erases entire portfolio
    print("--------")
    print("Here is your current portfolio:")
    dictionary_items = my_dict.items()
    for item in dictionary_items:
        ticker = item[0]
        value = item[1]
        print("\t- " + ticker + ": " + value)
    value = input("Proceed to erase the entire portfolio? (y/n) ")
    if value == "n" or value == "N":
        print("--------")
        return
    else:
        value2 = input("Please confirm, you are trying to erase everything! (y/n) ")
        if value2 == "n" or value2 == "N":
            print("--------")
            return
        else:
            my_dict.clear()
            print("Portfolio erased.")
            print("--------")


def userInput7(InputFilename, my_dict):  # Function that opens a new file
    print("--------")
    value = input("You have made changes to the current file. Would you like to commit the changes? (y/n) ")
    if value == "n" or value == "N":
        print("Your changes have been discarded.")
        fileName = input("What is the name of the file? ")
        return fileName
    else:
        outputFile = open(InputFilename, "w")
        outputFile.write("Name,Amount\n")  # I only put this because there's no example, and i'm assuming an empty
        # file is given.
        for item in my_dict:
            outputFile.write(item)
            outputFile.write(",")
            outputFile.write(my_dict[item])
            outputFile.write("\n")
        outputFile.close()
        print("Your changes have been saved!")
        fileName = input("What is the name of the file? ")
        return fileName


def userInput7extra(filename):  # Function used in function 7 that returns a dictionary
    my_dict = readFile(filename)
    print("File read!")
    print("--------")
    return my_dict


def userInput8(filename, my_dict):  # Exit Function
    print("--------")
    choice = input("You have made changes to the current file. Would you like to commit the changes? (y/n) ")
    if choice == "y" or choice == "Y":
        outputFile = open(filename, "w")
        outputFile.write("Name,Amount\n")  # I do this because the example sample is formatted like this
        for item in my_dict:
            outputFile.write(item)
            outputFile.write(",")
            outputFile.write(my_dict[item])
            outputFile.write("\n")
        outputFile.close()
        print("Your changes have been saved!")
        print("Goodbye!")
        exit(0)
    else:
        print("Your changes have been discarded.")
        print("Goodbye!")
        exit(0)


def readFile(inputFilename):  # Readfile Function that reads the input file and saves content in a list, returns
    # dictionary
    dictionary = {}
    inputFile = open(inputFilename, "r")
    # This is important, because of the sample input file.
    # I am assuming that every file starts with "Name,Amount" as the first line.
    # Therefore, to read the file, I always skip this first line to start parsing through tickers and values.
    # If file is empty or just 1 line (which is Name,Amount), I skip and proceed to return a dictionary.
    if os.path.getsize(inputFilename) != 0:  # This skips the first line of the file (name,amount)
        # UNLESS, file is empty
        next(inputFile)
    elif os.path.getsize(inputFilename) == 1:
        return dictionary
    contents = []
    for line in inputFile:
        temp1 = line.rstrip()
        wordAndNum = temp1.split(",")
        contents.append(wordAndNum)
        dictionary[str(contents[0][0])] = contents[0][1]
        contents = []
    inputFile.close()
    return dictionary


def printMenu():
    print("Main menu:")
    print("\t1. Print Entire Portfolio")
    print("\t2. Print Asset Details")
    print("\t3. Add a New Asset")
    print("\t4. Edit an Existing Asset")
    print("\t5. Remove an Existing Asset")
    print("\t6. Erase Entire Portfolio")
    print("\t7. Open a New File")
    print("\t8. Exit")


main()  # Main call

# All inputs are case insensitive
# At least 9 functions, including main function
# In main function, there are only be function calls and loops
# Use dictionary
