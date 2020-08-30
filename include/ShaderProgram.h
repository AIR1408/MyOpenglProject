#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <iostream>

#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

class ShaderProgram
{
public:
	ShaderProgram(std::string& vertex_shader_source, std::string& fragment_shader_source);
	~ShaderProgram();

	void setInt(std::string name, GLuint value);
	void setFloat(std::string name, GLfloat value);

	void setVector(std::string name, glm::vec3 vector);
	void setMatrix(std::string name, glm::mat4 matrix);
	bool isCompiled() { return success; };
	bool use();


private:
	GLuint shader_program_ID = 0;
	GLint success = false;
	GLchar infoLog[512];

	void linkShader(std::string& shader_source, GLenum shader_type);
};

#endif // !SHADER_PROGRAM_H
