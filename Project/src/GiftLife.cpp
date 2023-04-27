#include "GiftLife.h"

//--------------------------------------------------------------------------------------------------------------
GiftLife::GiftLife(sf::Vector2f location, int width, int height) :
	GiftType(gift, location, width, height)
{
}
namesOfObjects GiftLife::collide(Player& player)
{
	player.setLife(1);
	return gift;
}
void GiftLife::collide(MonsterType& monster)
{
}
