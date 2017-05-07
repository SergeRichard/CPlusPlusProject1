#include "Game.h"

Game::Game() : m_state(States::InsideCell)
{
	m_strings = m_XMLFetcher.GetStrings();

	std::cout << m_strings["WelcomeMessage"] << std::endl << std::endl;

	CreateAreas();


	DisplayAreaDescription();
}


Game::~Game()
{
}
void Game::CreateAreas() {
	Item item1("Stick", "It's a really long dirty old stick.");
	Item item2("Rock", "Nothing special. Just a medium size rock. Good for throwing...");
	Item item3("Keys", "Ring with keys on it.");

	Area insideCell;
	insideCell.AddItem(item1);
	insideCell.AddItem(item2);
	
	Area outsideCell;
	outsideCell.AddItem(item3);

	Area stairwell;

	m_areasMap[States::InsideCell] = insideCell;
	m_areasMap[States::OutsideCell] = outsideCell;
	m_areasMap[States::Stairwell] = stairwell;

	//Area area("");

}
void Game::PlayerInput() {
	std::string command;

	std::cout << "> ";
	std::getline(std::cin, command);

	ProcessCommand(command);
}
void Game::ProcessCommand(std::string command) {
	std::size_t endFirstWord = command.find(' ');
	std::size_t endSecondWord = command.find(' ', endFirstWord + 1);
	
	std::string firstWord = command.substr(0, endFirstWord);
	std::string secondWord = command.substr(endFirstWord + 1, endSecondWord);

	if (command == "look") {
		DisplayAreaDescription();
		ItemsSeen();
	}
	if (firstWord == "look") {

	}
	if (firstWord == "get") {

	}

}
void Game::ItemsSeen() {
	switch (m_state) {
	case States::InsideCell:
		std::cout << "You see: " << m_areasMap[States::InsideCell] << std::endl << std::endl;
		break;
	case States::OutsideCell:

		break;
	case States::Stairwell:
		break;
	}

}
void Game::DisplayAreaDescription() {
	switch (m_state) {
	case States::InsideCell:
		std::cout << m_strings["InACell"] << std::endl << std::endl;
		break;
	case States::OutsideCell:

		break;
	case States::Stairwell:
		break;
	}

}
