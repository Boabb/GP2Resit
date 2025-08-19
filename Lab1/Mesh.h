#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"
#include "transform.h"

struct Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	glm::vec3 GetPos() { return pos; }
	glm::vec2 GetTexCoord() { return texCoord; }
	glm::vec3 GetNormal() { return normal; }

	glm::vec3 normal;

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	Transform transform;

	void draw();
	void drawVertexes();
	void loadVertexs(Vertex* vertices, unsigned int numVertices);
	void init(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	void loadModel(const std::string& filename);
	void loadModel(const std::string& filename, Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	void initModel(const IndexedModel& model);
	void initFromIndexedModelFlat(const IndexedModel& model);

private:

	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS]; // create our array of buffers
	unsigned int drawCount; //how much of the vertexArrayObject do we want to draw
};

