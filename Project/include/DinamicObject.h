#pragma once
#include "GameObject.h"

class Board;
class DinamicObject : public GameObject
{
public:
	DinamicObject(const namesOfObjects index, sf::Vector2f location, int width, int height);
	DinamicObject() = default;
	~DinamicObject() = default;
	virtual void move(sf::Time deltaTime) = 0;
	int corectPosition(int point, int num, int pointDirection);
	void setNextDirectionByColumns();
	void setNextDirectionByRows();
	sf::Vector2f checkDirection(int nextDirection);
	void calculateSpeed(sf::Vector2f& m_nextDiarection, int speed);
	void isCloseEnoughToAxis(sf::Time deltaTime);
	sf::Vector2i checkCollisionByDirection(Board & board);
	int getDirection();
	void setLastPosition();
	void getStartPosition();
	void setPosition();
	void setDirection(sf::Vector2f direction);
	bool isOutOfLimits(const sf::Vector2f& destination);
	sf::Vector2f getNextDirection();

protected:
	sf::Vector2f m_direction; //כיוון נוכחי
	sf::Vector2f m_startPosition;
	sf::Vector2f m_positionDestination; //מיקום  היעד
	sf::Vector2f m_nextDirection; //כיוון הבא
	sf::Vector2f m_lastPosition; //מיקום האחרון שהיה בו
	sf::Vector2f m_location;
};