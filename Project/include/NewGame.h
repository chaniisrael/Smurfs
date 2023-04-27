#pragma once
#include "ButtonType.h"

class NewGame : public ButtonType
{
public:
	NewGame(sf::Vector2f location);
	~NewGame() = default;
	virtual void handleClick() override;

protected:

};