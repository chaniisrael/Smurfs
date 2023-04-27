#pragma once
#include "StaticObject.h"

class Board;
class Coins : public StaticObject
{
public:
	Coins( sf::Vector2f location, int width, int height);//c-tor
	virtual namesOfObjects collide(Player& player) override; //������� ������ ������� ��� ���� ����
	virtual void collide(MonsterType& monster) override; //������� ������ ������� ��� ����� ����� 

protected:
	sf::Sound m_sound1;
};