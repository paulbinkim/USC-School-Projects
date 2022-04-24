# Paul Kim, pbkim@usc.edu
# ITP 116, 10-10:50 AM, Fall 2021
# Lab 3
# Description:
# Program that uses Boolean expressions and conditions to implement
# The Guess a Number game.

import random

num = random.randint(1, 100)  # Inclusive (includes 1 and 100)
guessedNumber = -1  # Always false

# Main Code Function using a while loop and conditionals
print("I'm thinking of a number between 1 and 100.")
while guessedNumber != num:
    guessedNumber = int(input("Guess a number: "))
    if guessedNumber > 100 or guessedNumber < 1:
        print(guessedNumber, "is outside the range of possible values.")
    elif guessedNumber < num:
        print(guessedNumber, "is too low.")
    elif guessedNumber > num:
        print(guessedNumber, "is too high.")
    else:
        print("You guessed it!")
        PlayAgain = input("Do you want to play again? ")
        if PlayAgain == "no":
            print("Thank you for playing!")
        elif PlayAgain == "yes":
            num = random.randint(1, 100)
            print()  # Space
            print("I'm thinking of a number between 1 and 100.")