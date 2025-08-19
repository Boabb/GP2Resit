#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <array>

class Skybox {
public:
    Skybox(const std::array<std::string, 6>& faces);
    ~Skybox();
    void draw(const glm::mat4& view, const glm::mat4& projection);
private:
    GLuint cubemapTexture;
    GLuint VAO, VBO;
    void loadCubemap(const std::array<std::string, 6>& faces);
};
