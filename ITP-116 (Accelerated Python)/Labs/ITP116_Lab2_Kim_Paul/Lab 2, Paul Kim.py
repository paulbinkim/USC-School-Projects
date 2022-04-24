# Paul Kim, pbkim@usc.edu
# ITP 116, 10-10:50 AM, Fall 2021
# Lab 2
# Description:
# Program that uses Boolean expressions and arithmetic operators to achieve
# Desired Results

# Table 1
# Equation 1 - True
# Equation 2 - True
# Equation 3 - False
# Equation 4 - False
# Equation 5 - True
# Equation 6 - True
# Equation 7 - False

# Table 2 (Produce a True Output) (A,B,C,D)
# Equation 1 - 1,1,1,1
# Equation 2 - 0,0,1,1
# Equation 3 - 1,0,1,0
# Equation 4 - 1,0,0,1
# Equation 5 - 1,0,0,0
# Equation 6 - 1,0,1,0
# Equation 7 - 0,1,0,0

Number = float(input("Enter a number: "))
Operator = input("Enter an operator (+, -, x, /, //, %, **): ")
Number2 = float(input("Enter a number: "))
answer = 0

if Operator == "+":
    answer = Number + Number2

elif Operator == "-":
    answer = Number - Number2

elif Operator == "x":
    answer = Number * Number2

elif Operator == "/":
    answer = Number / Number2

elif Operator == "//":
    answer = Number // Number2

elif Operator == "%":
    answer = Number % Number2

elif Operator == "**":
    answer = Number ** Number2

else:
    print("You didn't enter a proper operator.")

print(Number, Operator, Number2, "=", answer)