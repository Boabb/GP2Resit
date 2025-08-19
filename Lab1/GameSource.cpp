#include "GameSource.h"

void GameSource::createBuffers(short width, short height)
{
	m_frontBuffer = ScreenBuffer(width, height);
	m_backBuffer = ScreenBuffer(width, height);
	m_resetBuffer = ScreenBuffer(width, height);

	for (short i = 0; i < width; i++)
	{
		for (short j = 0; j < height; j++)
		{
			m_resetBuffer.setChar(i, j, ' ');
		}
	}

	m_frontBuffer = m_resetBuffer;
	m_backBuffer = m_resetBuffer;
}

void GameSource::swapBuffers()
{
	std::swap(m_frontBuffer, m_backBuffer);
	m_backBuffer = m_resetBuffer;
}

void GameSource::drawGame(short width, short height)
{
	std::cout << "Score: " << getScore();
	for (short i = 0; i < height; i++)
	{
		for (short j = 0; j < width; j++)
		{
			m_gameWindow.setCursorPosition(j, i);
			std::cout << m_frontBuffer.getChar(j, i);
		}
	}
}

void GameSource::gameOver()
{
	*gameState = GAMEOVER;

	setHighScore(getScore());

	system("cls");

	std::cout << "Game Over! Your final Score was: " << getScore() << std::endl;
	std::cout << "Press Esc to return to the Main Menu!";

	while (*gameState == GAMEOVER)
	{
		if (true)
		{
			*gameState = STARTSCREEN;
		}
	}
}

void GameSource::setHighScore(short score)
{
	std::ofstream input("high_score.txt", fstream::app);

	if (!input.is_open())
	{
		std::cout << "Unable to read high score file!" << std::endl;
		return;
	}

	time_t now;
	time(&now);
	char* dt = std::ctime(&now);

	input << "You achieved a score of: " << score << " at: " << dt << std::endl;
};