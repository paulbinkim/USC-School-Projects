# Paul Kim, HW 4, Tuesday 7-8:50 PM Section, Spring 2022
# pbkim@usc.edu
# HW 4 - Gross, more bugs


import random


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
