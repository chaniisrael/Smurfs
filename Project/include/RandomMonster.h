#pragma once
#include "MonsterType.h"

class RandomMonster : public MonsterType
{
public:
	RandomMonster( sf::Vector2f location, int width, int height);
	~RandomMonster() = default;
	virtual void move(sf::Time deltaTime) override;

	//float manhattan…Distance(sf::Vector2f possibleDestigntion);*/

protected:

};