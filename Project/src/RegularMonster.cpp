#include "RegularMonster.h"

//--------------------------------------------------------------------------------------------------------------
RegularMonster::RegularMonster(sf::Vector2f location, int width, int height) :
	MonsterType(regularMonster, location, width, height), m_dir({1,0})
{
}
void RegularMonster::move(sf::Time deltaTime)
{
int randomDirection = rand() % 2;
m_nextDirection = checkDirection(Directions(randomDirection));
calculateSpeed(m_nextDirection, MONSTER_SPEED);

isCloseEnoughToAxis(deltaTime);
if (isOutOfLimits((m_direction * deltaTime.asSeconds()) + m_sprite.getPosition()))
m_sprite.move(m_direction * deltaTime.asSeconds());
}
//--------------------------------------------------------------------------------------------------------------

