#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "Const.h"

class GameObject
{
public:
	GameObject(const namesOfObjects index, sf::Vector2f location, int width, int height);
	GameObject() = default;
	~GameObject() = default;
	void setObjet(sf::Vector2f location, int width, int height);
	void draw(sf::RenderWindow& window);
	sf::FloatRect getGlobalBoundsOfSprite();


protected:
	sf::Sprite m_sprite;
};