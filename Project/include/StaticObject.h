#pragma once
#include "GameObject.h"
#include "Player.h"
#include "MonsterType.h"

class Board;
class StaticObject : public GameObject
{
public:
	StaticObject(const namesOfObjects index, sf::Vector2f location, int width, int height);
	~StaticObject() = default;
	virtual namesOfObjects collide(Player& player) = 0;
	virtual void collide(MonsterType& monster) = 0;

protected:

};