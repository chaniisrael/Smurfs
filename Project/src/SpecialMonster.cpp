#include "SpecialMonster.h"
#include <iostream>
#include <iostream>

//--------------------------------------------------------------------------------------------------------------
SpecialMonster::SpecialMonster(sf::Vector2f location, int width, int height, Player& player) :
	MonsterType(specialMonster, location, width, height), m_player(player)
{
}
void SpecialMonster::move(sf::Time deltaTime)
{
	float distanseFromPlayer, minDistanseFromPlayer = 1250;
	sf::Vector2f possibleDestination, direction;
	for (int i = 0; i < NUMBER_OF_DIRECTIONS; i++)
	{
		direction = checkDirection(Directions(i));
		calculateSpeed(direction, MONSTER_SPEED);
		possibleDestination = m_sprite.getPosition() + (direction * (deltaTime.asSeconds()));
		distanseFromPlayer = manhattanÉDistance(possibleDestination);
		 if (distanseFromPlayer < minDistanseFromPlayer)
		{
			m_nextDirection = direction;
			minDistanseFromPlayer = distanseFromPlayer;
			isCloseEnoughToAxis(deltaTime);
		}
		
	}
	if (isOutOfLimits((m_direction * deltaTime.asSeconds()) + m_sprite.getPosition()))
		m_sprite.move(m_direction * deltaTime.asSeconds());

}
//--------------------------------------------------------------------------------------------------------------
float SpecialMonster::manhattanÉDistance(sf::Vector2f possibleDestigntion)
{
	return (std::abs(possibleDestigntion.x - (m_player.getPosition()).x) +
		std::abs(possibleDestigntion.y - (m_player.getPosition()).y));
}
//-----------------------------------------------------------------------------------------------------------
