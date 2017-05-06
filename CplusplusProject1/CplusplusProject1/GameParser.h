#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include "HelperFunctions.h"

class GameParser
{
public:
	GameParser();
	~GameParser();

	std::map<std::string, std::string> GetStrings();

private:
	void FetchFromXML();
	void ParseTokens();
	
private:
	std::vector<std::string> m_tokens;
	std::map<std::string, std::string> m_strings;

};

