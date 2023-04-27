#include "StaticObject.h"
#include "Board.h"

//--------------------------------------------------------------------------------------------------------------
StaticObject::StaticObject(const namesOfObjects index, sf::Vector2f location, int width, int height) :
	GameObject(index, location, width, height)
{
}
