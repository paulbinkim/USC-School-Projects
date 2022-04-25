# Paul Kim, HW 4, Tuesday 7-8:50 PM Section, Spring 2022
# pbkim@usc.edu
# HW 5 - Sports!

# Athlete Class used in Boxer and Swimmer
class Athlete:
    athlete_count = 0

    "Constructor (new Athlete object)"

    def __init__(self, name_param, dob, origin, medals):
        self.name = name_param  # String
        self.dob = dob  # String
        self.origin = origin  # String
        self.medals = medals  # List
        Athlete.athlete_count += 1

    'Returns Name'

    def get_name(self):
        return self.name

    'Returns Date of Birth'

    def get_dob(self):
        return self.dob

    'Returns Origin'

    def get_origin(self):
        return self.origin

    "Returns Medals"

    def get_medals(self):
        return self.medals

    "Adds Medal to the Medal List"
    def add_medal(self, medal_param):
        self.medals.append(medal_param)


