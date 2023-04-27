#pragma once
#include "DinamicObject.h"
#include "Player.h"

class MonsterType : public DinamicObject
{
public:
	MonsterType(const namesOfObjects index, sf::Vector2f location, int width, int height);
	~MonsterType() = default;
	virtual void move(sf::Time deltaTime) = 0;
    virtual void collide(Player& player);
	void setIfWall(int ifWall);


protected:

};