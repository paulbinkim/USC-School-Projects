# Paul Kim, HW 4, Tuesday 7-8:50 PM Section, Spring 2022
# pbkim@usc.edu
# HW 4 - Gross, more bugs


from Arthropod import Arthropod
import random


class Insect(Arthropod):
    """ Insect Class that has attributes and methods described in the requirements"""
    insect_count = 0

    'Constructor for Insect Class'

    def __init__(self, name_param, color_param, limbs_count_param, wings_count_param):
        super().__init__(name_param, color_param, limbs_count_param)
        self.wings_count = wings_count_param
        Insect.insect_count += 1

    'Returns data about the Insect when printing'

    def __str__(self):
        return 'The ' + self.color + ' ' + self.name + ' has ' + str(self.limbs) + ' limbs and ' + str(
            self.wings_count) + ' wings.'

    'Returns Wings Count'

    def get_wings_count(self):
        return self.wings_count

    'Returns Insect Power'

    def get_power(self):
        return self.limbs + self.wings_count

    "Generate random number of limbs between 0 and # of limbs"
    "Generate random number of wings between 0 and # of wings"
    "Lose that number of limbs and wings and update both counts"

    def lose_fight(self):
        super().lose_fight()

        currWings = self.wings_count
        randomLossWings = random.randint(0, currWings)
        self.limbs = currWings - randomLossWings
