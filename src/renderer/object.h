#pragma once

#include <glad/glad.h>

class Object 
{
public:
	Object(GLfloat* points, GLfloat* colors, GLuint* indeces);
	~Object();

};