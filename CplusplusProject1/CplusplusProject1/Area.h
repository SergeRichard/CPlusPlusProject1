#pragma once
#include "Room.h"
#include <iostream>
#include <vector>
#include <string>
#include "Game.h"
#include "Item.h"

class Area
{
public:
	Area();
	~Area();

	void AddItems(std::vector<Item> items);
	void AddItem(Item item);
	bool RemoveItem(std::string name);

	friend std::ostream& operator<< (std::ostream& stream, const Area& area);
	
private:
	std::vector<Item> m_items;
	
};

