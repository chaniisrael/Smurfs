#include "ScoreGift.h"
#include "Board.h"

//--------------------------------------------------------------------------------------------------------------
ScoreGift::ScoreGift(sf::Vector2f location, int width, int height) :
	GiftType(gift, location, width, height)
{
}
namesOfObjects ScoreGift::collide(Player& player)
{
	player.setScore(3 * player.numOfLevel());
	return gift;
}
void ScoreGift::collide(MonsterType& monster)
{
}
//--------------------------------------------------------------------------------------------------------------

