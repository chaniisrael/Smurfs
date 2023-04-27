#include "Coins.h"
#include "Board.h"

//--------------------------------------------------------------------------------------------------------------
//c-tor
Coins::Coins( sf::Vector2f location, int width, int height) :
	StaticObject(coins, location, width, height)
{
}
namesOfObjects Coins::collide(Player& player)
{
	player.setScore(2 * player.numOfLevel());
	player.setNumOfCoins(-1);
	return coins;
}
void Coins::collide(MonsterType& monster)
{
}
//--------------------------------------------------------------------------------------------------------------
