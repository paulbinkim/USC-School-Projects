# Paul Kim, HW 4, Tuesday 7-8:50 PM Section, Spring 2022
# pbkim@usc.edu
# HW 5 - Sports!

from athlete.Athlete import Athlete


# Boxer Class
class Boxer(Athlete):
    """ Boxer Class that has attributes and methods described in the requirements"""
    boxer_count = 0

    'Constructor for Boxer Class'

    def __init__(self, name_param, dob, origin, medals, weight_class):
        super().__init__(name_param, dob, origin, medals)
        self.weight_class = weight_class  # String
        self.record = [0, 0]  # Initialize Record List
        Boxer.boxer_count += 1

    'Returns data about the Boxer when printing'

    def __str__(self):
        win = self.record[0]
        loss = self.record[1]
        return self.name + " is a " + self.weight_class + " boxer from " + self.origin + " born on " + self.dob + ". " + self.name + " has a " + str(win)+"-"+str(loss) + " record, and has won " + str(len(self.medals)) + " medals: " + str(self.medals) + "."

    'Returns Weight Class'

    def get_weight_class(self):
        return self.weight_class

    'Returns Record'

    def get_record(self):
        return self.record

    'Sets Weight Class'

    def set_weight_class(self, weight_class_param):
        self.weight_class = weight_class_param

    'Add 1 to the wins of the boxers record'

    def win_fight(self):
        self.record[0] += 1

    'Add 1 to the losses of the boxers record, then check to see if the boxer needs to retire'

    def lose_fight(self):
        self.record[1] += 1
        if self.record[1] >= 10:
            return "This boxer has retired"
        else:
            return "The fighter has " + 10-self.record[1] + " fights left before retirement."
