# Paul Kim, HW 2, Tuesday 7 - 8:50 PM Section, Spring 2022
# pbkim@usc.edu
# HW 2 - Collecting Pets

# Write a program to organize the several collections of different types of pets into a
# more formalized data structure which can easily be iterated through to get the pets' names.
# A dictionary. where the keys are the pet types, and their corresponding values are each a list of the names of pets.
# You should keep track of how many pets you actually have.

# If you get any animals, make sure you can add them directly to the dictionary.

# Only have one function "main()"
def main():
    # copy and pasted from prompt (Data Set)
    cats_names = ('Cassandra', 'Sir Whiskington', 'Truck')
    dogs_names = {'Barkey McBarkface', 'Leeloo Dallas', 'Taro'}  # Will be unordered so output differs
    parrots_names = ['Squawk', 'Squawk 2: the Squawkquel', 'Larry']
    names = ['peter', 'paul', 'mary']
    animals = ('cat', 'cat', 'hamster')

    # Creating a dictionary
    petDict = {}

    # Adding a list here (non-intentional) for "hard-coding", used to keep track if dictionary key exists
    # Preferred to use set, however, unordered
    uniquePets = ["cat", "dog", "parrot"]

    # Animal Count
    animalCount = 0

    # Programmatically inputting data into petDict (dictionary)
    for item in uniquePets:
        if item not in petDict:
            petDict.setdefault(item, [])

    for item in cats_names:
        petDict["cat"].append(item)
        animalCount += 1

    for item in dogs_names:
        petDict["dog"].append(item)
        animalCount += 1

    for item in parrots_names:
        petDict["parrot"].append(item)
        animalCount += 1

    count = 0  # Used for indexing

    # We add this unique collection into dictionary
    for item in animals:
        if item == "cat":
            petDict[item].append(names[count].capitalize())
        elif item == "hamster":
            petDict.setdefault(item, [])
            uniquePets.append(item)
            petDict[item].append(names[count].capitalize())
        count += 1
        animalCount += 1

    # Start of Prompt //
    print("Hi, Kristof!")

    input1 = 0
    while input1 != "3":
        # Prompt Statements
        print("Please choose from the following options:")
        print("\t1. See all your pets' names.")
        print("\t2. Add a pet.")
        print("\t3. Exit.")
        input1 = input("What would you like to do? (1, 2, 3): ")

        # Error Checking (handling)
        if input1 != "1" or input1 != "2" or input1 != "3":
            while input1 != "1" and input1 != "2" and input1 != "3":
                print()
                print("That's not a number")
                input1 = input("What would you like to do? (1, 2, 3): ")

        print()

        # Code for Option 1
        if input1 == "1":
            print("You have " + str(animalCount) + " pets.")

            # Method to output Dictionary (copied from Lab 2)
            for k in petDict:
                # Arithmetic/Manipulations to remove square brackets from list
                print(k + ": ", end="")
                res = str(petDict[k])
                res = res[1:-1]
                res = res.replace("'", "")
                print(res)

            print()

        # Code for Option 2
        elif input1 == "2":
            animalInput = input("What kind of animal is this?: ")
            animalInput = animalInput.lower()
            print()
            animalNameInput = input("What is the name of the " + animalInput + "?: ")
            animalNameInput = animalNameInput.title()
            print()
            animalCount += 1

            if animalInput not in uniquePets:
                uniquePets.append(animalInput)
                petDict.setdefault(animalInput, [])

            petDict[animalInput].append(animalNameInput)

            print("Great! " + str(animalNameInput) + " the " + str(animalInput) + " is now added to your pets.")
            print()

        # Code for Option 3
        elif input1 == "3":
            print("Goodbye!")
            exit()

    print("Goodbye!")


if __name__ == '__main__':
    main()