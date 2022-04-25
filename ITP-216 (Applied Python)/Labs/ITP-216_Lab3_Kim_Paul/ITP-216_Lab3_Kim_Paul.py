# Paul Kim, Lab 3, Tuesday 7 - 8:50 PM Section
# pbkim@usc.edu
# Lab 3 - The Oscars

"""
Write a program which reads the contents of a text file into several variables.
It will then print all that data out, line by line. You must do this by writing two functions:
One retrieving the header, and the other retrieving of the data.

NO USER INPUT

* Given a CSV File "oscar_age_female.csv"
"""

'''
Description: Retrieves the first line from a text file
Parameter: FileName (String)
Return Value: The first line of the file (String)
'''


def file_read_header(FileName):
    with open(FileName) as f:  # Open File
        FirstLine = f.readline()  # Read First Line
    return FirstLine  # Return String


'''
Description: Retrieves all data from a text file except the first line
Parameter: FileName (String)
Return Value: All the data from the file except for the first line (String)
'''


def file_read_data(FileName):
    Data = ""
    with open(FileName) as f:  # Open File
        next(f)  # skips first line
        Lines = f.readlines()  # Read entire file
        for line in Lines:  # Iterate through file
            Data += "\t" + line  # I could return a list, but I think this is way easier and efficient

    return Data  # Return tabulated string


'''
Description: Primary entrypoint to codebase.
Parameter: 0
Return Value: 0
'''


def main():
    Header = file_read_header("oscar_age_female.csv")  # Call to obtain Header
    print("Header:")
    print("\t" + Header, end="")  # To remove newline

    Data = file_read_data("oscar_age_female.csv")  # Call to obtain Data
    print("Data:")
    print(Data, end="")


if __name__ == '__main__':
    main()