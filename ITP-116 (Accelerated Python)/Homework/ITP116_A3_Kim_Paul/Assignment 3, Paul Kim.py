# Paul Kim, pbkim@usc.edu
# ITP 116, 10-10:50 AM, Fall 2021
# Assignment 3
# Description:
# Program that simulates a boba tea shop that stores user input,
# output information, utilizes arithmetic operators, compare values
# with boolean expressions, and utilizes conditional statements to
# alter behavior based on input.

# Initializing Balance variable that updates after every choice
Balance = 0.00

# Prompt statement getting customer's budget
print("Welcome to Cha Literally Means Tea! We strive to provide you with the best")
print("boba cha in the entire plaza located on Figueroa where Yoshinoya is!")
Budget = float(input("What's your budget for the order in USD? "))
print("Got it. Let's build your boba cha!")

print("--")  # Space

# Series of questions that simulate building custom order of boba tea (Pick Base)
print("What would you like as a base?")
print("\t A. 4.00 - Red Ruby Prem. Black Milk Tea w/ Brown Sugar")
print("\t B. 4.50 - Red Ruby Prem. Black Milk Tea w/ Pearls")
print("\t C. 4.00 - Jasmine Green Milk Tea")
print("\t D. 4.00 - Light Roast Oolong Milk Tea")
print("\t E. 4.00 - Full Roast Oolong Milk Tea")
print("\t F. 4.00 - Golden Phoenix High Mtn. Milk Tea")
print("\t G. 4.25 - Mango Green Milk Tea")
BaseChoice = input("Your choice: ")

# Series of conditionals from choice (A-G)
# Assuming that customers only make valid choices (else is not needed)
# Case-insensitive
if BaseChoice == "A" or BaseChoice == "a":
    print("Great Choice! Red Ruby Prem. Black Milk Tea w/ Brown Sugar is our best seller!")
    Balance += 4.00

if BaseChoice == "B" or BaseChoice == "b":
    print("Great Choice! Red Ruby Prem. Black Milk Tea w/ Pearls is our best seller!")
    Balance += 4.50

if BaseChoice == "C" or BaseChoice == "c":
    print("Great Choice! Jasmine Green Milk Tea is our best seller!")
    Balance += 4.00

if BaseChoice == "D" or BaseChoice == "d":
    print("Great Choice! Light Roast Oolong Milk Tea is our best seller!")
    Balance += 4.00

if BaseChoice == "E" or BaseChoice == "e":
    print("Great Choice! Full Roast Oolong Milk Tea is our best seller!")
    Balance += 4.00

if BaseChoice == "F" or BaseChoice == "f":
    print("Great Choice! Golden Phoenix High Mtn. Milk Tea is our best seller!")
    Balance += 4.00

if BaseChoice == "G" or BaseChoice == "g":
    print("Great Choice! Mango Green Milk Tea is our best seller!")
    Balance += 4.25

# Prints total balance after choice
print("Your current balance is $" + str(f'{Balance:.2f}') + ".")

# Prompts to pick toppings
print("Time to choose some toppings! Enter how many portions of each addon you'd")
print("like to add to your base tea =) The price show below is per portion")

Pearls = int(input("0.50 - Pearls: "))
MiniPearls = int(input("0.50 - Mini Pearls: "))
Pudding = int(input("0.50 - Pudding: "))
ToppingsOne = Pearls + MiniPearls + Pudding
Balance += ToppingsOne * 0.5
print("Your current balance is $" + str(f'{Balance:.2f}') + ".")

AloeVera = int(input("0.50 - Aloe Vera: "))
RedBean = int(input("0.50 - Red Bean: "))
ToppingsTwo = AloeVera + RedBean
Balance += ToppingsTwo * 0.5
print("Your current balance is $" + str(f'{Balance:.2f}') + ".")

Tiramisu = int(input("0.75 - Tiramisu Creama "))
Balance += Tiramisu * 0.75
print("Your current balance is $" + str(f'{Balance:.2f}') + ".")

SaltyCheese = int(input("0.50 - Salty Cheese Creama: "))
GoldFlakes = int(input("66.88 - Edible Gold Flakes: "))
Balance += SaltyCheese * 0.5 + GoldFlakes * 66.88
print("Your current balance is $" + str(f'{Balance:.2f}') + ".")

# Prompt that displays total
print()
print("Your order is complete! The total is $" + str(f'{Balance:.2f}') + ".")
print()

# Outputs whether budget meets the balance, or if it fails to meet balance
if Budget >= Balance:
    print("Enjoy your boba tea!")
else:
    print("Oops, looks like you didn't bring enough money! You would have to start over.")

# Piazza (No While Loop is required)
