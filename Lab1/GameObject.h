#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>

struct Position {
	short x;
	short y;

	bool operator==(const Position& other) const {
		return x == other.x && y == other.y;
	}
};

class GameObject
{
public:
	GameObject() { };
	GameObject(short x) : position{ x, position.y } {};
	GameObject(short xPosition, short yPosition)
		: position{ xPosition, yPosition }
	{
	}

	virtual Position getPosition() const
	{
		return this->position;
	}

	virtual void setPosition(short x, short y)
	{
		this->position.x = x;
		this->position.y = y;
	}

	//virtual void update();
	virtual bool getIsActive() const = 0;
	virtual void setActive(bool active) = 0;

	virtual char draw() const abstract = 0;

	Position position;

};



