#pragma once
#include "GiftType.h"

class Board;
class TimeGift : public GiftType
{
public:
	TimeGift(sf::Vector2f location, int width, int height); //c-tor
	virtual namesOfObjects collide(Player& player) override; //������� ������ ������� ��� ���� �����
	virtual void collide(MonsterType& monster) override; //������� ������ ������� ��� ����� �����

protected:

};