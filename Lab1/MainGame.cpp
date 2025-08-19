#include "MainGame.h"
#include "Camera.h"
#include "Skybox.h"
#include "AudioPlayer.h"
#include "RandomEngine.h"
#include "Texture.h"
#include <iostream>
#include <string>
#include <SDL/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <string>

struct Material {
    std::string name;
    glm::vec3 diffuse;
    std::string diffuseMap;
};

extern std::map<std::string, Material> LoadMTL(const std::string& filename);

Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
					Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
					Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };

unsigned int indices[] = { 0, 1, 2 };

MainGame::MainGame() : _gameState(GameState::PLAY), counter(0.0f)
{
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
    audioPlayer->play("res/background.wav");
    initSystems();
    gameLoop();
}

void MainGame::initSystems()
{
    _gameDisplay.initDisplay();
    RandomEngine randomEngine;
    int skyboxIndex = randomEngine.getRandomInt(0, 6);
    std::string basePath = "../res/Skybox/Skybox" + std::to_string(skyboxIndex) + "/";
    std::array<std::string, 6> faces = {
        basePath + "posx.jpg",
        basePath + "negx.jpg",
        basePath + "posy.jpg",
        basePath + "negy.jpg",
        basePath + "posz.jpg",
        basePath + "negz.jpg"
    };
    myCamera = std::make_unique<Camera>();
    skybox = std::make_unique<Skybox>(faces);
    audioPlayer = std::make_unique<AudioPlayer>();

    mesh1.loadModel("..\\res\\Sheep.obj", vertices, 3, indices, 3);
    mesh1.transform.SetPos(glm::vec3(-5, -5, 0));
    mesh1.transform.SetRot(glm::vec3(0, 180, 0));

    mesh2.loadModel("..\\res\\Pig.obj", vertices, 3, indices, 3);
    mesh2.transform.SetPos(glm::vec3(0, -5, 0));
    mesh2.transform.SetRot(glm::vec3(0, 180, 0));

    mesh3.loadModel("..\\res\\Horse.obj", vertices, 3, indices, 3);
    mesh3.transform.SetPos(glm::vec3(5, -5, 0));
    mesh3.transform.SetRot(glm::vec3(0, 180, 0));

    objectShader.init("..\\res\\objectShader");
    skyboxShader.init("..\\res\\skyboxShader");
    myCamera->initCamera(glm::vec3(0, 0, -10), 70.0f, (float)_gameDisplay.getWidth() / _gameDisplay.getHeight(), 0.01f, 1000.0f);
    counter = 0.0f;

    texture1.init("..\\res\\Sheep.jpg");
    texture2.init("..\\res\\Pig.jpg");
    texture3.init("..\\res\\Horse.jpg");

}

void MainGame::gameLoop()
{
    Uint32 lastTicks = SDL_GetTicks();
    const Uint32 targetFrameTime = 1000 / 60;
    while (_gameState == GameState::PLAY)
    {
        Uint32 frameStart = SDL_GetTicks();
        float deltaTime = (frameStart - lastTicks) / 1000.0f;
        lastTicks = frameStart;
        processInput(deltaTime);
        drawGame();
        Uint32 frameEnd = SDL_GetTicks();
        Uint32 frameDuration = frameEnd - frameStart;
        if (frameDuration < targetFrameTime)
        {
            SDL_Delay(targetFrameTime - frameDuration);
        }
    }
}

void MainGame::processInput(float deltaTime)
{
    SDL_Event evnt;
    const float moveSpeed = 5.0f * deltaTime;
    while (SDL_PollEvent(&evnt))
    {
        if (evnt.type == SDL_QUIT)
        {
            _gameState = GameState::EXIT;
        }
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_W])
    {
		glm::vec3 mesh1Pos = *mesh1.transform.GetPos();
		mesh1Pos.z -= moveSpeed;
        mesh1.transform.SetPos(mesh1Pos);
    }
    if (state[SDL_SCANCODE_S])
    {
        glm::vec3 mesh1Pos = *mesh1.transform.GetPos();
        mesh1Pos.z += moveSpeed;
        mesh1.transform.SetPos(mesh1Pos);
    }
    if (state[SDL_SCANCODE_A])
    {
        glm::vec3 mesh1Pos = *mesh1.transform.GetPos();
        mesh1Pos.x -= moveSpeed;
        mesh1.transform.SetPos(mesh1Pos);
    }
    if (state[SDL_SCANCODE_D])
    {
        glm::vec3 mesh1Pos = *mesh1.transform.GetPos();
        mesh1Pos.x += moveSpeed;
        mesh1.transform.SetPos(mesh1Pos);
    }
    int x, y;
    SDL_GetMouseState(&x, &y);
    static int lastX = x, lastY = y;
    float sensitivity = 0.5f;
    myCamera->Yaw((x - lastX) * sensitivity);
    myCamera->Pitch((lastY - y) * sensitivity);
    lastX = x;
    lastY = y;
}
void MainGame::drawGame()
{
    _gameDisplay.clearDisplay(0.5f, 0.5f, 0.5f, 1.0f);
    glm::mat4 view = glm::mat4(glm::mat3(myCamera->GetViewMatrix()));
    glm::mat4 proj = myCamera->GetProjectionMatrix();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    skyboxShader.Bind();
    glUniformMatrix4fv(glGetUniformLocation(skyboxShader.GetShaderProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(skyboxShader.GetShaderProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(proj));
    glUniform1i(glGetUniformLocation(skyboxShader.GetShaderProgram(), "skybox"), 0);
    skybox->draw(view, proj);

    objectShader.Bind();
    glUniform1i(glGetUniformLocation(objectShader.GetShaderProgram(), "textureSampler"), 0);
    glUniform3f(glGetUniformLocation(objectShader.GetShaderProgram(), "lightDir"), -0.2f, -1.0f, -0.3f);
    glUniform3f(glGetUniformLocation(objectShader.GetShaderProgram(), "lightColor"), 1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(objectShader.GetShaderProgram(), "ambientColor"), 0.5f, 0.5f, 0.5f);

    objectShader.Update(mesh1.transform, *myCamera);
    texture1.Bind(0);
    mesh1.drawVertexes();

    glm::vec3 mesh2Pos = glm::vec3(mesh2.transform.GetPos()->x, mesh2.transform.GetPos()->y, counter);
    mesh2.transform.SetPos(mesh2Pos);
    mesh2.transform.SetRot(glm::vec3(0, counter, 0));
    objectShader.Update(mesh2.transform, *myCamera);
    texture2.Bind(0);
    mesh2.drawVertexes();

    objectShader.Update(mesh3.transform, *myCamera);
    texture3.Bind(0);
    mesh3.drawVertexes();

    counter += 0.01f;

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    _gameDisplay.swapBuffer();
}
