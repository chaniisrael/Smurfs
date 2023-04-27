#include "MonsterType.h"

//--------------------------------------------------------------------------------------------------------------
MonsterType::MonsterType(const namesOfObjects index, sf::Vector2f location, int width, int height) :
	DinamicObject(index, location, width, height)
{
	
}
//--------------------------------------------------------------------------------
void MonsterType::collide(Player& player)
{
	
	if (player.getLife() != 0)
	{
		player.setLife(-1);
		player.getStartPosition();
		this->getStartPosition();
	}

}
//------------------------------------------------------------------------------------------------------
