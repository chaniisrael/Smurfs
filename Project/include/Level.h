#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Board.h"
#include "MonsterType.h"
#include "Player.h"
#include "Resources.h"
#include "InformationDisplay.h"
//#include "InformationDisplay.h"
using std::vector;

class Level
{
public:
	Level(Player& player, const std::string fileName, const int& numOfLevel);
	~Level()/* = default*/;
	void run(sf::RenderWindow& window, bool& gameStatus, bool& restart, Player& player,const int& numOfLevel);
	void draw(sf::RenderWindow& window, Player& player);
	void CheckLevelEvents(sf::RenderWindow& window, Player& player);
	void move(Player& player);
	sf::Time getDeltaTime();
	void mainCollision(Player& player);
	void playerCollideWithMonster(Player& player);
	void playerCollideWithStaticObject(Player& player);
	void monsterCollideWithStaticObject(Player& player);
	bool checkIfEof();
	bool checkIfScale(Player& player);
	bool checkIfEmpty(Player& player);
	bool checkIfRod(Player& player);

protected:
	vector <std::unique_ptr<MonsterType>> m_monsters;
	Board m_board;

	sf::Clock m_clock;
	sf::Clock m_timePassed;
	InformationDisplay m_informationDisplay;
};

