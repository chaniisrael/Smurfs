#pragma once
//מחלקת קבועים
const auto PLAYER = '@';
const auto MONSTER = '%'; 
const auto COINS = '*';
const auto SCALE = 'H';
const auto WALL = '#';
const auto ROD = '-';
const auto SPACE = ' ';
const auto GIFT = '+';
const auto HIGHT_OF_WINDOW = 600;
const auto WIDTH_OF_WINDOW = 1100;
const auto TOTAL_LIFE = 3;
const auto PLAYER_SPEED = 110;
const auto MONSTER_SPEED = 50;
const auto EPSILON = 1;
const auto NUMBER_OF_DIRECTIONS = 4;

enum namesOfObjects
{
	coins,
	wall,
	player,
	gift,
	rod,
	scale,
	regularMonster,
	specialMonster,
	randomMonster,
	exitGame,
	menuScreen,
	newGame,
	gameBackground1,
	gameBackground2,
	gameBackground3,
	life,
	GameOver,
	winner
};


enum Directions
{
	left,
	right,
	up,
	down,
	Default
};
