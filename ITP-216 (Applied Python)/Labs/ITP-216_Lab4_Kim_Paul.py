# Paul Kim, Lab 4, Tuesday 7-8:50 PM Section
# pbkim@usc.edu
# Lab 4 - Ew, a bug

import random  # To generate random number

"""
Create a class called Arthropod which has the attributes and methods described in the requirements.

Assignment has no actual output. However, encouraged to test your class by making an instance
of it and calling its various methods
"""


class Arthropod:
    """ Arthropod Class that has attributes and methods described in the requirements"""
    arthropod_count = 0  # Total Count of objects instantiated

    'Constructor'

    def __init__(self, name_param, color_param, limbs_count_param):
        self.name = name_param
        self.limbs = limbs_count_param
        self.color = color_param
        Arthropod.arthropod_count += 1

    'Returns Name'

    def get_name(self):
        return self.name

    'Returns Color'

    def get_color(self):
        return self.color

    'Returns Number of Limbs'

    def get_limbs_count(self):
        return self.limbs

    "Change Arthropod's Color'"

    def set_color(self, newColor):
        self.color = newColor

    "Generate random number of limbs between 0 and # of limbs"
    "Lose that number of limbs and update limbs count"

    def lose_fight(self):
        currLimbs = self.limbs
        randomLoss = random.randint(0, currLimbs)
        self.limbs = currLimbs - randomLoss


# Main Function (Tests)
def main():
    a = Arthropod("Tommy", "Red", 4)
    print(a.get_name())
    print(a.get_color())
    print(a.get_limbs_count())
    print()

    b = Arthropod("John", "Blue", 3)
    print(b.get_name())
    print(b.get_color())
    print(b.get_limbs_count())
    print()

    b.set_color("Orange")
    print(b.get_color())
    b.lose_fight()
    print(b.get_limbs_count())
    print()

    COUNT = Arthropod.arthropod_count
    print(COUNT)
    print()

    c = Arthropod("Tim", "Yellow", 14)
    print(c.get_name())
    print(c.get_color())
    print(c.get_limbs_count())
    c.lose_fight()
    print(c.get_limbs_count())
    print()

    COUNT = Arthropod.arthropod_count
    print(COUNT)
    print()


# Call to Main
if __name__ == '__main__':
    main()
