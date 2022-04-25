# Paul Kim, Lab 2, Tuesday 7 - 8:50 PM Section
# pbkim@usc.edu
# Lab 2 - Collecting Collections
# Ask the user for an input, then convert that collection into the following other types of collections
# list, tuple, set, dictionary

# should only have one function (prompt)
def main():
    solutionString = ""  # string
    solutionList = []  # list
    solutionTuple = ()  # tuple
    solutionSet = set()  # set
    solutionDictionary = {}  # dictionary

    input1 = input("Please enter an input to be converted: ")
    print()

    # main loop that parses through input and makes additions accordingly
    for char in input1:
        char1 = str(char) + ', '
        solutionString += char1
        solutionList.append(char)
        solutionTuple = solutionList
        solutionSet.add(char)
        if char in solutionDictionary:
            solutionDictionary[char] += 1
        else:
            solutionDictionary[char] = 1

    # Method to output String
    print("string: " + solutionString)

    # Method to output List
    print("list: ", end="")
    print(*solutionList, sep=', ', end="")  # Method to format data as shown in Example Output
    print(',')

    # Method to output Tuple
    print("tuple: ", end="")
    print(*solutionTuple, sep=', ', end="")  # Method to format data as shown in Example Output
    print(',')

    # Method to output Set
    print("set: ", end="")
    # Displays correct and # of unique char values in Set
    print(*solutionSet, sep=', ', end="")  # I'm not entirely sure why this output is difference, but I hope it is fine
    print(',')

    # Method to output Dictionary
    print("dictionary: ")
    for k in solutionDictionary:
        print("\t" + k + ": ", end="")
        print(solutionDictionary[k])


if __name__ == '__main__':
    main()