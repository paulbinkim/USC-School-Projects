# Paul Kim
# ITP 116, 10:00-10:50 AM
# Lab 5 - This is a menu-driven program to give information about the World Series
# champions using lists and tuples.

# List of World Series Champions
winners = [(2020, "Dodgers"), (2019, "Nationals"), (2018, "Red Sox"), (2017, "Astros"), (2016, "Cubs"), (2015, "Royals"), (2014, "Giants"), (2013, "Red Sox"), (2012, "Giants"),
           (2011, "Cardinals"), (2010, "Giants"), (2009, "Yankees"), (2008, "Phillies"), (2007, "Red Sox"), (2006, "Cardinals"), (2005, "White Sox"), (2004, "Red Sox"),
           (2003, "Marlins"), (2002, "Angels"), (2001, "Diamondbacks"),(2000, "Yankees")]

# Tuple of Menu Items
menuItems = ("1. Sort By Year", "2. Sort By Team", "3. Get Number of Wins Per Team", "4. Exit")

# Prompt
print("Welcome to the World Series Champions program!")
for item in menuItems:
    print(item)
choice = input("What would you like to do? ")

# Main While Loop
while not choice == "4":
    if choice == "1":  # Algorithm to sort by the year.
        i = 0
        while i < len(winners):  # Bubble Sort
            j = i + 1
            while j < len(winners):
                if winners[i][0] > winners[j][0]:
                    # Swap Statements
                    temp = winners[i]
                    winners[i] = winners[j]
                    winners[j] = temp
                j += 1
            i += 1
        for team in winners:  # Prints the year and the team in sorted order by year.
            print(team[0], team[1])

    elif choice == "2":
        i = 0
        while i < len(winners):
            j = i + 1
            while j < len(winners):
                if winners[i][1] > winners[j][1]:
                    # Swap Statements
                    temp = winners[i]
                    winners[i] = winners[j]
                    winners[j] = temp
                j += 1
            i += 1
        for team in winners:  # Prints the year and the team in sorted order by year.
            print(team[0], team[1])

    elif choice == "3":
        teamList = []  # Create Empty List
        for item in winners:
            teamList.append(item[1])
        teamList.sort()  # Sort Function
        uniqueTeamsList = []
        for team in teamList:
            if team not in uniqueTeamsList:
                uniqueTeamsList.append(team)
        for team in uniqueTeamsList:
            numWins = teamList.count(team)  # Counts how many times team appeared
            print(team, numWins)

    else:
        print("That is not a valid choice.")

    print()  # Extra Line Space

    # Prompt Statement displayed after every loop
    for item in menuItems:
        print(item)
    choice = input("What would you like to do? ")

# End Prompt Statement
print("Thank you for using my program.")