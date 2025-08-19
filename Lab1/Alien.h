#pragma once
#include <vector>
#include "RandomEngine.h"
#include "GameObject.h"
#include "GameSource.h"
#include "Macros.h"
#include "Missile.h"

//IS LIST ITEM
extern short alienDirection;

static std::vector<Missile> enemyMissiles(MAXAMOUNTOFENEMYMISSILES);

class Alien : public GameObject
{
public:
	Alien() { };

	Alien(short xPosition, short yPosition) : GameObject(xPosition, yPosition), position{ xPosition, yPosition } { shootCooldown = 75; }

	~Alien() { this->isActive = false; };

	bool getIsActive() const override { return isActive; };
	void setActive(bool active) override { this->isActive = active; };

	short getListIndex() const { return listIndexIncrement; };
	void setListIndex(short value) { this->listIndexIncrement = value; }

    static void setAlienSpeed(const float _v)
    {
        alienSpeed() = _v;
    }

    static const float& getAlienSpeed()
    {
        return alienSpeed();
    }

	char draw() const override { return 'A'; };

	void setPosition(short x, short y);

	void update();

	void shoot(Missile& missile);

	Position position;

	static std::shared_ptr<short> direction;
	static float timeUntilMove;
	short shootCooldown = 100;

private:        
    static float& alienSpeed()
    {
        static float v = 0;
        return v;
    }

	bool isActive;
	short listIndexIncrement;
};

