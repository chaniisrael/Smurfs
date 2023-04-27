#include "Menu.h"
#include <iostream>

//--------------------------------------------------------------------------------------------------------------
Menu::Menu() : m_sprite(Resources::getInstance().m_images[menuScreen])
{
	m_menu.push_back(std::make_unique<NewGame>(sf::Vector2f(40, 310)));
	m_menu.push_back(std::make_unique<ExitGame>(sf::Vector2f(40, 440)));
}
//--------------------------------------------------------------------------------------------------------------
void Menu::CheckMenuEvents(sf::RenderWindow& window)
{
	while (true)
	{
		if (auto event = sf::Event{}; window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::MouseButtonReleased:   
			{
				bool isButtonPressed = false;
				handleClick(isButtonPressed, event.mouseButton, window);
				if (isButtonPressed)
					return;
				break;
			}
			case sf::Event::Closed:
				window.close();
				exit(0);
				break;
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------------------
void Menu::drawMenuWindow(sf::RenderWindow& window)
{
	window.draw(m_sprite); //ציור הרקע
	for (const auto& button : m_menu) //ציור הכפתורים על התמונה
		button->drawOnWindow(window);
}
//--------------------------------------------------------------------------------------------------------------
void Menu::handleClick(bool& isButtonPressed, const sf::Event::MouseButtonEvent& event, sf::RenderWindow& window)
{
	for (const auto&button : m_menu)//מעבר על ווקטור הכפתורים
		if (button->isContain(isButtonPressed, event, window))
		{
			button->handleClick();//פונקציה שהמתפלת בלחיצה 
		}
}
