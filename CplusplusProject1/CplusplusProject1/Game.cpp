#include "Game.h"

Game::Game()
{
	m_strings = m_XMLFetcher.GetStrings();

	std::cout << m_strings["WelcomeMessage"] << std::endl;
}


Game::~Game()
{
}
