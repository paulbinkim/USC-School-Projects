# Paul Kim, pbkim@usc.edu
# ITP 116, 10-10:50 AM, Fall 2021
# Assignment 6
# Description:
# Smart Contract Program that reads input from a user,
# outputs information, utilize arithmetic operators, perform
# string manipulation, utilize various list techniques
# utilize conditional statements and utilizes loops to repeat certain code blocks.

# Piazza Functionality
import codecs
source = input("Enter the input: ")
inputStr = codecs.decode(source, "unicode-escape")  # Ignoring warning (Piazza)

myList = []  # Empty list used to hold code
numLines = 1  # Number of Lines Variable (Starts from one, since first line starts at 1)
numWords = 0  # Number of Words Variable
numLoops = 0  # Number of Loops Variable

myList = inputStr.split()  # Passing string (words) into list

numLines += source.count("\\n")  # To count the number of lines (counting new lines)

for loop in myList:  # Loop that counts the number of "for" and "while" used in string
    if loop == "for" or loop == "while":
        numLoops += 1

for word in myList:  # Loop that counts the number of words in string
    numWords += 1

# Conditionals of code rating following loop criteria
if numLoops == 0:
    strRating = "Perfection"
elif numLoops == 1:
    strRating = "Could be worse"
else:
    strRating = "Dumpster gas fire"

# Output Statements
print()
print("======")
print("- Number of lines: " + str(numLines))
print("- Number of words: " + str(numWords))
print("- Number of loops: " + str(numLoops))
print("- Rating: " + str(strRating))
print("- Decompressed source:")
print(inputStr)