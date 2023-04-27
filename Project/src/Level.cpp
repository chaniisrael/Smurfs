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
//����� ���
void Level::run(sf::RenderWindow& window, bool& gameStatus, bool& restart, Player& player, const int& numOfLevel)
{
	while (window.isOpen())
	{

		window.clear();
		m_board.draw(window, numOfLevel);//����� ���� �� ����
		//����� �������� ������ ������ ����
		m_informationDisplay.displayData(window, player.getLife(), player.getScore(), numOfLevel,
			player.getTime() - m_timePassed.getElapsedTime().asSeconds());
		draw(window, player);//����� �� �������
		window.display();
		CheckLevelEvents(window, player);//�� �� �����
		player.setLastPosition(); //���� �� ������ ������ ����
		move(player);//����� �������� ������ ������
		mainCollision(player); //����� �������� ������ ��������
		if (player.getTime() - (m_timePassed.getElapsedTime().asSeconds()) <= 0)//�� ����� ����� ����
		{
			player.setLife(-1);//����� ����
			restart = true;
		}
		if (player.getLife() == 0)//�� ����� �����
		{
			gameStatus = true;
		}
		if (player.getNumOfCoins() == 0)//�� ����� ��� �� �� �������
		{
			player.setScore(50 * numOfLevel);
		}
		if (player.getLife() == 0 || restart || player.getNumOfCoins() == 0)
                          return;

	}
}
//--------------------------------------------------------------------------------------------------------------
//������ �� ������� ������ �� ����
void Level::draw(sf::RenderWindow& window, Player& player)
{
	for (const auto& monster : m_monsters)
		monster->draw(window);
	player.draw(window);
}
//--------------------------------------------------------------------------------------------------------------
//������� ������ ������
void Level::CheckLevelEvents(sf::RenderWindow& window, Player& player)
{
	bool IfScale = checkIfScale(player);
	bool IfEmpty = checkIfEmpty(player);
	if (IfEmpty)//���� ������ �� �����
	{
		player.handleEvent(sf::Keyboard::Key::Down, IfScale, IfEmpty);//����� �������� �� ������ �����
		player.move(getDeltaTime());//����� �������� �� �����
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
				player.handleEvent(event.key.code, IfScale, IfEmpty);//����� �������� �� ������ �����
				if (player.getDeleteCellZ()||player.getDeleteCellX())// �� ���� ����� �� �����
				{
					m_board.deleteCell(player.getPosition(),player);//����� �� ���
					player.setDeleteCellX(false);
					player.setDeleteCellZ(false);
				}
				player.move(getDeltaTime());//����� �������� �� �����
			break;
		}
		default:
			break;
		}
	}
}
//--------------------------------------------------------------------------------------------------------------
//���� ������ �� ���� ��������
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
//�������
void Level::mainCollision(Player& player)
{
	playerCollideWithStaticObject(player);//����� �������� ������� �� ���� �� �������� �����
	playerCollideWithMonster(player);//����� �������� ������� �� ���� �� ������
	monsterCollideWithStaticObject(player);//����� �������� ������� �� ������ �� �������� �����
}
//--------------------------------------------------------------------------------------------------
//����� �������� ������� �� ���� �� ������
void Level::playerCollideWithMonster(Player& player)
{
	for (const auto& monster : m_monsters)
		if (player.getGlobalBoundsOfSprite().intersects(monster.get()->getGlobalBoundsOfSprite()))
			monster.get()->collide(player);
}
//--------------------------------------------------------------------------------------------------------------
//����� �������� ������� �� ���� �� �������� �����
void Level::playerCollideWithStaticObject(Player& player)
{
	auto cell = sf::Vector2i(-1, -1);
	cell = player.checkCollisionByDirection(m_board);
	if (cell != sf::Vector2i(-1, -1))
	{
		if (!m_board.checkIfEmpty(cell)) //�� ��� �� ���
		{
			if (player.getGlobalBoundsOfSprite().intersects(m_board.getCell(cell)->getGlobalBoundsOfSprite()))
			{
				m_board.getCell(cell)->collide(player);
				if (!m_board.checkIfScaleOrWallOrRod(cell))//�� ������ ���� �� ���
					m_board.deleteObjectFromCell(cell); //����� �����
			}
		}
	}
}

//--------------------------------------------------------------------------------------------------------------
//����� �������� ������� �� ������ �� �������� �����
void Level::monsterCollideWithStaticObject(Player& player)
{
	auto cell = sf::Vector2i(-1, -1);
	for (const auto& monster : m_monsters)
	{
		
		cell = monster.get()->checkCollisionByDirection(m_board);
		if (cell != sf::Vector2i(-1, -1))
		{
			if (!m_board.checkIfEmpty(cell)) //�� ��� �� ���
			{
				if (monster.get()->getGlobalBoundsOfSprite().intersects(m_board.getCell(cell)->getGlobalBoundsOfSprite()))
					if (typeid(*monster).name() != typeid(SpecialMonster).name())
					        m_board.getCell(cell)->collide(*monster);
			}
		}
	}
}

//--------------------------------------------------------------------------------------------------------------
//������� ������ �� ���� ����� ����
bool Level::checkIfEof()
{
	return m_board.checkIfEof();
}
//--------------------------------------------------------------------------------------------------------------
//����� �� ������ �� ����� �� ����
bool Level::checkIfScale(Player& player)
{
	
	auto cell = sf::Vector2i(-1, -1);
	cell = player.checkCollisionByDirection(m_board);
	if (cell != sf::Vector2i(-1, -1))
		if (!m_board.checkIfEmpty(cell)) //�� ��� �� ���
			if (player.getGlobalBoundsOfSprite().intersects(m_board.getCell(cell)->getGlobalBoundsOfSprite()))
				if (m_board.checkIfScale(cell))
					return true;

	return false;
	
}
//--------------------------------------------------------------------------------------------------------
//�� ��� ���� ����� ��� ���� ����
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
//�� ��� ���
bool Level::checkIfRod(Player& player)
{
	auto cell = sf::Vector2i(-1, -1);
	cell = player.checkCollisionByDirection(m_board);
	if (cell != sf::Vector2i(-1, -1))
		if (!m_board.checkIfEmpty(cell)) //�� ��� �� ���
			if (player.getGlobalBoundsOfSprite().intersects(m_board.getCell(cell)->getGlobalBoundsOfSprite()))
				if (m_board.checkIfRod(cell))
					return true;
	return false;
}

