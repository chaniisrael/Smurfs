#pragma once
#include "StaticObject.h"

class Wall : public StaticObject
{
public:
	Wall(sf::Vector2f location, int width, int height); //c-tor
	virtual namesOfObjects collide(Player& player) override; //פונקציה שבודקת התנגשות בין שחקן לקיר
	virtual void collide(MonsterType& monster) override; //פונקציה שבודקת התנגשות בין מפלצת לקיר

protected:

};