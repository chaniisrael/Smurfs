#include "GameManager.h"

//--------------------------------------------------------------------------------------------------------------
GameManager::GameManager() : m_player(),m_menu(), m_window(sf::VideoMode(WIDTH_OF_WINDOW, HIGHT_OF_WINDOW), "Game")
{
}

void GameManager::run()
{
	while (m_window.isOpen())
	{
	    managesMenu();//������� ������ ���� �����
		bool gameStatus = false;
		managesLevels(gameStatus);//������� ������ ��� ������ ������ ������ ����
		managesEndOfGame(gameStatus);//������� ������ ���� ����� ����� 
		return;
	}
}

//--------------------------------------------------------------------------------------------------------------
void GameManager::managesLevels(bool& gameStatus)
{

	int numOfLevel = 1; //����� ������ �� ���� ����
	bool restart = false;
	auto levelFile = std::string("Level1.txt");
	while (std::ifstream(levelFile))
	{
		restart = false;
		Level level(m_player, levelFile, numOfLevel);//����� ����� 
		level.run(m_window, gameStatus, restart, m_player, numOfLevel);//����� ����� ������ ���
		if (restart)//�� ����� ���� ����� ���� ����
		{
			numOfLevel--;
			m_player.setNumOfCoins(-m_player.getNumOfCoins());
		}
		numOfLevel++;
		levelFile = std::string("Level") + std::to_string(numOfLevel) + std::string(".txt");
	}
}
//------------------------------------------------------------------------------------
void GameManager::managesMenu()
{
	m_window.clear();
	m_menu.drawMenuWindow(m_window);//������ �� ���� ���������
	m_window.display();
	m_menu.CheckMenuEvents(m_window);// ����� �� �� ����� ����� ������
}
//-------------------------------------------------------------------------------------------------------
void GameManager::managesEndOfGame(bool& gameStatus)
{
	if (gameStatus)
		Resources::getInstance().m_gameOverMusic.play();
	else
		Resources::getInstance().m_winnerMusic.play();
	while (m_window.isOpen())
	{
		auto sprite = sf::Sprite();
		if (gameStatus)
			sprite = sf::Sprite(Resources::getInstance().m_images[GameOver]);
		else
			sprite = sf::Sprite(Resources::getInstance().m_images[winner]);
		m_window.draw(sprite);
		m_window.display();
		if (auto event = sf::Event{}; m_window.pollEvent(event))
			if (event.type == sf::Event::Closed)
			{
				if (gameStatus)
					Resources::getInstance().m_gameOverMusic.stop();
				else
					Resources::getInstance().m_winnerMusic.stop();
				return;
			}
	}
}









