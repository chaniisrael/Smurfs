#include "Rod.h"
#include "Board.h"

//--------------------------------------------------------------------------------------------------------------
//c-tor
Rod::Rod(sf::Vector2f location, int width, int height) :
	StaticObject(rod, location, width, height)
{
}
namesOfObjects Rod::collide(Player& player)
{
	return rod;
}
void Rod::collide(MonsterType& monster)
{
}
//--------------------------------------------------------------------------------------------------------------
