#include "DinamicObject.h"
#include "Board.h"

//--------------------------------------------------------------------------------------------------------------
DinamicObject::DinamicObject(const namesOfObjects index, sf::Vector2f location, int width, int height) :
	GameObject(index, location, width, height), m_direction(1, 0), m_startPosition(location), m_lastPosition(location)
{
}
//--------------------------------------------------------------------------------------------------------------
int DinamicObject::corectPosition(int point, int num, int pointDirection)
{
	point = (point - (point % num)); //חישוב נקודת הצירים
	if (pointDirection > 0) //אם הכיוון הוא ימינה או למטה 
		return point + num + EPSILON; //מוסיפה כדי לקדם אותו
	return point;
}
//--------------------------------------------------------------------------------------------------------------
//חישוב לפי צירים
void DinamicObject::setNextDirectionByColumns()
{
	m_positionDestination.y = corectPosition((m_sprite.getPosition().y), (m_sprite.getGlobalBounds().height), m_direction.y);
	m_positionDestination.x = m_sprite.getPosition().x;
}
//--------------------------------------------------------------------------------------------------------------
//חישוב לפי צירים
void DinamicObject::setNextDirectionByRows()
{
	m_positionDestination.x = corectPosition((m_sprite.getPosition().x), (m_sprite.getGlobalBounds().width), m_direction.x);
	m_positionDestination.y = m_sprite.getPosition().y;
}
//--------------------------------------------------------------------------------------------------------------
//חישוב לפי צירים
sf::Vector2f DinamicObject::checkDirection(int nextDirection)
{
	switch (nextDirection)
	{
	case left:
		setNextDirectionByColumns();
		return { -1,0 };
	case right:
		setNextDirectionByColumns();
		return { 1,0 };
	case up:
		setNextDirectionByRows();
		return { 0,-1 };
	case down:
		setNextDirectionByRows();
		return { 0,1 };
	default:
		break;
	}
}
//--------------------------------------------------------------------------------------------------------------
void DinamicObject::calculateSpeed(sf::Vector2f& nextDirection, int speed)
{
    nextDirection.x *= speed;
	nextDirection.y *= speed;
}
//--------------------------------------------------------------------------------------------------------------
void DinamicObject::isCloseEnoughToAxis(sf::Time deltaTime)
{
	if (std::abs(m_sprite.getPosition().x - m_positionDestination.x) <= EPSILON &&
		std::abs(m_sprite.getPosition().y - m_positionDestination.y) <= EPSILON)
	{
		m_direction = m_nextDirection;
		if (isOutOfLimits((m_direction * deltaTime.asSeconds()) + m_sprite.getPosition()))//אם זה לא יוצא מהגבולות
			m_sprite.move(m_direction * deltaTime.asSeconds());
	}

}
//--------------------------------------------------------------------------------------------------------------
sf::Vector2i DinamicObject::checkCollisionByDirection(Board& board)
{
	auto cell = sf::Vector2i(-1, -1);
	auto width = m_sprite.getGlobalBounds().width;
	auto height = m_sprite.getGlobalBounds().height;
	auto x = m_sprite.getPosition().x;
	auto y = m_sprite.getPosition().y;
	switch (getDirection())
	{
	case left:
		cell = sf::Vector2i(floor((x + 4) / width), floor((y + 4) / height));
		break;
	case right:
		cell = sf::Vector2i(floor((x + width - 4) / width), floor((y + 4) / height));
		break;
	case up:
		cell = sf::Vector2i(floor((x + 4) / width), floor((y) / height));
		break;
	case down:
		cell = sf::Vector2i(floor((x + 4) / width), floor((y+ height) / height));
		break;
	default:
		break;
	}
	if (cell != sf::Vector2i(-1, -1))
	{
		if (!board.checkIfEmpty(cell))
			return cell;
	}
	return cell = sf::Vector2i(-1, -1);

}
//--------------------------------------------------------------------------------------------------------------
int DinamicObject::getDirection()
{
	if (m_direction.x == 0 && m_direction.y == 0)
		return Default;
	else if (m_direction.x < 0)
		return left;
	else if (m_direction.x > 0)
		return right;
	else if (m_direction.y < 0)
		return up;
	else if (m_direction.y > 0)
		return down;
}
//--------------------------------------------------------------------------------------------------------------
//משנה למיקום שהוא נמצא
void DinamicObject::setLastPosition()
{
	m_lastPosition = m_sprite.getPosition();
}
//------------------------------------------------------------------------------------------------------------
////משנה למיקום ההתחלתי-
void DinamicObject::getStartPosition()
{
	m_sprite.setPosition(m_startPosition);
}
//--------------------------------------------------------------------------------------------------------------
void DinamicObject::setPosition()
{
	
	if (m_direction.x > 0)
		m_positionDestination.x -= m_sprite.getGlobalBounds().width;
	if (m_direction.y > 0)
		m_positionDestination.y -= m_sprite.getGlobalBounds().height;
	m_sprite.setPosition(sf::Vector2f(ceil(m_lastPosition.x), ceil(m_lastPosition.y)));
}
//--------------------------------------------------------------------------------------------------------------
//משנה כיוון
void DinamicObject::setDirection(sf::Vector2f direction)
{
	m_direction = direction;
}
//--------------------------------------------------------------------------------------------------------------
//בדיקת גבולות
bool DinamicObject::isOutOfLimits(const sf::Vector2f& destination)
{
	return(destination.x >= 0 && destination.x + m_sprite.getGlobalBounds().width <= WIDTH_OF_WINDOW && //WIDTH_OF_BOARD &&
		destination.y >= 0 && destination.y + m_sprite.getGlobalBounds().height <= HIGHT_OF_WINDOW);
}
sf::Vector2f DinamicObject::getNextDirection()
{
	return m_nextDirection;
}
