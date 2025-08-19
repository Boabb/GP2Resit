#pragma once
#include <SDL/SDL.h>
#include <string>
#include <GL/glew.h>

class Display
{
public:
	Display();
	~Display();

	void initDisplay();
	void clearDisplay(float r, float g, float b, float a);
	void swapBuffer();
	float getWidth();
	float getHeight();

private:
	void returnError(std::string errorString);
	SDL_Window* sdlWindow;
	SDL_GLContext glContext;
	float screenWidth;
	float screenHeight;
};

