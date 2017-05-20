#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

bool Player::ObjectInInventory(std::string object) {

	for (Item item : inventory) {
		if (item.name == object)
			return true;
	}
	return false;
}