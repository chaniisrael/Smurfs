#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "ButtonType.h"
#include "Resources.h"
#include "ExitGame.h"
#include "NewGame.h"
#include "Const.h"
using std::vector;

class Menu
{
public:
	Menu();
	~Menu() = default;
	void CheckMenuEvents(sf::RenderWindow& window);
	void drawMenuWindow(sf::RenderWindow& window);
	void handleClick(bool& isButtonPressed, const sf::Event::MouseButtonEvent& event, sf::RenderWindow& window);

protected:
	sf::Sprite m_sprite;
	vector  <std::unique_ptr<ButtonType>> m_menu;
};