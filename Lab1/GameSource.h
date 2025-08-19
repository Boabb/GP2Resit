#pragma once
#pragma warning(disable : 4996)
#include <ctime>
#include <fstream>
#include "ScreenBuffer.h"
#include "Window.h"
#include "RandomEngine.h"

class GameSource
{
public:

	virtual void initialiseGame() abstract;

	virtual void gameLoop() abstract;

	virtual void setHighScore(short score);

	virtual void setScore(int value) abstract;

	virtual short getScore() const abstract;

	void drawGame(short width, short height);

	void updateGame();

	void gameOver();

	void swapBuffers();

	void createBuffers(short width, short height);

	ScreenBuffer m_frontBuffer;
	ScreenBuffer m_backBuffer;
	ScreenBuffer m_resetBuffer;

	Window m_gameWindow;

	enum GameState
	{
		STARTSCREEN,
		SPACEINVADERS,
		FROGGER,
		GAMEOVER,
		EXIT
	};

	std::unique_ptr<GameState> gameState = std::make_unique<GameState>();

};

