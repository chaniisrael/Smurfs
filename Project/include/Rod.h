#pragma once
#include "StaticObject.h"

class Board;
class Rod : public StaticObject
{
public:
	Rod(sf::Vector2f location, int width, int height); //c-tor
	virtual namesOfObjects collide(Player& player) override; //פונקציה שבודקת התנגשות בין שחקן לאבן
	virtual void collide(MonsterType& monster) override; //פונקציה שבודקת התנגשות בין מפלצת למוט

protected:

};