#include "SpaceInvaders.h"

extern short menuChoice;

static std::vector<Alien> aliens(AMOUNTOFALIENS);
static std::vector<Barrier> barriers(AMOUNTOFBARRIERS);
static std::vector<Missile> playerMissiles(MAXAMOUNTOFMISSILES);

float Alien::timeUntilMove = ALIENMOVEFREQ;
shared_ptr<short> Alien::direction = std::make_shared<short>(alienDirection);
static short alienDirection = ALIENMOVEDIST;

static float alienSpeed = Alien::getAlienSpeed();

void SpaceInvaders::initialiseGame() 
{
	m_gameWindow.setWindow(WIDTH, HEIGHT);
	createBuffers(WIDTH, HEIGHT);
	initialiseMissiles();
	initialiseBarrierPositions();
	initialiseAlienPositions();
	//Set Player initial position
	m_player->setPosition(WIDTH / 2, HEIGHT - 2);
	setGamePositions(WIDTH, HEIGHT);
	gameLoop();
};

void SpaceInvaders::initialiseMissiles()
{
	for (short i = 0; i < MAXAMOUNTOFMISSILES; i++)
	{
		playerMissiles[i].acceleration = -1;
		playerMissiles[i].isEnemy = false;
		playerMissiles[i].setListIndex(i);
	}
	for (short i = 0; i < MAXAMOUNTOFENEMYMISSILES; i++)
	{
		enemyMissiles[i].acceleration = 1;
		enemyMissiles[i].isEnemy = true;
		enemyMissiles[i].setListIndex(i);
	}
}

void SpaceInvaders::initialiseBarrierPositions()
{
	short index = 0;
	for (short barrierSet = 1; barrierSet < 5; barrierSet++)
	{
		for (short barrierUnit = -2; barrierUnit < 3; barrierUnit++)
		{
			barriers[index].setPosition(barrierUnit + (WIDTH / 5 * barrierSet), BARRIER);
			barriers[index].setListIndex(index);
			index++;
		}
	}
}

void SpaceInvaders::initialiseAlienPositions()
{
	short index = 0;
	for (short xPosition = WIDTH / 2 - (DISTBETWEENALIENS * aliens.size() / 2); index < aliens.size(); xPosition += DISTBETWEENALIENS)
	{
		aliens[index].setListIndex(index);

		if (xPosition + alienDirection < WIDTH && alienDirection > -1)
		{
			aliens[index].position = { xPosition, 0 };
			aliens[index].direction = std::make_shared<short>(alienDirection = 3);
		}
		index++;
	}

};

void SpaceInvaders::setGamePositions(short width, short height)
{
	//Ground
	for (short i = 0; i < WIDTH; i++)
	{
		m_backBuffer.setChar(i, GROUND, Ground::draw());
	}

	//Barriers
	for (Barrier& barrier : barriers)
	{
		if (barrier.getIsActive())
		{
			//if Barriers position is contested
			if (!m_backBuffer.trySetChar(barrier.position.x, barrier.position.y, barrier.draw()))
			{
				checkCollision(barrier, barrier.position.x, barrier.position.y);
			}
		}
	}

	//Player
	if (m_player->getIsActive())
	{
		if (m_player->position.y <= BARRIER + 1)
		{
			m_player->position.y = BARRIER + 1;
		}
		//if Players position is contested
		if (!m_backBuffer.trySetChar(m_player->position.x, m_player->position.y, m_player->draw()))
		{
			checkCollision(*m_player, m_player->position.x, m_player->position.y);
		}
	}

	//Aliens
	for (Alien& alien : aliens)
	{
		if (alien.getIsActive())
		{
			//if Aliens position is contested
			if (!m_backBuffer.trySetChar(alien.position.x, alien.position.y, alien.draw()))
			{
				checkCollision(alien, alien.position.x, alien.position.y);
			}
		}
	}

	//Missiles
	for (Missile& missile : playerMissiles)
	{
		if (missile.getIsActive())
		{
			missile.update();
			//if Missiles new position is contested
			if (!m_backBuffer.trySetChar(missile.position.x, missile.position.y, missile.draw()))
			{
				checkCollision(missile, missile.position.x, missile.position.y);
			}
		}
	}

	for (Missile& missile : enemyMissiles)
	{
		if (missile.getIsActive())
		{
			missile.update();
			//if Missiles new position is contested
			if (!m_backBuffer.trySetChar(missile.position.x, missile.position.y, missile.draw()))
			{
				checkCollision(missile, missile.position.x, missile.position.y);
			}
		}
	}
};

void SpaceInvaders::checkCollision(GameObject& initiator, short x, short y)
{
	if (initiator.getIsActive())
	{
		bool destroySelf = false;
		//Player/Alien Collision
		if (typeid(initiator) == typeid(Player) && m_backBuffer.getChar(x, y) == aliens[0].draw())
		{
			destroySelf = true;
			for (Alien& alien : aliens)
			{
				if (alien.position == Position{ x, y } && alien.getIsActive())
				{
					onAlienKilled(alien);
					break;
				}
			}
			*gameState = GAMEOVER;
		}
		//Player/Barrier Collision
		else if (typeid(initiator) == typeid(Player) && m_backBuffer.getChar(x, y) == playerMissiles[0].draw())
		{
			for (Barrier& barrier : barriers)
			{
				if (barrier.position == Position{ x, y } && barrier.getIsActive())
				{
					m_player->position.y--;
					m_backBuffer.setChar(x, y--, '^');
				}
			}
		}
		//Player/Ground Collision
		else if (typeid(initiator) == typeid(Player) && m_backBuffer.getChar(x, y) == Ground::draw())
		{
			m_player->position.y++;
			m_backBuffer.setChar(x, y++, '^');

		}
		//Alien/Barrier Collision
		else if (typeid(initiator) == typeid(Alien) && m_backBuffer.getChar(x, y) == barriers[0].draw())
		{
			destroySelf = true;
			for (Barrier& barrier : barriers)
			{
				barrier.setActive(false);
			}
		}
		//Missile/Alien Collision
		else if (typeid(initiator) == typeid(Missile) && m_backBuffer.getChar(x, y) == aliens[0].draw())
		{
			destroySelf = true;
			for (Missile& missile : playerMissiles)
			{
				if (missile.position == initiator.position && missile.getIsActive())
				{
					missile.setActive(false);

					for (Alien alien : aliens)
					{
						if (alien.position == Position{ x, y } && alien.getIsActive())
						{
							onAlienKilled(alien);
							break;
						}
					}
				}
			}
			m_backBuffer.setChar(x, y, ' ');
		}
		//Missile/Barrier Collision
		else if (typeid(initiator) == typeid(Missile) && m_backBuffer.getChar(x, y) == barriers[0].draw())
		{
			if (initiator.getIsActive())
			{
				destroySelf = true;
				for (Barrier& barrier : barriers)
				{
					if (barrier.position == Position{ x, y } && barrier.getIsActive())
					{
						barrier.setActive(false);
						break;
					}
				}
			}
		}
		//Missile/Player Collision
		else if (typeid(initiator) == typeid(Missile) && m_backBuffer.getChar(x, y) == m_player->draw())
		{
			if (initiator.getIsActive())
			{
				destroySelf = true;
				gameOver();
			}
		}
		//Missile/Missile Collision
		else if (typeid(initiator) == typeid(Missile) && m_backBuffer.getChar(x, y) == playerMissiles[0].draw())
		{
			if (initiator.getIsActive())
			{
				destroySelf = true;

				for (Missile& missile : playerMissiles)
				{
					if (missile.position == Position{ x, y } && missile.getIsActive())
					{
						missile.setActive(false);
						break;
					}
				}
				for (Missile& missile : enemyMissiles)
				{
					if (missile.position == Position{ x, y } && missile.getIsActive())
					{
						missile.setActive(false);
						break;
					}
				}
			}
		}
		if (destroySelf)
		{
			initiator.setActive(false);
			m_backBuffer.setChar(x, y, ' ');
		}
	}
};

void SpaceInvaders::onAlienKilled(Alien alien)
{
	aliens.erase(aliens.begin() + alien.getListIndex());

	for (short i = alien.getListIndex(); i < aliens.size(); i++)
	{
		aliens[i].setListIndex(i);
	}

	m_score += 1;

	if (aliens.empty())
	{
		m_score += 10;
		*gameState = GAMEOVER;
	}
}

void SpaceInvaders::processInput()
{
	m_player->update();
	m_player->shootCooldown -= 0.2;
	if (m_player->shootCooldown <= 0)
	{
		for (Missile& playerMissile : playerMissiles)
		{
			if (!playerMissile.getIsActive())
			{
				m_player->fireMissile(playerMissile);
				m_player->shootCooldown = MAXPLAYERSHOOTCOOLDOWN;
				return;
			}
		}
	}
};

void SpaceInvaders::updateGame()
{
	Alien::setAlienSpeed(.15f * (AMOUNTOFALIENS / aliens.size()));
	Alien::timeUntilMove -= Alien::getAlienSpeed();

	for (Alien& alien : aliens)
	{
		alien.update();
		if (alien.shootCooldown <= 0)
		{
			for (Missile& enemyMissile : enemyMissiles)
			{
				if (!enemyMissile.getIsActive())
				{
					alien.shoot(enemyMissile);
					alien.shootCooldown = MAXENEMYSHOOTCOOLDOWN;
				}
			}
		}
	}
	if (Alien::timeUntilMove <= 0)
	{
		Alien::timeUntilMove = ALIENMOVEFREQ;
		short increment = (alienDirection > 0) ? -1 : 1;
		short startingPosition = (alienDirection > 0) ? aliens.size() - 1 : 0;
		short endingPosition = (alienDirection > 0) ? -1 : aliens.size();
		for (short i = startingPosition; i != endingPosition; i += increment)
		{
			bool advance = false;
			//if adding alien speed onto this aliens position keeps within window boundaries
			if (aliens[i].position.x + alienDirection < WIDTH && aliens[i].position.x + alienDirection >= 0)
			{
				aliens[i].position.x += alienDirection;
			}

			//else if adding alien speed onto this aliens position breaches the right side of the window
			else if (aliens[i].position.x + alienDirection >= WIDTH)
			{
				aliens[i].position.x -= abs(alienDirection);

				advance = true;
				//Invert Alien movement horizontally
				alienDirection = -abs(alienDirection);
			}

			//else if adding alien speed onto this aliens position breaches the left side of the window
			else if (aliens[i].position.x + alienDirection < 0)
			{
				aliens[i].position.x += (abs(alienDirection));
				advance = true;

				//Invert Alien movement horizontally
				alienDirection = abs(alienDirection);
			}
			//if the aliens should advance
			if (advance)
			{
				for (Alien& alien : aliens)
				{
					//All Aliens advance one unit
					alien.position.y++;
					//Game Over if Aliens have reached the barriers
					if (alien.position.y == BARRIER)
					{
						*gameState = GAMEOVER;
					}
				}
			}
		}
	}
}

void SpaceInvaders::gameLoop()
{
	while (*gameState == GameState::SPACEINVADERS)
	{
		processInput();
		updateGame();
		setGamePositions(WIDTH, HEIGHT);
		swapBuffers();
		drawGame(WIDTH, HEIGHT);
	}
}