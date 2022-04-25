# Paul Kim, HW 4, Tuesday 7-8:50 PM Section, Spring 2022
# pbkim@usc.edu
# HW 5 - Sports!


from athlete.Athlete import Athlete


# Swimmer Class
class Swimmer(Athlete):
    """ Swimmer Class that has attributes and methods described in the requirements"""
    swimmer_count = 0

    'Constructor for Swimmer Class'

    def __init__(self, name_param, dob, origin, medals, strokes):
        super().__init__(name_param, dob, origin, medals)
        self.strokes = strokes  # List
        Swimmer.swimmer_count += 1

    'Returns data about the Swimmer when printing'

    def __str__(self):
        return self.name + " is a swimmer from " + self.origin + " born on " + self.dob + ". " + self.name + " knows " + str(
            self.strokes) + ", and has won " + str(len(self.medals)) + " medals: " + str(self.medals) + "."

    'Returns Stroke'

    def get_strokes(self):
        return self.strokes

    'Adds Stroke'

    def add_stroke(self, stroke1):
        self.strokes.append(stroke1)
