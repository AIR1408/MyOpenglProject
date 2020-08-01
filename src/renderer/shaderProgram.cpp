#include "shaderProgram.h"
#include <iostream>
#include "../extra/extra.h"

ShaderProgram::ShaderProgram(const GLchar*& vertex_shader_source, const GLchar*& fragment_shader_source)
{
    sp_ID = glCreateProgram();
    linkShader(vertex_shader_source, GL_VERTEX_SHADER);
    linkShader(fragment_shader_source, GL_FRAGMENT_SHADER);
    glLinkProgram(sp_ID);
    glGetProgramiv(sp_ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(sp_ID, 512, nullptr, infoLog);
        ext::err(strcat("ERROR::SHADER::PROGRAM::LINKING_FAILED ", infoLog));
    }
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(sp_ID);
}

bool ShaderProgram::use()
{
    glUseProgram(sp_ID);
    return true;
}

void ShaderProgram::linkShader(const GLchar*& shader_source, const GLenum shader_type)
{
    GLuint shader_ID = glCreateShader(shader_type);
    glShaderSource(shader_ID, 1, &shader_source, nullptr);
    glCompileShader(shader_ID);
    glGetShaderiv(shader_ID, GL_COMPILE_STATUS, &success);
    if (success)
    {
        glAttachShader(sp_ID, shader_ID);
        glDeleteShader(shader_ID);
    }
    else 
    {
        glGetShaderInfoLog(shader_ID, 512, nullptr, infoLog);
        ext::err(strcat("ERROR::SHADER::COMPILATION_FAILED ", infoLog));
    }
}
