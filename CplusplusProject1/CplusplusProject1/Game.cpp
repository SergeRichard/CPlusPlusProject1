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

	Area insideCell(true);
	insideCell.AddItem(item1);
	insideCell.AddItem(item2);
	
	Area outsideCell(false);
	outsideCell.AddItem(item3);

	Area stairwell(false);

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
	}
	if (firstWord == "look") {
		if (secondWord == "inventory") {
			std::cout << "Inventory: ";
			std::vector<Item> items = m_player.GetInventory();
			for (int i = 0; i < items.size(); ++i) {
				std::cout << items[i].name << (i != items.size() - 1 ? ", " : ".");
			}
			std::cout << std::endl;
		}
	}
	if (firstWord == "get") {
		if (secondWord == "keys") {
			if (m_state == States::InsideCell && m_areasMap[States::InsideCell].IsLocked() == true) {
				for (auto i : m_player.GetInventory()) {
					if (i.name == "Stick") {
						for (auto a : m_areasMap[States::OutsideCell].GetItems())
						{
							if (a.name == "Keys") {
								std::cout << "You reach out through the bars with the stick and hook on to key ring pulling it back inside the cell. You now have the cell keys." << std::endl;
								m_player.AddItemToInventory(m_areasMap[States::OutsideCell].RemoveItem("Keys"));
							}
						}						
					}
					else {
						std::cout << "Keys are too far. Maybe a certain long object might help..." << std::endl;
					}
				}				
			}
		}
		if (secondWord == "stick") {
			for (auto a : m_areasMap[m_state].GetItems())
			{
				if (a.name == "Stick") {
					std::cout << "You get the stick." << std::endl;
					m_player.AddItemToInventory(m_areasMap[m_state].RemoveItem("Stick"));
				}
			}
		}
		if (secondWord == "rock") {
			for (auto a : m_areasMap[m_state].GetItems())
			{
				if (a.name == "Rock") {
					std::cout << "You get the rock." << std::endl;
					m_player.AddItemToInventory(m_areasMap[m_state].RemoveItem("Rock"));
				}
			}

		}
	}
}

void Game::DisplayAreaDescription() {
	switch (m_state) {
	case States::InsideCell:
		std::cout << m_strings["InACell"] << std::endl << std::endl;
		std::cout << "You see: " << m_areasMap[States::InsideCell] << std::endl << std::endl;
		break;
	case States::OutsideCell:

		break;
	case States::Stairwell:
		break;
	}

}
