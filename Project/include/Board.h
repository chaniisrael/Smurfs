#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "MonsterType.h"
#include "Player.h"
#include"StaticObject.h"
#include "Wall.h"
#include "Coins.h"
#include "Rod.h"
#include "RegularMonster.h"
#include "SpecialMonster.h"
#include "RandomMonster.h"
#include "GiftType.h"
#include "ScoreGift.h"
#include "TimeGift.h"
#include "Scale.h"
#include "GiftLife.h"
#include "GiftBadMonster.h"


using std::vector;
using std::ifstream;

class Level;
class Board
{
public:
	Board(Player& player1, vector <std::unique_ptr<MonsterType>>& monstersVec, const std::string fileName, const int& numOfLevel); //c-tor
	void readLevelFile(Player& player1, vector <std::unique_ptr<MonsterType>>& monstersVec, const int& numOfLevel); //������� ������ �� ����
	void insertData(Player& player1, vector <std::unique_ptr<MonsterType>>& monsterVec, char c, int i, int j,int limitTime, const int& numOfLevel); //������� ������� �� ����� ���������
	void draw(sf::RenderWindow& window, const int& numOfLevel); //������� ������ �� ���� �� ����
	bool checkIfEof(); //������� ������ �� ���� ����� ����
	StaticObject* getCell(sf::Vector2i cell); //������� ������ ����� �� �� ���� ������� �� ���� ���
	void deleteObjectFromCell(sf::Vector2i& cell); //������� ������ �� �����
	bool checkIfEmpty(sf::Vector2i cell);
	bool checkIfScaleOrWallOrRod(const sf::Vector2i& location);
	bool checkIfScale(const sf::Vector2i& location);
	bool checkIfRod(const sf::Vector2i& location);
	bool checkIfEmpty22(const sf::Vector2f& location);
	void deleteCell(const sf::Vector2f& location, Player& player);
	
		

	
protected:
	void openBoardFile(); //������� ������ ���� �� ���� ����
	ifstream m_file; //����� ����� �� �����
	vector<vector<std::unique_ptr<StaticObject>>> m_gameBoard; //������ ��������� �������
	int m_width;
	int m_height;
	int m_time;
	sf::Clock m_timePassed;
	bool m_ifDelete;
	sf::Vector2f m_locationDelete;
	

};
