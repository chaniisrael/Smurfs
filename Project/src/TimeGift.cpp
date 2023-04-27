#include "TimeGift.h"
#include "Board.h"

//--------------------------------------------------------------------------------------------------------------
TimeGift::TimeGift(sf::Vector2f location, int width, int height) :
	GiftType(gift, location, width, height)
{
}
namesOfObjects TimeGift::collide(Player& player)
{
	player.setTime(15);
	return gift;
}
void TimeGift::collide(MonsterType& monster)
{
}
//--------------------------------------------------------------------------------------------------------------

