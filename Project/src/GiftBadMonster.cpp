#include "GiftBadMonster.h"

GiftBadMonster::GiftBadMonster(sf::Vector2f location, int width, int height, vector <std::unique_ptr<MonsterType>>& monsters) :
	GiftType(gift, location, width, height),m_monsters(monsters),m_width(width), m_height(height)
{
}
namesOfObjects GiftBadMonster::collide(Player& player)
{
	sf::Vector2f location = { player.getPosition().x + 3,player.getPosition().y };
	if (player.isOutOfLimits(location))
	{
		int monsterType = rand() % 3;
		if (monsterType == 0)
			m_monsters.push_back(std::make_unique<RegularMonster>(location, m_width, m_height));
		else if (monsterType == 1)
			m_monsters.push_back(std::make_unique<SpecialMonster>(location, m_width, m_height, player));
		else if (monsterType == 2)
			m_monsters.push_back(std::make_unique<RandomMonster>(location, m_width, m_height));
	}

	return gift;
}
void GiftBadMonster::collide(MonsterType& monster)
{
}