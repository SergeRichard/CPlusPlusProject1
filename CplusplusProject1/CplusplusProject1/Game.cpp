#include "Game.h"

Game::Game() : m_state(States::InsideCell), m_gameDone(false), m_guardMoved(false)
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
				bool itemFound = false;
				for (auto i : m_player.GetInventory()) {		
					if (itemFound)
						break;
					if (i.name == "Stick") {
						for (auto a : m_areasMap[States::OutsideCell].GetItems())
						{
							if (a.name == "Keys") {
								std::cout << "You reach out through the bars with the stick and hook on to key ring pulling it back inside the cell. You now have the cell keys." << std::endl;
								m_player.AddItemToInventory(m_areasMap[States::OutsideCell].RemoveItem("Keys"));
								itemFound = true;
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
	if (firstWord == "unlock") {
		if (secondWord == "cell") {
			for (auto i : m_player.GetInventory()) {
				if (i.name == "Keys") {
					if (m_areasMap[m_state].IsLocked() == true) {
						std::cout << "You unlock the cell door." << std::endl;
						m_areasMap[m_state].SetLock(false);
					}
					else {
						std::cout << "Cell door is already unlocked." << std::endl;
					}
				}
			}
		}
	}
	if (firstWord == "leave") {
		if (secondWord == "cell") {
			if (m_areasMap[m_state].IsLocked() == false) {
				std::cout << "You go to leave the cell, before you do though, the guard wakes up!";
				if (m_player.ObjectInInventory("Rock")) {
					std::cout << " You throw the rock at the guard's head and knock him out. You step out of the cell." << std::endl << std::endl;
					m_state = States::OutsideCell;
					DisplayAreaDescription();
				}
				else {
					std::cout << " The guard pulls his gun and shoots you. You die. Game over." << std::endl;
					m_gameDone = true;
				}
			}
		}
	}
	if (firstWord == "move") {
		if (secondWord == "guard" && m_state == States::OutsideCell) {
			std::cout << "\nWhere to? ";
			std::string location;
			std::cin >> location;

			if (location == "cell") {
				std::cout << "You move guard inside the cell and make sure to lock it." << std::endl;
				m_guardMoved = true;
			}
		}
	}
	if (firstWord == "go") {
		if (secondWord == "north" && m_state == States::OutsideCell) {
			m_state = States::Stairwell;
			if (!m_guardMoved) {
				std::cout << "Alarm sounds and in no time guards are coming from above and below the stairwell. You are forced to surrender. Game over." << std::endl;
				m_gameDone = true;
			}
			else {
				std::cout << std::endl;
				DisplayAreaDescription();
			}
		}
		if (secondWord == "down" && m_state == States::Stairwell) {
			
			std::cout << m_strings["ExitDoor"] << std::endl;
			m_gameDone = true;

		}
		if (secondWord == "up" && m_state == States::Stairwell) {
			std::cout << "\nYou arrive at a door. Do you open the door or climb down the stairwell to where you were at?" << std::endl;
			std::cout << "(type 'yes' to open door, or 'no' to climb down) ";
			std::string decision;
			std::cin >> decision;
			if (decision == "yes") {
				std::cout << "You enter a room full of guards. You try to leave, but the door is locked behind. the four guards pull there guns and you are forced to surrender. Game over." << std::endl;
				m_gameDone = true;
			}
			else {
				m_state = States::Stairwell;
				std::cout << std::endl;
				DisplayAreaDescription();
			}
		}

	}
}

void Game::DisplayAreaDescription() {
	switch (m_state) {
	case States::InsideCell:
		std::cout << m_strings["InACell"] << std::endl << std::endl;
		std::cout << "You see: " << m_areasMap[States::InsideCell] << std::endl << std::endl;
		std::cout << "Obvious locations: None." << std::endl << std::endl;
		break;
	case States::OutsideCell:
		std::cout << m_strings["OutsideTheCell"] << std::endl << std::endl;
		std::cout << "You see: " << m_areasMap[States::OutsideCell] << std::endl << std::endl;
		std::cout << "Obvious locations: North." << std::endl << std::endl;
		break;
	case States::Stairwell:
		std::cout << m_strings["AtAStairwell"] << std::endl << std::endl;
		std::cout << "You see: " << m_areasMap[States::Stairwell] << std::endl << std::endl;
		std::cout << "Obvious locations: Up, Down." << std::endl << std::endl;
		break;
	}

}
