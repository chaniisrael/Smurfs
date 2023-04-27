#include "Resources.h"

//--------------------------------------------------------------------------------------------------------------
Resources& Resources::getInstance()
{
	static Resources m_instance;
	return m_instance;
}
//--------------------------------------------------------------------------------------------------------------
Resources::Resources()
{
	insertImageToVector();
	
}
//----------------------------------------------------------------------------------------------
void Resources::insertImageToVector()
{
	auto image = sf::Texture(); // texture יצירת תמונה מסוג

	image.loadFromFile("Coins.png");
	m_images.push_back(image); //הכנסת התמונה לווקטור

	image.loadFromFile("wall3.png");
	m_images.push_back(image); //הכנסת התמונה לווקטור

	image.loadFromFile("Player.png");
	m_images.push_back(image); //הכנסת התמונה לווקטור

	image.loadFromFile("Gift.png");
	m_images.push_back(image); //הכנסת התמונה לווקטור

	image.loadFromFile("Rod3.png");
	m_images.push_back(image);

	image.loadFromFile("Scale2.png");
	m_images.push_back(image); //הכנסת התמונה לווקטור

	image.loadFromFile("RegularMonster.png");
	m_images.push_back(image); ///הכנסת התמונה לווקטור

	image.loadFromFile("SpecialMonster.png");
	m_images.push_back(image); ///הכנסת התמונה לווקטור
	 
	image.loadFromFile("RandomMonster.png");
	m_images.push_back(image);

	image.loadFromFile("ExitGame.png");
	m_images.push_back(image); //הכנסת התמונה לווקטור

	image.loadFromFile("MenuScreen.jpg");
	m_images.push_back(image); ///הכנסת התמונה לווקטור

	image.loadFromFile("NewGame.png");
	m_images.push_back(image); //הכנסת התמונ

	image.loadFromFile("background1.jpg");
	m_images.push_back(image);

	image.loadFromFile("background2.gif");
	m_images.push_back(image);

	image.loadFromFile("background3.jpg");
	m_images.push_back(image);


	image.loadFromFile("life.png");
	m_images.push_back(image);

	image.loadFromFile("GameOver.jpg");
	m_images.push_back(image);  //הכנסת התמונה לווקטור
	
	image.loadFromFile("winner.jpg");
	m_images.push_back(image); //הכנסת התמונה לווקט
		
	
	m_font.loadFromFile("c:/Windows/Fonts/Forte.ttf");
	m_backgroundMusic.openFromFile("backGroundMusic.wav");
	m_backgroundMusic2.openFromFile("backGroundMusic2.wav");
	m_gameOverMusic.openFromFile("GameOverMusic.wav");
	m_winnerMusic.openFromFile("GameWin.wav");
}
