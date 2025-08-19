#pragma once
#include <iostream>
#include <windows.h>

using namespace std;

class Window
{
public:	
	Window() {};

	void setWindow(short width, short height);

	void setCursorPosition(short x, short y);

	short getWidth() { return this->width; }

	short getHeight() { return this->height; }

	short width, height;	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
};