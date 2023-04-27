#include "Scale.h"

Scale::Scale(sf::Vector2f location, int width, int height) :
	StaticObject(scale, location, width, height)
{

}
namesOfObjects Scale::collide(Player& player)
{
	return scale;
}
void Scale::collide(MonsterType& monster)
{
}
//-------------------------------------------------------------------------------------