#pragma once
#include "StaticObject.h"
#include "Const.h"

class Scale : public StaticObject
{
public:
	Scale(sf::Vector2f location, int width, int height); //c-tor
     virtual namesOfObjects collide(Player& player) override; //������� ������ ������� ��� ���� ����
	virtual void collide(MonsterType& monster) override; //������� ������ ������� ��� ����� �����

protected:

};