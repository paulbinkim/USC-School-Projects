# Paul Kim, pbkim@usc.edu
# ITP 116, 10-10:50 AM, Fall 2021
# Assignment 5
# Description:
# Program that takes gets a taste of Professional C++.
# Output information, utilize arithmetic operators, perform
# string manipulation, utilize conditional statements
# and utilizes loops to repeat certain code blocks.

# Prompt
print("=== ITP435+64 Fall 2021 Fake RLE ===")
print()

# Initialization declarations
strChoice = "0"
new_string = ""

# Main while loop that keeps running until exit (3) is called
while strChoice != "3":
    # Prompt statements
    print("What would you like to do?")
    print("\t1. Compress")
    print("\t2. Decompress")
    print("\t3. Exit")
    strChoice = input("Your choice: ")

    print()

    # String Choice One
    if strChoice == "1":
        sourceString = input("Enter the source string: ")
        sourceString = sourceString.lower()
        if sourceString.isalpha():
            count = 1
            # Loops through each character of string and counts repetition
            # Then concatenates and adds to new_string along with the counts
            for i in range(len(sourceString)-1):
                if sourceString[i] == sourceString[i+1]:
                    count += 1
                else:
                    new_string += str(count) + sourceString[i]
                    count = 1
            new_string += str(count) + sourceString[i+1]
            print("Compressed output:", new_string)
        else:
            print("Only alphabetic characters are allowed when compressing a source string.")

        # Reset String
        new_string = ""
        print()
        print("---")
        print()

    # We can assume string is in correct format (Prompt)
    # Choice 2
    elif strChoice == "2":
        sourceString = input("Enter the source string: ")
        sourceString = sourceString.lower()
        if sourceString.isalnum():
            for i in range(len(sourceString)-1):
                if sourceString[i].isdigit():  # Checks if digit
                    digit = sourceString[i]  # Takes digit count and reprints "x" times the character into string.
                    for x in range(0, int(digit)):
                        new_string += sourceString[i+1]
            print("Decompressed output:", new_string.lower())  # Print and convert string to lower-case
        else:
            print("Only alphanumeric characters are allowed when compressing a source string.")

        # Reset string
        new_string = ""
        print()
        print("---")
        print()

    # Exits code when user inputs 3
    elif strChoice == "3":
        quit()  # Exits code

    # Error checking when user enters an invalid input.
    else:
        print("That is not a valid option.")

        print()
        print("---")
        print()