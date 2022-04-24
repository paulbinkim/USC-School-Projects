# Paul Kim
# ITP 116, 10:00-10:50 AM
# Lab 8 - File Expansion program that gives us practice working with File I/0

def main():  # Main Function that makes calls to other functions
    print("Welcome to the File Extension program.")
    inputFilename = getFilename("input")
    outputFilename = getFilename("output")
    fileContents = readFile(inputFilename)
    writeFile(fileContents, outputFilename)
    print(outputFilename + " has been created.")


def getFilename(typeofFile):  # Get filename Function that prompts user nad returns a filename
    filename = input("Enter the name of the " + typeofFile + " file: ")
    return filename


def readFile(inputFilename):  # Readfile Function that reads the input file and saves content in a list
    inputFile = open(inputFilename, "r")
    contents = []
    for line in inputFile:
        wordAndNum = line.split(" ")
        contents.append(wordAndNum)
    inputFile.close()
    return contents


def writeFile(listOfWords, outputFilename):  # Writefile Function that writes the functionality onto the output file.
    outputFile = open(outputFilename, "w")
    for line in listOfWords:
        # Line[0] is the string
        # Line[1] is the number of each line
        print((line[0] + "\n") * int(line[1]), file=outputFile, end="")
    outputFile.close()


main()  # Call to main
