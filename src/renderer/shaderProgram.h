#pragma once

#include <glad/glad.h>
#include <iostream>

class ShaderProgram
{
public:
	ShaderProgram(std::string& vertex_shader_source, std::string& fragment_shader_source);
	~ShaderProgram();

	bool isCompiled() { return success; };
	bool draw();


private:
	GLuint sp_ID = 0;
	GLint success = false;
	GLchar infoLog[512];

	void linkShader(std::string& shader_source, GLenum shader_type);
};