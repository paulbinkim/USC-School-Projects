# Paul Kim, HW 4, Tuesday 7-8:50 PM Section, Spring 2022
# pbkim@usc.edu
# HW 5 - Sports!

# Importing Package/Module to create Boxer and Swimmer Class
from athlete.Boxer import Boxer
from athlete.Swimmer import Swimmer


# Main Function (Test Output)
def main():
    # Mary Berry Object
    MaryBerry = Boxer("Mary Berry", "1935/03/24", "UK", ["Gold(2012)", "Gold(2016)"], "Light Flyweight")
    # MaryBerry.win_fight()
    # MaryBerry.lose_fight()
    print(MaryBerry)

    # Dave Thomas Object
    DaveThomas = Swimmer("Dave Thomas", "1932/07/02", "USA", ['Silver (1992)', 'Gold (1996)'],
                         ['freestyle', 'breaststroke'])
    # DaveThomas.add_stroke("Swimmah")
    print(DaveThomas)


if __name__ == '__main__':
    main()
