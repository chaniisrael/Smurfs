#include "GameObject.h"

GameObject::GameObject(const namesOfObjects index, sf::Vector2f location, int width, int height) :
	m_sprite(Resources::getInstance().m_images[index])
{
	setObjet(location, width, height);
}
//--------------------------------------------------------------------------------------------------------------
void GameObject::setObjet(sf::Vector2f location, int width, int height)
{
	auto texture = m_sprite.getTexture();
	auto texSize = texture->getSize();
	auto newTexSize = sf::Vector2u(width, height);
	auto scaleX = (newTexSize.x * 1.00f / texSize.x);
	auto scaleY = (newTexSize.y * 1.00f / texSize.y);
	m_sprite.setScale(scaleX, scaleY);
	m_sprite.setPosition(location);
}
//--------------------------------------------------------------------------------------------------------------
void GameObject::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}
//--------------------------------------------------------------------------------------------------------------
sf::FloatRect GameObject::getGlobalBoundsOfSprite()
{
	return m_sprite.getGlobalBounds();
}
