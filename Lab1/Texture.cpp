#include "Texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <glm/vec3.hpp>

Texture::Texture()
{
}

void Texture::init(const std::string& fileName)
{
	int width, height, numComponents; //width, height, and no of components of image
	unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4); //load the image and store the data

	if (imageData == NULL)
	{
		std::cerr << "texture load failed" << fileName << std::endl;
	}

	glGenTextures(1, &textureHandler); // number of and address of textures
	glBindTexture(GL_TEXTURE_2D, textureHandler); //bind texture - define type 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // wrap texture outside width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // wrap texture outside height

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // linear filtering for minification (texture is smaller than area)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // linear filtering for magnifcation (texture is larger)

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData); //Target, Mipmapping Level, Pixel Format, Width, Height, Border Size, Input Format, Data Type of Texture, Image Data

	stbi_image_free(imageData);
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureHandler); // number of and address of textures
}

void Texture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31); /// check we are working with one of the 32 textures

	glActiveTexture(GL_TEXTURE0 + unit); //set acitve texture unit
	glBindTexture(GL_TEXTURE_2D, textureHandler); //type of and texture to bind to unit
}

// Simple MTL parser (expand as needed)
struct Material {
    std::string name;
    glm::vec3 diffuse;
    std::string diffuseMap;
};

std::map<std::string, Material> LoadMTL(const std::string& filename) {
    std::map<std::string, Material> materials;
    std::ifstream file(filename);
    std::string line, currentName;
    Material mat;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        iss >> key;
        if (key == "newmtl") {
            if (!currentName.empty()) materials[currentName] = mat;
            iss >> currentName;
            mat = Material();
            mat.name = currentName;
        } else if (key == "Kd") {
            iss >> mat.diffuse.r >> mat.diffuse.g >> mat.diffuse.b;
        } else if (key == "map_Kd") {
            iss >> mat.diffuseMap;
        }
    }
    if (!currentName.empty()) materials[currentName] = mat;
    return materials;
}
