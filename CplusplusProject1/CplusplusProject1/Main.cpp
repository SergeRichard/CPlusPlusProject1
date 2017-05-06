#include <iostream>
#include <string>
#include <fstream>
#include "Game.h"
#include "Area.h"
#include "Room.h"
#include <algorithm>
#include <functional> 
#include <cctype>
#include <locale>
#include <string>
#include <queue>
using namespace std;

// trim from start
static inline std::string &ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
}
void ProcessDesc() {


}
void ProcessRoom(queue<string>& commands, vector<Area>& areas) {
	if (commands.front().find("<Room name=") != std::string::npos) {
		std::size_t posStart = commands.front().find("\"");
		std::size_t posEnd = commands.front().find("\"", posStart + 1);
		string name = commands.front().substr(posStart + 1, posEnd - posStart - 1);

		Room room(name);

		areas.front().InitRoom(name);
		commands.pop();

		
	}

	if (commands.front() == "</Room>") {
		commands.pop();
		return;
	}
	else {
		throw exception("Error! Matching end tag expected.");
	}
}
void ProcessArea(queue<string>& commands, vector<Area>& areas) {
	cout << "Processing world" << endl;
	if (commands.front().find("<Area name=") != std::string::npos) {
		std::size_t posStart = commands.front().find("\"");
		std::size_t posEnd = commands.front().find("\"",posStart + 1);
		string name = commands.front().substr(posStart + 1, posEnd - posStart - 1);

		Area area(name);

		areas.push_back(area);
		commands.pop();
	}	
	else {
		throw exception("Error! At least one room is required in an area");
		cout << "Didn't find <Area name=" << endl;
		return;
	}
	while (commands.front().find("<Room name=") != std::string::npos) {
		commands.pop();
		ProcessRoom(commands, areas);
		
	}
	if (commands.front() == "</Area>") {
		return;
	}
	else {
		throw exception("error! Expecting matching end tag.");
	}
}
void ProcessWorld(queue<string>& commands, vector<Area>& areas) {
	if (commands.front() == "<World>") {
		commands.pop();

		ProcessArea(commands, areas);
	}
	else {
		cout << "Error: World expected!" << endl;
		return;
	}

}
int main() 
{
	//Game game;
	//while (true)
	//{
	//	


	//}

	ifstream inFile("Strings.xml");
	string strOneLine;

	queue<string> commands;
	vector<Area> areas;

	if (!inFile) {
		cout << "Can't open file!" << endl;

	}
	// first tag expected is <World>
	while (inFile)
	{
		getline(inFile, strOneLine);
		trim(strOneLine);		
		commands.push(strOneLine);		
	}

	//ProcessWorld(commands, areas);

	inFile.close();

	getchar();

	return 0;


}