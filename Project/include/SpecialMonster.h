#pragma once
#include "MonsterType.h"
#include "Player.h"

class SpecialMonster : public MonsterType
{
public:
	SpecialMonster(sf::Vector2f location, int width, int height, Player& player);
	~SpecialMonster() = default;
	virtual void move(sf::Time deltaTime) override;
	float manhattan…Distance(sf::Vector2f possibleDestigntion);

protected:
	Player& m_player;
	
};