#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

using std::vector;

class Resources
{
public:
	~Resources() = default;
	static Resources& getInstance();
	sf::SoundBuffer* getMusic(int num);
	vector <sf::Texture> m_images; 
	sf::Font m_font;
	sf::Music m_backgroundMusic;
	sf::Music m_backgroundMusic2;
	sf::Music m_winnerMusic;
	sf::Music m_gameOverMusic;
	vector<std::unique_ptr<sf::SoundBuffer>> m_soundBuffer;


protected:
	Resources();
	Resources(const Resources& other) = default;
	void insertImageToVector();
	void insertMusic();
	
};