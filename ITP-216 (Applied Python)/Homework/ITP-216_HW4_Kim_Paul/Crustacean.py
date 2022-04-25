# Paul Kim, HW 4, Tuesday 7-8:50 PM Section, Spring 2022
# pbkim@usc.edu
# HW 4 - Gross, more bugs


from Arthropod import Arthropod  # Importing File


class Arachnid(Arthropod):
    """ Arachnid Class that has attributes and methods described in the requirements"""
    arachnid_count = 0

    'Constructor for Arachnid Class'

    def __init__(self, name_param, color_param, limbs_count_param, venomous_param):
        super().__init__(name_param, color_param, limbs_count_param)
        self.venomous = venomous_param
        Arachnid.arachnid_count += 1

    'Returns data about the Arachnid when printing'

    def __str__(self):
        if self.venomous:
            string1 = "venomous"
        else:
            string1 = "non-venomous"
        return 'The ' + self.color + ' ' + string1 + ' ' + self.name + ' has ' + str(self.limbs) + ' limbs.'

    'Returns Venomous State'

    def get_venomous(self):
        return self.venomous

    'Returns Arachnid Power'

    def get_power(self):
        if self.venomous:
            return self.limbs * 2
        else:
            return self.limbs
