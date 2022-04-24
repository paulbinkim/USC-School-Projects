# Paul Kim, pbkim@usc.edu
# ITP 116, 10-10:50 AM, Fall 2021
# Lab 4
# Description:
# Travel Recommender Program
import random

# Initialization of Program
print("Welcome to the travel recommendation program.")
cities = ["New York", "London", "Beijing", "Sydney"]

print()

strChoice = "0"
# Main while loop
while strChoice != "5":
    print("1. Add potential cities to the list.")
    print("2. View the potential cities.")
    print("3. Remove a city from the list.")
    print("4. Make a recommendation where to go.")
    print("5. Exit")

    strChoice = input("What would you like to do? ")

    while not strChoice.isdigit():  # If choice is not a digit (loop)
        print("Choice must be numeric.")
        strChoice = input("What would you like to do? ")

    if strChoice == "1":  # Choice 1
        newCity = input("What city would you like to add? ")
        if newCity in cities:
            print("That's a great city, but it's already in our list.")
            print()
        else:
            cities.append(newCity)
            print(newCity, "was added to the list.")
            print()

    elif strChoice == "2":  # Choice 2
        print("The cities currently in the list are ", end="")
        for city in cities:
            print(city, end="")
            if not city == cities[len(cities) - 1]:
                print(", ", end="")
            else:
                print(".")
        print()

    elif strChoice == "3":  # Choice 3
        removeCity = input("What city would you like to remove? ")
        if removeCity in cities:
            cities.remove(removeCity)
            print(removeCity, "was removed from the list.")
            print()
        else:
            print(removeCity, "is not in the list.")
            print()

    elif strChoice == "4":  # Choice 4
        randomCity = random.choice(cities)
        print("Pack your bags. We're going to", randomCity)
        print()

    elif strChoice == "5":  # Choice 5 (Terminates)
        print("Thank you for using my travel recommendation program.")

    else:  # If input is invalid
        print("That is not a valid option")
        print()
