#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <vector>

#include "../extra/extra.h"

enum DrawingMode
{
	NONE,
	VERT,
	VERT_IND,
};

class Mesh
{
public:
	Mesh(std::vector<ext::Vertex> vertices);
	Mesh(std::vector<ext::Vertex> vertices, std::vector<ext::Texture> textures);
	Mesh(std::vector<ext::Vertex> vertices, std::vector<GLuint> indices, std::vector<ext::Texture> textures);
	~Mesh();

	void draw();
	
private:
	std::vector<ext::Vertex> vertices = std::vector<ext::Vertex>();
	std::vector<GLuint> indices = std::vector<GLuint>();
	std::vector<ext::Texture> textures = std::vector<ext::Texture>();

	GLuint vao, vbo, ebo;

	void setupMesh();
	DrawingMode mode = NONE;
};

#endif // !MESH_H
