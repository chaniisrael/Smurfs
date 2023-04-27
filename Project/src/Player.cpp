#include "Player.h"
#include <iostream>
#include <iostream>

//--------------------------------------------------------------------------------------------------------------
//c-tor
Player::Player(): m_life(TOTAL_LIFE), m_score(0), m_numOfCoins(0), m_deleteCellZ(false),m_deleteCellX(false)
{
}

//--------------------------------------------------------------------------------------------------------------
void Player::setPlayer(const namesOfObjects index, sf::Vector2f location, int width, int height, sf::Vector2f direction, int time, const int& numOfLevel)
{
	m_sprite.setTexture(Resources::getInstance().m_images[player]);
	setObjet(location, width, height);
	m_direction = direction;
	m_startPosition = location;
	m_location= location;
	m_time = time;
	m_timeeee = time;
	m_numOfLevel =numOfLevel;
	
}
//--------------------------------------------------------------------------------------------------------------
//פונקציה שמטפלת בלחיצות של שחקן
void Player::handleEvent(sf::Keyboard::Key key, bool& IfScale, bool& IfEmpty)
{
	switch (key)
	{
	case sf::Keyboard::Key::Space:
		if (m_direction.x != 0)
			setNextDirectionByRows();
		else if (m_direction.y != 0)
			setNextDirectionByColumns();
		m_nextDirection = { 0, 0 };
		break;
	case sf::Keyboard::Key::Left:
		m_nextDirection = checkDirection(Directions(key - 71));
		calculateSpeed(m_nextDirection, PLAYER_SPEED);
		break;
	case sf::Keyboard::Key::Right:
			m_nextDirection = checkDirection(Directions(key - 71));
			calculateSpeed(m_nextDirection, PLAYER_SPEED);
			
		break;
	case sf::Keyboard::Key::Up:
		if (IfScale)
		{
			m_nextDirection = checkDirection(Directions(key - 71));
			calculateSpeed(m_nextDirection, PLAYER_SPEED);
	     }
		break;
	case sf::Keyboard::Key::Down:
		if (IfScale || IfEmpty)
		{ 
		m_nextDirection = checkDirection(Directions(key - 71));
		calculateSpeed(m_nextDirection, PLAYER_SPEED);
		}
		break;
	case sf::Keyboard::Key::Z:
		m_deleteCellZ = true;
		break;
	case sf::Keyboard::Key::X:
		m_deleteCellX = true;
		break;
	
	}
}
//--------------------------------------------------------------------------------------------------------------
//תזוזה
void Player::move(sf::Time deltaTime)
{
	isCloseEnoughToAxis(deltaTime);
	if (isOutOfLimits((m_direction * deltaTime.asSeconds()) + m_sprite.getPosition()))
		m_sprite.move(m_direction * deltaTime.asSeconds());
}
//--------------------------------------------------------------------------------------------------------------
sf::Vector2f Player::getPosition() const
{
	return m_sprite.getPosition();
}
//-------------------------------------------
void Player::startPosition()
{
	m_location = m_startPosition;
}
//-------------------------------------------
bool Player::isAteAllCoins()
{
	return false;
}
//-------------------------------------------
int Player::getNumOfCoins()const
{
	return m_numOfCoins;
}
//-------------------------------------------
void Player::setNumOfCoins(int num)
{
	m_numOfCoins += num;
}
//-------------------------------------------
int Player::getScore() const
{
	return m_score;
}
//-------------------------------------------
void Player::setScore(int score)
{
	m_score += score;
}
//-------------------------------------------
void Player::setLife(int num)
{
	m_life += num;
}
//-------------------------------------------
int Player::getLife()const
{
	return m_life;
}
//-------------------------------------------
int Player::getTime()const
{
	return m_time;
}
//-------------------------------------------
void Player::setTime(int num)
{
	m_time += num;
}

//-------------------------------------------
int Player::numOfLevel()
{
	return m_numOfLevel;
}
//-------------------------------------------
bool Player::getDeleteCellX() const
{
	return m_deleteCellX;
}
//-------------------------------------------
void Player::setDeleteCellX(bool num)
{
	m_deleteCellX = num;
}
//-------------------------------------------
bool Player::getDeleteCellZ()const
{
	return m_deleteCellZ;
}
//-------------------------------------------
void Player::setDeleteCellZ(bool num)
{
	m_deleteCellZ = num;
}

