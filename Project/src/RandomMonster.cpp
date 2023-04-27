#include "RandomMonster.h"

RandomMonster::RandomMonster(sf::Vector2f location, int width, int height) :
	MonsterType(randomMonster, location, width, height)
{
}
void RandomMonster::move(sf::Time deltaTime)
{
	
	int randomDirection = rand() % 4;
	m_nextDirection = checkDirection(Directions(randomDirection));
	calculateSpeed(m_nextDirection, MONSTER_SPEED);

	isCloseEnoughToAxis(deltaTime);
	if (isOutOfLimits((m_direction * deltaTime.asSeconds()) + m_sprite.getPosition()))
		m_sprite.move(m_direction * deltaTime.asSeconds());
}
//--------------------------------------------------------------------------------------------------------------




