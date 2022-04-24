# Paul Kim, pbkim@usc.edu
# ITP 116, 10-10:50 AM, Fall 2021
# Assignment 2
# Description:
# Program that stores user input and outputs information
# Utilizes arithmetic operators, and compares values with boolean expressions.
# Utilizes conditional statements to alter behavior based on input.

# Prompt statements, requiring user input.
print()
print("Welcome to Who Wants to Be a $DOGE Holder!")
# Assumes that input will be valid
Prediction = int(input("How many questions do you think you can answer correctly (out of 3): ")) # Must be an integer
print()
print("------")

QuestionsCorrect = 0 # Variable to tally how much questions are correct

# First question prompt.
print("Question 1:")
print("What is objectively the best type of party during COVID?")
print("A. Sneaking past the guards into University Gateway at night.")
print("B. \"If I get it, I get it\" party in Tuscany garage.")
print("C. No mask YOLO party on Figueroa Street with signs to block traffic.")
print("D. The best party during COVID is one that never takes place.")

Answer = input("You answer is: ")
if Answer == "D" or Answer == "d":
      print("Correct!")
      QuestionsCorrect +=1
else:
      print("Wrong! The correct answer is D.")

# Second question prompt
print("------")
print("Question 2:")
print("What class is this program for?")
print("A. ITP-116")  # Changed output to correct class... not ITP-499
print("B. CSCI-201")
print("C. ITP-256")
print("D. I believe I am a self-driven learner and a great fit for your company. I\nwrote this entirely out of my "
      "overwhelming desire and thirst for knowledge.\nAs Steve Jobs once said, “stay hungry, stay foolish.” Wait, "
      "it wasn't “stay\nthirsty”?")

Answer = input("You answer is: ")
if Answer == "A" or Answer == "a":
      print("Correct!")
      QuestionsCorrect += 1
else:
      print("Wrong! The correct answer is A.")

# Third question prompt
print("------")
print("Question 3:")
print("What is considered a “pro-gamer move” in the software engineering world?")
print("A. Force pushing into a shared repository every single time.")
print("B. Killing the entire terminal when you accidentally open Vim because\n"
      "Control+C doesn't make it quit.")
print("C. Resist using any IDEs because Sublime Text (UNREGISTERED) is superior.")
print("D. All of the above.")

Answer = input("You answer is: ")
if Answer == "D" or Answer == "d":
      print("Correct!")
      QuestionsCorrect += 1
else:
      print("Wrong! The correct answer is D.")

# Output statement returning prediction, and actual questions correct
print("------")
print("You predicted you would answer " + str(Prediction) + " questions correctly and you answered " + str(QuestionsCorrect))
print("questions correctly.")
print()

# Conditionals depending on prediction, and the questions actually correct.
if Prediction <= QuestionsCorrect:
      print("Wowow! Such doge, some say you are a prophet of profit. You won 1337 shares\n"
            "of $DOGE!")
else:
      print("You were this close to getting set up for life but sadly you missed the mark.\n"
            "Goodbye sadge.")


