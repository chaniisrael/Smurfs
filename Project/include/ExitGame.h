#pragma once
#include "ButtonType.h"

class ExitGame : public ButtonType
{
public:
	ExitGame(sf::Vector2f location);
	~ExitGame() = default;
	virtual void handleClick() override;

protected:

};