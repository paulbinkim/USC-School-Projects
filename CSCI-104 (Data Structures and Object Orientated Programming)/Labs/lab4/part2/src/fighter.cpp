#include "fighter.h"

using namespace std;

Fighter::Fighter(string name) : Player(name) {
	// nothing to do here
}

void Fighter::doAction(Player *target) {
	if (!target) return;
	target->setHP(target->getHP() - 75);
}