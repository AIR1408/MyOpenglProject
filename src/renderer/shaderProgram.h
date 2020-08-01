#pragma once
#include <glad/glad.h>

class ShaderProgram {
public:
	ShaderProgram(const GLchar*& vertex_shader_source, const GLchar*& fragment_shader_source);
	~ShaderProgram();

	bool isCompiled() { return success; };
	bool use();


private:
	GLuint sp_ID = 0;
	GLint success = false;
	GLchar infoLog[512];

	void linkShader(const GLchar*& shader_source, const GLenum shader_type);
};