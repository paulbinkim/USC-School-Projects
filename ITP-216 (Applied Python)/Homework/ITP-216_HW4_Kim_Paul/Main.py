# Paul Kim, HW 4, Tuesday 7-8:50 PM Section, Spring 2022
# pbkim@usc.edu
# HW 4 - Gross, more bugs

from Arthropod import Arthropod
from Insect import Insect
from Crustacean import Arachnid

"""
Create a very bad ripoff of Pokemon. Using the Arthropod class you wrote in the lab, write
two more classes which inherit from it:

Arachnid -- venomous arthropods.
    - Their power is based on the number of limbs they have, If they are venomous, their power is doubled.
    
Insect -- arthropods with wings.
    - Their power is based on the number of current limbs plus the number of current wings they have
    
During a match:
    1. Several rounds of fights
    2. Each arthropod's strike will be based on their power
    3. When they lose a fight, they must also lose a random number of limbs and/or wings
    4. If any point, one of the arthropod's power is reduced to 0, the fight is over and the winner is the
       arthropod with any power remaining
"""


def main():
    """Test CODE (Commented out, but can uncomment to check functionality"""

    # arhtro1 = Arthropod("Tommy", "red", 4)
    # print(arhtro1.get_name())
    # print(arhtro1.get_color())
    # print(arhtro1.get_limbs_count())
    # print()
    #
    # arachnid1 = Arachnid("Charlie", "silver", 16, False)
    # print(arachnid1.get_name())
    # print(arachnid1.get_color())
    # print(arachnid1.get_limbs_count())
    # print(arachnid1.get_venomous())
    # print(arachnid1.get_power())
    # print(arachnid1)
    # print()
    #
    # insect1 = Insect("Ryan", "blue", 4, 6)
    # print(insect1.get_name())
    # print(insect1.get_color())
    # print(insect1.get_limbs_count())
    # print(insect1.get_wings_count())
    # print(insect1.get_power())
    # insect1.lose_fight()
    # print(insect1)
    # print()
    #
    # COUNT = Arthropod.arthropod_count
    # print(COUNT)
    # COUNT = Arachnid.arachnid_count
    # print(COUNT)
    # COUNT = Insect.insect_count
    # print(COUNT)


if __name__ == '__main__':
    main()
