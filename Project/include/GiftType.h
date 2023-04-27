#pragma once
#include "StaticObject.h"

class GiftType : public StaticObject
{
public:
	GiftType(const namesOfObjects index, sf::Vector2f location, int width, int height);
	~GiftType() = default;
	virtual namesOfObjects collide(Player& player) = 0;
	virtual void collide(MonsterType& monster) = 0;

protected:

};