#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Item.h"

class Player
{
public:
	Player();
	~Player();

	void AddItemToInventory(Item item) { inventory.push_back(item); }
	std::vector<Item> GetInventory() { return inventory; }
	bool ObjectInInventory(std::string object);

private:

	std::vector<Item> inventory;
};

