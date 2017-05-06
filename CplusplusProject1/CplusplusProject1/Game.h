#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "Area.h"
#include "GameParser.h"
#include "HelperFunctions.h"

class Game
{
public:
	Game();
	~Game();



private:
	std::vector<Area> areas;
	std::map<std::string, std::string> m_strings;
	GameParser m_XMLFetcher;
};

