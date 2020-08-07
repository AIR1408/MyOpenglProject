#pragma once

#include <glad/glad.h>
#include <iostream>
#include <glm/vec3.hpp>

class ShaderProgram
{
public:
	ShaderProgram(std::string& vertex_shader_source, std::string& fragment_shader_source);
	~ShaderProgram();

	void setInt(std::string name, GLuint value);
	void setVector(std::string name, glm::vec3 vector);
	void setMatrix(std::string name, GLfloat* value);
	bool isCompiled() { return success; };
	bool use();


private:
	GLuint shader_program_ID = 0;
	GLint success = false;
	GLchar infoLog[512];

	void linkShader(std::string& shader_source, GLenum shader_type);
};