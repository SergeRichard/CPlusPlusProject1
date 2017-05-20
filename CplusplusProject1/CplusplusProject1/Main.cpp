#include <iostream>
#include <string>
#include "Game.h"

int main() 
{
	Game game;
	while (true)
	{
		game.PlayerInput();
		if (game.GameDone())
			break;
	}



	getchar();

	return 0;


}