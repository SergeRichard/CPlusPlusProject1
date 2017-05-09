#pragma once
#include "Room.h"
#include <iostream>
#include <vector>
#include <string>
#include "Game.h"
#include "Item.h"

struct Item;

class Area
{
public:
	Area();
	Area(bool locked);
	~Area();

	void AddItems(std::vector<Item> items);
	void AddItem(Item item);
	Item RemoveItem(std::string name);
	bool IsLocked() { return m_locked; }
	std::vector<Item> GetItems() { return m_items; }

	friend std::ostream& operator<< (std::ostream& stream, const Area& area);
	
private:
	std::vector<Item> m_items;
	bool m_locked;
};

