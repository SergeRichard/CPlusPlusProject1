#pragma once
#include "GameParser.h"
#include <string>

class Room
{
public:
	Room(std::string name);
	~Room();

private:
	std::string m_name;
	

};

