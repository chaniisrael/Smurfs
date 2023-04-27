#include "Level.h"

//--------------------------------------------------------------------------------------------------------------
Level::Level(Player& player, const std::string fileName, const int& numOfLevel) : m_board(player, m_monsters, fileName, numOfLevel), m_clock(),m_informationDisplay()
{
	if (numOfLevel != 4)
	{
		Resources::getInstance().m_backgroundMusic.play();
		Resources::getInstance().m_backgroundMusic.setLoop(true);
	}
	else
	{
		Resources::getInstance().m_backgroundMusic2.play();
		Resources::getInstance().m_backgroundMusic2.setLoop(true);
	}
}
Level::~Level()
{
	Resources::getInstance().m_backgroundMusic.stop();
	Resources::getInstance().m_backgroundMusic2.stop();
}
//--------------------------------------------------------------------------------------------------------------
//מנהלת שלב
void Level::run(sf::RenderWindow& window, bool& gameStatus, bool& restart, Player& player, const int& numOfLevel)
{
	while (window.isOpen())
	{

		window.clear();
		m_board.draw(window, numOfLevel);//מדפיס למסך את השלב
		//זימון לפונקציה שמטפלת בתצוגת מידה
		m_informationDisplay.displayData(window, player.getLife(), player.getScore(), numOfLevel,
			player.getTime() - m_timePassed.getElapsedTime().asSeconds());
		draw(window, player);//הדפסה של המפלצות
		window.display();
		CheckLevelEvents(window, player);//עם יש לחיצה
		player.setLastPosition(); //שומר את המיקום האחרון שהיה
		move(player);//קיראה לפונקציה שמטפלת בתזוזה
		mainCollision(player); //קריאה לפונקציה שמטפלת בהתנגשות
		if (player.getTime() - (m_timePassed.getElapsedTime().asSeconds()) <= 0)//אם לשחקן ניגמר הזמן
		{
			player.setLife(-1);//הורדת חיים
			restart = true;
		}
		if (player.getLife() == 0)//עם ניגמר החיים
		{
			gameStatus = true;
		}
		if (player.getNumOfCoins() == 0)//אם השחקן אכל את כל המטבעות
		{
			player.setScore(50 * numOfLevel);
		}
		if (player.getLife() == 0 || restart || player.getNumOfCoins() == 0)
                          return;

	}
}
//--------------------------------------------------------------------------------------------------------------
//מדפיסה את המפלצות והשחקן על המסך
void Level::draw(sf::RenderWindow& window, Player& player)
{
	for (const auto& monster : m_monsters)
		monster->draw(window);
	player.draw(window);
}
//--------------------------------------------------------------------------------------------------------------
//פונקציה שמטפלת בלחיצה
void Level::CheckLevelEvents(sf::RenderWindow& window, Player& player)
{
	bool IfScale = checkIfScale(player);
	bool IfEmpty = checkIfEmpty(player);
	if (IfEmpty)//מטפל בנפילה של השחקן
	{
		player.handleEvent(sf::Keyboard::Key::Down, IfScale, IfEmpty);//קיראה לפונקציה של הלחיצה בשחקן
		player.move(getDeltaTime());//קיראה לפונקציה של תזוזה
	}
	auto event = sf::Event{};
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			exit(0);
			break;
		case sf::Event::KeyPressed:
		{
				player.handleEvent(event.key.code, IfScale, IfEmpty);//קיראה לפונקציה של הלחיצה בשחקן
				if (player.getDeleteCellZ()||player.getDeleteCellX())// עם היתה לחיצה על מחיקה
				{
					m_board.deleteCell(player.getPosition(),player);//מחיקה של התא
					player.setDeleteCellX(false);
					player.setDeleteCellZ(false);
				}
				player.move(getDeltaTime());//קיראה לפונקציה של תזוזה
			break;
		}
		default:
			break;
		}
	}
}
//--------------------------------------------------------------------------------------------------------------
//מטפל בתוזזה של השקן והמפלצות
void Level::move(Player& player)
{

	player.move(m_clock.getElapsedTime());
	srand(time(0));
	auto deltaTime = getDeltaTime();
	for (const auto& monster : m_monsters)
	{
		monster.get()->setLastPosition();
		monster->move(deltaTime);
	}
}
////--------------------------------------------------------------------------------------------------------------
sf::Time Level::getDeltaTime()
{
	auto deltaTime = m_clock.restart();
	return deltaTime;
}
//--------------------------------------------------------------------------------------------------------------
//התנגשות
void Level::mainCollision(Player& player)
{
	playerCollideWithStaticObject(player);//קיראה לפונקצית התנגשות של שחקן עם אוביקטים סטטים
	playerCollideWithMonster(player);//קיראה לפונקצית התנגשות של שחקן עם מפלצות
	monsterCollideWithStaticObject(player);//קיראה לפונקצית התנגשות של מפלצות עם אוביקטים סטטים
}
//--------------------------------------------------------------------------------------------------
//קיראה לפונקצית התנגשות של שחקן עם מפלצות
void Level::playerCollideWithMonster(Player& player)
{
	for (const auto& monster : m_monsters)
		if (player.getGlobalBoundsOfSprite().intersects(monster.get()->getGlobalBoundsOfSprite()))
			monster.get()->collide(player);
}
//--------------------------------------------------------------------------------------------------------------
//קיראה לפונקצית התנגשות של שחקן עם אוביקטים סטטים
void Level::playerCollideWithStaticObject(Player& player)
{
	auto cell = sf::Vector2i(-1, -1);
	cell = player.checkCollisionByDirection(m_board);
	if (cell != sf::Vector2i(-1, -1))
	{
		if (!m_board.checkIfEmpty(cell)) //אם התא לא ריק
		{
			if (player.getGlobalBoundsOfSprite().intersects(m_board.getCell(cell)->getGlobalBoundsOfSprite()))
			{
				m_board.getCell(cell)->collide(player);
				if (!m_board.checkIfScaleOrWallOrRod(cell))//אם התמונה שבתא לא קיר
					m_board.deleteObjectFromCell(cell); //נמחוק מהלוח
			}
		}
	}
}

//--------------------------------------------------------------------------------------------------------------
//קיראה לפונקצית התנגשות של מפלצות עם אוביקטים סטטים
void Level::monsterCollideWithStaticObject(Player& player)
{
	auto cell = sf::Vector2i(-1, -1);
	for (const auto& monster : m_monsters)
	{
		
		cell = monster.get()->checkCollisionByDirection(m_board);
		if (cell != sf::Vector2i(-1, -1))
		{
			if (!m_board.checkIfEmpty(cell)) //אם התא לא ריק
			{
				if (monster.get()->getGlobalBoundsOfSprite().intersects(m_board.getCell(cell)->getGlobalBoundsOfSprite()))
					if (typeid(*monster).name() != typeid(SpecialMonster).name())
					        m_board.getCell(cell)->collide(*monster);
			}
		}
	}
}

//--------------------------------------------------------------------------------------------------------------
//פונקציה שבודקת אם הגיע לסיום השלב
bool Level::checkIfEof()
{
	return m_board.checkIfEof();
}
//--------------------------------------------------------------------------------------------------------------
//בדיקה אם במיקום של השחקן יש סולם
bool Level::checkIfScale(Player& player)
{
	
	auto cell = sf::Vector2i(-1, -1);
	cell = player.checkCollisionByDirection(m_board);
	if (cell != sf::Vector2i(-1, -1))
		if (!m_board.checkIfEmpty(cell)) //אם התא לא ריק
			if (player.getGlobalBoundsOfSprite().intersects(m_board.getCell(cell)->getGlobalBoundsOfSprite()))
				if (m_board.checkIfScale(cell))
					return true;

	return false;
	
}
//--------------------------------------------------------------------------------------------------------
//אם התא מתחת לשחקן ריק השחק נופל
bool Level::checkIfEmpty(Player& player)
{
	
	auto cell = sf::Vector2f(-1, -1);
	cell = player.getPosition();
      if(!checkIfRod(player))
			if (m_board.checkIfEmpty22(cell))
					return true;
	return false;
}
//----------------------------------------------------------------------------------
//אם התא מוט
bool Level::checkIfRod(Player& player)
{
	auto cell = sf::Vector2i(-1, -1);
	cell = player.checkCollisionByDirection(m_board);
	if (cell != sf::Vector2i(-1, -1))
		if (!m_board.checkIfEmpty(cell)) //אם התא לא ריק
			if (player.getGlobalBoundsOfSprite().intersects(m_board.getCell(cell)->getGlobalBoundsOfSprite()))
				if (m_board.checkIfRod(cell))
					return true;
	return false;
}

