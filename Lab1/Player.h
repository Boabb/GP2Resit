#pragma once
#include <iostream>
#include <string>
#include "Missile.h"

class Player : public GameObject
{
public:
	Player() { };
	Player(short xPosition, short yPosition) : GameObject(xPosition, yPosition) {}

	void update();

	void fireMissile(Missile& missile) const;

	bool getIsActive() const override { return isActive; };
	void setActive(bool active) override { this->isActive = active; };

	char draw() const override { return '^'; };

	float shootCooldown;

private:
	bool isActive;
};

