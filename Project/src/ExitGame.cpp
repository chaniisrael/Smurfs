#include "ExitGame.h"
#include <iostream>

//--------------------------------------------------------------------------------------------------------------
ExitGame::ExitGame(sf::Vector2f location) : ButtonType(exitGame, location)
{
}
//--------------------------------------------------------------------------------------------------------------
void ExitGame::handleClick()
{
		exit(0);
}
