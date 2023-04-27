#pragma once
#include "GiftType.h"

class Board;
class ScoreGift : public GiftType
{
public:
	ScoreGift(sf::Vector2f location, int width, int height);
	~ScoreGift() = default;
	virtual namesOfObjects collide(Player& player) override;
	virtual void collide(MonsterType& monster) override;

protected:

};