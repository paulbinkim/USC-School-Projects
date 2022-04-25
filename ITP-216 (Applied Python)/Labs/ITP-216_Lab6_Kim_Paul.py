# Paul Kim, Lab 6, Tuesday 7-8:50 PM Section
# pbkim@usc.edu
# Lab 6 - Numbers and Feathers

"""
Task-list based lab to get you comfortable working with comprehensions and generators
"""

# Comprehension that creates a list (called sevens) consisting of all multiples of seven from 1 to 1000.
sevens = [i for i in range(1, 1000) if i % 7 == 0]
print(len(sevens))  # 142 Items Long
print(sevens)

print()

# Comprehension that creates a dictionary (called birdos) consisting of the following content (paired currently by
# index)

name = ['Great potoo', 'Smew', 'Tundra bean goose', 'Southern pied babbler']
genus_and_species = ['Nyctibius grandis', 'Mergellus albellus', 'Anser serrirostris', 'Turdoides bicolor']

birdos = {key: value for key, value in zip(name, genus_and_species)}
print(birdos)

print()


# Generator expression which creates a generator (called square_gen) which will yield two values: a number and its
# square. You can test it by running the following code:

square_gen = ((number, number*number) for number in range(10))  # square_gen is a list

for number, square in square_gen:
    print(number, 'squared:', square)
