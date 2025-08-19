#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include <memory>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "Camera.h"
#include "Skybox.h"
#include "AudioPlayer.h"
#include <glm/glm.hpp>

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:

	void initSystems();
	void processInput(float deltaTime);
	void gameLoop();
	void drawGame();

	Display _gameDisplay;
	GameState _gameState;
	Mesh mesh1;
	Mesh mesh2;
	Mesh mesh3;
	std::unique_ptr<Camera> myCamera;
	Texture texture1; 
	Texture texture2;
	Texture texture3;
	Shader objectShader; 
	Shader skyboxShader; 
	std::unique_ptr<Skybox> skybox;
	std::unique_ptr<AudioPlayer> audioPlayer;
	float counter;
};

