#pragma once

#include <glad/glad.h>

class Mesh
{
public:
	Mesh(GLfloat* vertex, GLuint sizev_bytes, GLuint* index, GLuint sizei_bytes, GLenum draw_type);
	~Mesh();

	void setTexture(GLuint* texture);
	void draw();

private:
	GLuint
		vao, vbo, ebo,
		sizei;
	GLuint* texture = nullptr;
};