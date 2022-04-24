#include "inventory.h"
#include <iostream>

Inventory::Inventory()
{
	// nothing to do here
}

/* Add an item to the inventory with the given name and amount. */
void Inventory::addItem(std::string name, int amount)
{
	int i = 0;
	
	while (i < (int)size()) { // Vector class (size of the vector)
		if (at(i).name == name) {
			at(i).amount += amount;
			return;
		}
		else {
			i++;
		}
	}
	push_back(Item(name, amount));
}

/* Remove all items with this name from the inventory. */
void Inventory::removeItem(std::string name)
{
	int i = 0;

	while (i < (int)size()) {
		if (at(i).name == name) {
			erase(this->begin() + i); // Vector syntax
			return;
		}
		else {
			i++;
		}
	}
}

/* Return the number of items with this name from the inventory. */
int Inventory::getNumItems(std::string name)
{
	int i = 0;

	while (i < (int)size()) {
		if (at(i).name == name) {
			return at(i).amount;
		}
		else {
			i++;
		}
	}
	
	return 0;
}

/* Print all the items in this format:
	key value
	key value
	key value
*/
void Inventory::printAllItems()
{
	int i = 0;

	while (i < (int)size()) {
		std::cout << at(i).name << " " << at(i).amount << std::endl;
	}
}
