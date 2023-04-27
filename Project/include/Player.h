#pragma once
#include "DinamicObject.h"
#include "Const.h"
class Player : public DinamicObject
{
public:
	Player(); //c-tor
	void setPlayer(const namesOfObjects index, sf::Vector2f location, int width, int height, sf::Vector2f direction, int time, const int& numOfLevel);
	void handleEvent(sf::Keyboard::Key key,bool& IfScale, bool& IfEmpty);
	virtual void move(sf::Time deltaTime) override;
	sf::Vector2f getPosition() const;
	void startPosition();
	bool isAteAllCoins();
	int getNumOfCoins()const;
	void setNumOfCoins(int num);
	int getScore() const;
	void setScore(int score);
	void setLife(int num);
	int getLife()const;
    int getTime() const;
	void setTime(int time);
	int numOfLevel();
	bool getDeleteCellZ()const;
	void setDeleteCellZ(bool num);
	bool getDeleteCellX()const;
	void setDeleteCellX(bool num);
protected:
	int m_life;//מספר חיים
	int m_score;//ניקוד
	int m_time;
	int m_timeeee;
	int m_numOfCoins;//מחזיק כמה מטבעות צריך לאכול
    int m_numOfLevel;//מספר שלב
	bool m_deleteCellZ;
	bool m_deleteCellX;
	

};