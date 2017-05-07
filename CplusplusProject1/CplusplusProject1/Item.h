#pragma once
#include <string>
#include <iostream>

struct Item
{
	Item() {};
	Item(std::string name, std::string desc) : name(name), description(desc) {};

	~Item() {};

	std::string name;
	std::string description;
};

