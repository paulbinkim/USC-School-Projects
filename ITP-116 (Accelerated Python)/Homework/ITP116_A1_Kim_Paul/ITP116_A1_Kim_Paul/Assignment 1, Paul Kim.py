# Paul Kim, pbkim@usc.edu
# ITP 116, 10-10:50 AM, Fall 2021
# Assignment 1
# This program creates a Mad Libs story.
# It gets input from the user and prints output.

Name = input("Enter a person's name: ")
Company = input("Enter a company name: ")
Number = int(input("Enter a positive number with 4 digits: "))
Object = input("Enter an object name (singular): ")
Verb = input("Enter a verb that was applied to the object above (past tense): ")
positiveNumber = int(input("Enter a positive number: "))
decimalNumber = float(input("Enter a decimal number: "))
Location = input("Enter a location name: ")

print("\n")
print("Story 1")
print("My name is " + "\"%s\"" % Name + ".", "I'm the android sent by " + "\"%s\"" % Company + ",", "model number")
print("\"%s\"" % Number + ".", "My " + "\"%s\"" % Object, "was unfortunately " + "\"%s\"" % Verb + ", but its memory has")
print("been transferred. You have " + "\"%s\"" % positiveNumber, "seconds to comply or else will face up to")
print("\"%s\"" % decimalNumber, "years in " + "\"%s\"" % Location + ".")

print("")

print("Story 2")
print("Hi, my name is " + "\"%s\"" % Name + ",", "your tour guide for " + "\"%s\"" % Company + " University! In the")
print("year " + "\"%s\"" % Number + ",", "our private research " + "\"%s\"" % Object + " in Los Angeles, California")
print("was " + "\"%s\"" % Verb + ".", "For the most recent academic year, we broke the record with")
print("\"%s\"" % positiveNumber, "students enrolled in the " + "\"%s\"" % decimalNumber + "-year undergraduate programs located in")
print("our " + "\"%s\"" % Location, "wing. How wonderful!")

print("")
print("---")
print("")

print("Thanks for checking out this program!")