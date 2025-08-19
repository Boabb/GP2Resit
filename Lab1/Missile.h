#pragma once
#include "GameObject.h"

//IS LIST ITEM
class Missile : public GameObject
{
public:
	Missile() : isActive(false), isEnemy(isEnemy) { position = { 0,0 }; }
	void update();

	bool getIsActive() const override { return isActive; };
	void setActive(bool active) override { this->isActive = active; };

	short getListIndex() const { return listIndexIncrement; };
	void setListIndex(short value) { this->listIndexIncrement = value; }

	char draw() const override { return '!'; };

	bool isEnemy;
	short acceleration/*= (isEnemy) ? 1 : -1*/; //Game coords are inverted - this has stopped working for some reason
private:
	bool isActive;
	short travelTime = 0;
	short listIndexIncrement;
};


