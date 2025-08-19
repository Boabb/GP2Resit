#pragma once
#include "GameObject.h"

//IS LIST ITEM
class Barrier : public GameObject
{
public:
	Barrier() { };
	Barrier(short xPosition, short yPosition) : GameObject(xPosition, yPosition) {};

	bool getIsActive() const override{ return isActive; };
	void setActive(bool active) override { this->isActive = active; };

	short getListIndex() const { return listIndexIncrement; };
	void setListIndex(short value) { this->listIndexIncrement = value; }

	char draw() const override { return '='; };

private:
	bool isActive;
	short listIndexIncrement;
};

