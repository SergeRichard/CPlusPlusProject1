#include "GameParser.h"



GameParser::GameParser()
{
}


GameParser::~GameParser()
{
}
std::map<std::string, std::string> GameParser::GetStrings() {
	FetchFromXML();
	ParseTokens();
	return m_strings;
}
void GameParser::FetchFromXML() {
	std::ifstream inFile("Strings.xml");
	std::string strOneLine;

	if (!inFile) {
		std::cout << "Can't open file!" << std::endl;

	}
	// first tag expected is <World>
	if (inFile) {
		do
		{
			getline(inFile, strOneLine);

			trim(strOneLine);
			m_tokens.push_back(strOneLine);

			if (inFile.eof())
				break;

		} while (!inFile.eof());
	}

	inFile.close();

}
void GameParser::ParseTokens() {
	std::string name;
	enum parseState {tag, content, endTag};

	int state = tag;

	std::map<std::string, std::string>::iterator it;


	for(auto token : m_tokens) {
		state %= 3;

		switch (state)
		{
		case tag:
			
			if (token.find("<String name=\"") != std::string::npos) {
				//std::cout << "Found: " << token << std::endl;

				std::size_t start = token.find("\"");
				std::size_t end = token.find("\"", start + 1);
				name = token.substr(start + 1, end - start - 1);

				//std::cout << "name: " << name << std::endl;
				state++;
			}
			else
			{
				std::cout << "Error! Not able to find string tag!" << std::endl;
			}
			break;
		case content:
			m_strings[name] = token;

			state++;
			break;
		case endTag:
			if (token == "</String>") {
				state++;
			}
			else
			{
				std::cout << "Error! Not able to find string tag!" << std::endl;
			}
			break;

		}
	}

}
