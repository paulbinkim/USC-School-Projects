# Paul Kim
# ITP 116, 10:00-10:50 AM
# Lab 7 - War Card Game that gives more practice using functions.

import random
import time

# Global Variables which are tuples containing the suits and values.
suits = ("Hearts", "Diamonds", "Clubs", "Spades")
values = ("2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace")


# Function that prints the name of the player who wins or whether the game was a draw.
def printMessage(winner, player1Name, player2Name):
    if winner == 1:
        print(player1Name + " wins.")
    elif winner == 2:
        print(player2Name + " wins.")
    else:
        print("It's a draw.")


# Function that prints out the card that each player drew.
def printCards(playerName, playerCard):
    print(playerName + " got the " + playerCard[1] + " of " + playerCard[0] + ".")


# Function that determines which player won and return a value based on that.
def compareCards(player1Card, player2Card):
    index1 = values.index(player1Card[1])
    index2 = values.index(player2Card[1])
    if index1 > index2:
        return 1
    elif index2 > index1:
        return 2
    else:
        return 0


# Function that will randomly choose a suit and value, and return a tuple that contains the two value.
def getCard():
    randomValue = random.choice(values)
    randomSuit = random.choice(suits)
    return randomSuit, randomValue


# Function that prompts the user the name of the player number passed in. Will return name.
def getName(playerNumber):
    return input("Enter the name of player " + str(playerNumber) + ": ")


# Calls other functions and have print statements
def main():
    print("Welcome to the Game of War!")
    player1Name = getName(1)
    player2Name = getName(2)
    print("Good luck, " + player1Name + " and " + player2Name + "!")
    print("Drawing cards...")
    time.sleep(2)
    player1Card = getCard()
    player2Card = getCard()
    printCards(player1Name, player1Card)
    printCards(player2Name, player2Card)
    winner = compareCards(player1Card, player2Card)
    printMessage(winner, player1Name, player2Name)


main()
