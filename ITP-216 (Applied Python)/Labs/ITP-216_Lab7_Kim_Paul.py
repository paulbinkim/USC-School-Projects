# Paul Kim, Lab 7, Tuesday 7-8:50 PM Section
# pbkim@usc.edu
# Lab 7 - It's a Piece of Cake

# Task Based Lab to get comfortable with decorators.

# Decorator Function which validates input
def validator_decorator(func):
    def wrapper(*args, **kwargs):
        print("Testing arguments:")

        arg_types = [type(arg) for arg in args]
        arg_flags = [arg_type == str for arg_type in arg_types]

        if False in arg_flags or len(kwargs) != 2:
            if False in arg_flags:
                print('\tArguments rejected: not all args are strings.')
            if len(kwargs) != 2:
                print('\tArguments rejected: not all kwargs have two key:value pairs.')

        else:
            print("\tArguments accepted: all args are Strings, and all kwargs are dictionaries with two k:v pairs.")

        print('Printing args:')

        for arg in args:
            print('\t', arg)

        print("Printing kwargs:")
        print('\tanimal:', kwargs)

        print("Running function:", end='\n\n')
        func(*args, **kwargs)

    return wrapper


# Function to be decorated
@validator_decorator
def print_all_the_things(*args, **kwargs):
    print("This will print all the things:", end='\n\t')
    print(*args)
    for kwarg in kwargs:
        print('\t', kwarg, ": ", kwargs[kwarg], sep='')


# Main Function
def main():
    print_all_the_things("Another", "lab", "involving", "animals.", cat=True, dog=False)
    print()
    print("--------------------------------")
    print()
    print_all_the_things("Never", "Eat", "Shredded", "Wheat", cat=True, dog=False, hamster='never')


# Call to Main
if __name__ == '__main__':
    main()