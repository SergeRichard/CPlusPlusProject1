#pragma once

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include "Area.h"
#include "GameParser.h"
#include "HelperFunctions.h"
#include "Item.h"
#include "Player.h"

class Area;

class Game
{
public:
	Game();
	~Game();

	enum class States {InsideCell, OutsideCell, Stairwell};

	void PlayerInput();
	bool GameDone() { return m_gameDone; }
private:
	void DisplayAreaDescription();

	void CreateAreas();
	void ProcessCommand(std::string command);

private:
	std::map<std::string, std::string> m_strings;
	std::map<States, Area> m_areasMap;
	GameParser m_XMLFetcher;
	States m_state;
	Player m_player;
	bool m_gameDone;
	bool m_guardMoved;
};

