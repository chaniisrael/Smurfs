#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Player.h"
#include "Menu.h"

class GameManager
{
public:
	GameManager();
	void run();
	void managesMenu();
	void managesLevels(bool& gameStatus);
	void managesEndOfGame(bool& gameStatus);

private:
	sf::RenderWindow m_window;
	Player m_player;
	Menu m_menu;
};
