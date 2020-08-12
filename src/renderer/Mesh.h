#pragma once

#include <glad/glad.h>
#include <vector>

#include "../extra/extra.h"

class Mesh
{
public:
	Mesh(std::vector<ext::Vertex> vertices, std::vector<GLuint> indeces, std::vector<ext::Texture> textures);
	~Mesh();

	void draw();

private:
	std::vector<ext::Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<ext::Texture> textures;

	GLuint vao, vbo, ebo;

	void setupMesh();
};