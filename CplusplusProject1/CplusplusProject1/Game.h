#pragma once

#include <vector>
#include "Area.h"

class Game
{
public:
	Game();
	~Game();

private:
	std::vector<Area> areas;
};

