#include "Wall.h"
#include "Board.h"

//--------------------------------------------------------------------------------------------------------------
//c-tor
Wall::Wall(sf::Vector2f location, int width, int height):
StaticObject(wall, location, width, height)
{
}

namesOfObjects Wall::collide(Player& player)
{
	player.setDirection({ 0,0 }); //עוצר את השחקן במקום
	return wall;
}

void Wall::collide(MonsterType& monster)
{
	monster.setPosition();
}
