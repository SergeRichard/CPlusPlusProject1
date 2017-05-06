#pragma once
#include "Room.h"
#include <iostream>
#include <vector>
#include <string>

class Area
{
public:
	Area(std::string name);
	~Area();

	void InitRoom(std::string name);

private:
	std::string m_name;
	std::vector<Room> rooms;
};

