#pragma once
#include <iostream>
#include <conio.h> // for _getch()
#include "GameSource.h"
#include "SpaceInvaders.h"

class Menu
{
public:
	Menu() {
		startMenu();
		update();
	}
	~Menu() {}
	short startMenu();
	void update();
	GameSource& getGame() { return *game; };

	std::unique_ptr<GameSource> game;
};

