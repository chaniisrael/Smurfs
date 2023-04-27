#include "Board.h"
#include "Level.h"
#include <iostream>

//--------------------------------------------------------------------------------------------------------------
//c-tor
Board::Board(Player& player1, vector <std::unique_ptr<MonsterType>>& monstersVec, const std::string fileName, const int& numOfLevel) : m_file(std::ifstream(fileName)),m_height(0),m_width(0),m_time(4),m_locationDelete(0,0)
{
	openBoardFile();
	readLevelFile(player1, monstersVec, numOfLevel);
}
//--------------------------------------------------------------------------------------------------------------
//פונקציה שקוראת את השלב
void Board::readLevelFile(Player& player1, vector <std::unique_ptr<MonsterType>>& monstersVec, const int& numOfLevel)
{
	int col,row,limitTime;
	m_file >> row >> col >>limitTime;
	m_width = WIDTH_OF_WINDOW / col;//חישוב גובה של תא
	m_height = HIGHT_OF_WINDOW / row; //חישוב גובה של תא
	m_gameBoard.resize(row);
	char c = m_file.get();
	srand(time(0)); //אתחול

	for (int i = 0; i < row; i++) //לולאה שרצה על שורות מטריצת הלוח עד גודל המערך
	{
		for (int j = 0; j < col; j++) //לולאה שרצה על עמודות מטריצת הלוח עד גודל המערך
		{
			c = m_file.get();
			insertData(player1, monstersVec, c, i, j,limitTime,numOfLevel);
		}
		c = m_file.get();
	}
}
//--------------------------------------------------------------------------------------------------------------
//פונקציה שמעדכנת את נתוני האוביקטים
void Board::insertData(Player& player1, vector <std::unique_ptr<MonsterType>>& monstersVec, char c, int i, int j, int limitTime, const int& numOfLevel)
{
	sf::Vector2f location(j * m_width, i * m_height); //חישוב נקודה שמאלית עליונה
	switch (c) //:c בדיקה האם 
	{
	case COINS: //במקרה שהתו הוא מטבע
	{
		m_gameBoard[i].push_back(std::make_unique<Coins>(location, m_width, m_height));
		player1.setNumOfCoins(+1);
		break;
	}
	case ROD: //במקרה שהתו הוא מוט
	{
		m_gameBoard[i].push_back(std::make_unique<Rod>(location, m_width, m_height));
		break;
	}
	case SCALE: //במקרה שהתו הוא סולם
	{
		m_gameBoard[i].push_back(std::make_unique<Scale>(location, m_width, m_height));
			break;
	}
	case WALL: //במקרה שהתו הוא קיר
	{
		m_gameBoard[i].push_back(std::make_unique<Wall>(location, m_width, m_height));
		
		break;
	}
	case GIFT: //במקרה שהתו הוא מתנה
	{	
		int giftType = rand() % 4;
		if(giftType == 0)
			m_gameBoard[i].push_back(std::make_unique<ScoreGift>(location, m_width, m_height));
		if(giftType == 1)
			m_gameBoard[i].push_back(std::make_unique<GiftLife>(location, m_width, m_height));
		if(giftType == 2)
			m_gameBoard[i].push_back(std::make_unique<TimeGift>(location, m_width, m_height));
		if (giftType == 3)
			m_gameBoard[i].push_back(std::make_unique<GiftBadMonster>(location, m_width, m_height, monstersVec));
		break;
	}
	case PLAYER: //במקרה שהתו הוא שחקן
	{
		player1.setPlayer(player, location, m_width, m_height, sf::Vector2f(0, 0), limitTime,numOfLevel);
		m_gameBoard[i].push_back(nullptr);
		break;
	}
	case MONSTER: //במקרה שהתו הוא מפלצת
	{
		int monsterType;
		if(numOfLevel==4)
		   monsterType = 2;
		else
		   monsterType = rand() % 2;
		if (monsterType == 0)
			monstersVec.push_back(std::make_unique<RegularMonster>(location, m_width, m_height));
		else if (monsterType == 1)
			monstersVec.push_back(std::make_unique<RandomMonster>(location, m_width, m_height));
		else if (monsterType == 2)
			monstersVec.push_back(std::make_unique<SpecialMonster>(location, m_width, m_height, player1));
		m_gameBoard[i].push_back(nullptr);
		break;
	}
	case SPACE:
		m_gameBoard[i].push_back(nullptr);
		break;
	default:
		break;
	}
}
//--------------------------------------------------------------------------------------------------------------
//פונקציה שמציגה את הלוח על המסך
void Board::draw(sf::RenderWindow& window, const int& numOfLevel)
{
	sf::Sprite sprite(Resources::getInstance().m_images[gameBackground1]);
	window.draw(sprite);
	for (int i = 0; i < m_gameBoard.size(); i++)
	{
		for (int j = 0; j < m_gameBoard[i].size(); j++) 
		{
			if (m_gameBoard[i][j] != nullptr)
				m_gameBoard[i][j]->draw(window);
		}
	}
}
//--------------------------------------------------------------------------------------------------------------
//פונקציה שבודקת אם הגיע לסיום השלב
bool Board::checkIfEof()
{
	return !m_file.eof();
}
//--------------------------------------------------------------------------------------------------------------
//פונקציה שמקבלת מיקום של תא בלוח ומחזירה את תוכן התא
 StaticObject* Board::getCell(sf::Vector2i cell)
{
	 return m_gameBoard[cell.y][cell.x].get();
}
 //--------------------------------------------------------------------------------------------------------------
 //פונקציה שמוחקת תא מהלוח
void Board::deleteObjectFromCell(sf::Vector2i& cell)
{
	m_gameBoard[cell.y][cell.x] = nullptr;
}
//--------------------------------------------------------------------------------------------------------------
//פונקציה שמקבלת מיקום תא ומחזירה אם התא ריק
bool Board::checkIfEmpty(sf::Vector2i cell)
{
	if (m_gameBoard[cell.y][cell.x] == nullptr)
		return true;
	return false;
}
//-----------------------------------------------------------------------------
bool Board::checkIfScaleOrWallOrRod(const sf::Vector2i& location)
{
	return((typeid(Wall).name() == typeid(*m_gameBoard[location.y][location.x]).name())) || ((typeid(Rod).name() == typeid(*m_gameBoard[location.y][location.x]).name())) || ((typeid(Scale).name() == typeid(*m_gameBoard[location.y][location.x]).name()));
}
//---------------------------------------------------------------------------
bool Board::checkIfScale(const sf::Vector2i& location)
{
	return typeid(Scale).name() == typeid(*m_gameBoard[location.y][location.x]).name();
}
//-----------------------------------------------------------------
bool Board::checkIfRod(const sf::Vector2i& location)
{
	return typeid(Rod).name() == typeid(*m_gameBoard[location.y][location.x]).name();
}
//בדיקה שבתא מתחת לשחקן הוא ריק או שיש מתנה או כסף 
bool Board::checkIfEmpty22(const sf::Vector2f& location)
{
	int location1 = (float(location.y) / m_height)+1;
	int location2 =( float(location.x) / m_width);
	auto p = m_gameBoard.begin() + (location1);
	auto p2 = p->begin() + (location2);
	if (*p2 == nullptr|| typeid(GiftType).name() == typeid(*m_gameBoard[location1][location2]).name() || typeid(Coins).name() == typeid(*m_gameBoard[location1][location2]).name())
		return true;
	return false;
	
}
//----------------------------------------------------------------------------------------------
//מחיקת תא 
void Board::deleteCell(const sf::Vector2f& location,Player& player)
{
	int x=0, y= 1;
	if (player.getDeleteCellZ())
		x=-1;
	else if (player.getDeleteCellX())
		x=1;
	int location1 = (float(location.y) / m_height) +(y);
	int location2 = (float(location.x) / m_width) +(x);
	auto p = m_gameBoard.begin() + (location1);
	auto p2 = p->begin() + (location2);
	if (*p2 != nullptr)
	{
		if ((typeid(Wall).name() == typeid(*m_gameBoard[location1][location2]).name()))
			*p2 = nullptr;
	}
}
//--------------------------------------------------------------------------------------------------------------
//פונקציה שפותחת נכון את קובץ השלב
void Board::openBoardFile()
{
	if (!m_file.is_open())
	{
		std::cerr << "Can't open the file \n";
		exit(EXIT_FAILURE);
	}
}
