#pragma once
#include "GiftType.h"
#include "MonsterType.h"
#include "RandomMonster.h"
#include "SpecialMonster.h"
#include "RegularMonster.h"

//class Board;
class GiftBadMonster : public GiftType
{
public:
	GiftBadMonster(sf::Vector2f location, int width, int height, vector <std::unique_ptr<MonsterType>>& monsters); //c-tor
	virtual namesOfObjects collide(Player& player) override; //������� ������ ������� ��� ���� �����
	virtual void collide(MonsterType& monster) override; //������� ������ ������� ��� ����� �����

protected:
	vector <std::unique_ptr<MonsterType>>& m_monsters;
	int m_width;
	int m_height;
};