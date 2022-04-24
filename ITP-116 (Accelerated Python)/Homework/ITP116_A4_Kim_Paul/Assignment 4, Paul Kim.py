# Paul Kim, pbkim@usc.edu
# ITP 116, 10-10:50 AM, Fall 2021
# Assignment 4
# Description:
# Program that takes a look at Gordon Ramsay's Bank Balance
# That stores user input, outputs information, utilizes arithmetic operators
# Compare values with boolean expressions, use conditional statements to alter behavior
# And utilizes loops to repeat certain blocks based on a condition.

Balance = 0  # Initializing a Bank Balance of $

# Printing initialization output statement
print("Welcome to Gordon Ramsay's Bank Balance! The show where hero and zero can be")
print("down to one simple question...")

# First question prompt
print()
print("------")
print("Question 1:")
print("What is objectively the best type of party during COVID?")
print("A. Sneaking past the guards into University Gateway at night.")
print("B. \"If I get it, I get it\" party in Tuscany garage.")
print("C. No mask YOLO party on Figueroa Street with signs to block traffic.")
print("D. The best party during COVID is one that never takes place.")
boolean = 0

Answer1 = input("Your answer is: ")

while boolean == 0:  # While statement that will keep running until correct input
    if Answer1 == "d" or Answer1 == "D":  # Case insensitive
        Balance += 6000
        print("Correct! Your balance is now $" + str(Balance) + ".")
        break
    else:
        Balance -= 3000
        print("Wrong! Your balance is now $" + str(Balance) + ".")
        Answer1 = input("Your answer is: ")

# Second question prompt
print("------")
print("Question 2:")
print("What class is this program for?")
print("A. ITP-116")
print("B. CSCI-201")
print("C. ITP-256")
print("D. I believe I am a self-driven learner and a great fit for your company. I\n wrote this entirely out of my "
      "overwhelming desire and thirst for knowledge.\n As Steve Jobs once said, \"stay hungry, stay foolish.\" Wait, "
      "it wasn't \"stay\n thirsty\"?")
boolean = 0

Answer1 = input("Your answer is: ")

while boolean == 0:  # While statement that will keep running until correct input
    if Answer1 == "A" or Answer1 == "a":  # Case incentive
        Balance += 6000
        print("Correct! Your balance is now $" + str(Balance) + ".")
        break
    else:
        Balance -= 3000
        print("Wrong! Your balance is now $" + str(Balance) + ".")
        Answer1 = input("Your answer is: ")

# Third question prompt (INSTANT DEATH)
print("------")
print("Question 3 [INSTANT DEATH!]: ")
print("What is considered a \"pro-gamer move\" in the software engineering world?")
print("A. Force pushing into a shared repository every single time.")
print("B. Killing the entire terminal when you accidentally open Vim because Control+C doesn’t make it quit.")
print("C. Resist using any IDEs because Sublime Text (UNREGISTERED) is superior.")
print('D. All of the above.')

Answer1 = input("Your answer is: ")

# Conditionals, if correct user obtains $6000, if wrong and user has money, user loses everything
# Only one chance to answer
if Answer1 == "D" or Answer1 == "d": # Case insensitive
    Balance += 6000
    print("Correct! Your balance is now $" + str(Balance) + ".")
else:
    if Balance > 0:
        Balance = 0
        print("Wrong! Your balance is now $" + str(Balance) + ".")
    else:
        Balance -= 3000
        print("Wrong! Your balance is now $" + str(Balance) + ".")
print("------")

if Balance > 0:
    print("Finally, a good flipping contestant. You don't come into cooking to get rich,\n"
          "but you come into this show to get rich and you did it. Congratulations!")
elif Balance < 0:
    print("Hey hey hey you, hey you, come here... You do seriously surprise me... With\n"
          "how bad you are!")
else:
    print("You came with nothing and you are leaving with nothing.")
