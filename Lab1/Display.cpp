#include "Display.h"
#include <iostream>


Display::Display()
{
    sdlWindow = nullptr;
    screenWidth = 1024.0f;
    screenHeight = 768.0f;
}

Display::~Display()
{
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
}

float Display::getWidth() { return screenWidth; }
float Display::getHeight() { return screenHeight; }

void Display::returnError(std::string errorString)
{
    std::cout << errorString << std::endl;
    std::cout << "press any  key to quit...";
    int in;
    std::cin >> in;
    SDL_Quit();
}

void Display::swapBuffer()
{
    SDL_GL_SwapWindow(sdlWindow);
}

void Display::clearDisplay(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::initDisplay()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    sdlWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)screenWidth, (int)screenHeight, SDL_WINDOW_OPENGL);

    if (sdlWindow == nullptr)
    {
        returnError("window failed to create");
    }

    glContext = SDL_GL_CreateContext(sdlWindow);

    if (glContext == nullptr)
    {
        returnError("SDL_GL context failed to create");
    }

    SDL_GL_SetSwapInterval(1);

    GLenum error = glewInit();
    if (error != GLEW_OK)
    {
        returnError("GLEW failed to initialise");
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
}