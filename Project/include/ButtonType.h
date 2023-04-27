#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "Const.h"

class ButtonType
{
public:
	ButtonType(const namesOfObjects index, sf::Vector2f location); //c-tor
	void drawOnWindow(sf::RenderWindow& window); //פונקציה שמציגה את התפריט על המסך
	virtual void handleClick() = 0; //פונקציה שמקבלת ומטפלת באירוע של לחיצת כפתור
	bool isContain(bool& isButtonPressed, const sf::Event::MouseButtonEvent& event, sf::RenderWindow& window); //פונקציה שבודקת אם הלחיצה נעשתה על הכפתור
	sf::Sprite getSprite(); //פונקציה שמחזירה את התמונה

protected:
	sf::Sprite m_sprite; //משתנה ששומר את התמונות
};