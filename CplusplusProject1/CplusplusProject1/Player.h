#pragma once

#include <iostream>
#include <vector>
#include <string>

class Player
{
public:
	Player();
	~Player();

	void AddItemToInventory(std::string item) { inventory.push_back(item); }
	std::vector<std::string> GetInventory() { return inventory; }

private:

	std::vector<std::string> inventory;
};

