#pragma once
#include <iostream>
#include <string>
#include "RandomEngine.h"
#include <chrono>
#include "Macros.h"
#include "GameSource.h"
#include "ScreenBuffer.h"
#include "Menu.h"
#include "Window.h"
#include "Ground.h"
#include "Player.h"
#include "Alien.h"
#include "Barrier.h"

/// <summary>
/// amount of copies made throughout project scope 
/// (incremented through copy constructors)
/// </summary>
//short noOfCopies = 0;
//short totalNoOfCopies = 0;

class SpaceInvaders : public GameSource
{
public:

	SpaceInvaders() { };
	~SpaceInvaders() { };

	short getScore() const override { return m_score; };
	void setScore(int value) override { this->m_score = value; }

	void initialiseGame() override;

	void gameLoop() override;

	void initialiseMissiles();

	void initialiseBarrierPositions();

	void initialiseAlienPositions();

	void setGamePositions(short width, short height);

	void checkCollision(GameObject& initiator, short x, short y);

	void onAlienKilled(Alien alien);

	void processInput();

	void updateGame();

private:
	int m_score;

	Ground m_gameGround;

	std::unique_ptr<Player> m_player = std::make_unique<Player>();
};