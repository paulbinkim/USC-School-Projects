# Paul Kim
# ITP 116, 10:00-10:50 AM
# Lab 6 - Quadratic Formula using functions

import math  # Importing for math.sqrt function


def getValue(variableName):  # getValue Function
    num = float(input("Enter " + variableName + ": "))  # Gets user input as a float
    return num


def quadraticFormula(a, b, c):  # QuadraticFormula Function
    radicand = b * b - 4 * a * c
    if radicand < 0:  # If Negative
        radicand = -radicand
        part1 = round(-b / (2 * a), 2)
        part2 = round(math.sqrt(radicand) / (2 * a), 2)
        solution1 = str(part1) + " + " + str(part2) + "i"
        solution2 = str(part1) + " - " + str(part2) + "i"
    else:  # Else, if Positive
        solution1 = (-b + math.sqrt(radicand)) / (2 * a)
        solution2 = (-b - math.sqrt(radicand)) / (2 * a)
        solution1 = round(solution1, 2)
        solution2 = round(solution2, 2)
    return [solution1, solution2]


def printSolutions(a, b, c, solution1, solution2):  # PrintSolutions Function
    print("The solutions to the equation ", end="")
    print(str(a) + "x^2 + " + str(b) + "x + " + str(c) + " are ", end="")
    print(str(solution1) + " and " + str(solution2))


def main():  # Main Function that calls other functions
    print("This program finds solutions to the equation ax^2 + bx + c = 0.")
    num1 = getValue("a")
    num2 = getValue("b")
    num3 = getValue("c")
    solutionsList = quadraticFormula(num1, num2, num3)
    printSolutions(num1, num2, num3, solutionsList[0], solutionsList[1])


main()  # Call to main

# Followed Professor Miller's Code during Lecture