#include "shaderProgram.h"

ShaderProgram::ShaderProgram(std::string& vertex_shader_source, std::string& fragment_shader_source)
{
    sp_ID = glCreateProgram();

    linkShader(vertex_shader_source, GL_VERTEX_SHADER);
    linkShader(fragment_shader_source, GL_FRAGMENT_SHADER);
    glLinkProgram(sp_ID);
    glGetProgramiv(sp_ID, GL_LINK_STATUS, &success);
    if (!success) 
    {
        glGetProgramInfoLog(sp_ID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED "  << infoLog << std::endl;
        exit(-1);
    }
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(sp_ID);
}

bool ShaderProgram::draw()
{
    glUseProgram(sp_ID);
    return true;
}

void ShaderProgram::linkShader(std::string& shader_source, GLenum shader_type)
{
    GLuint shader_ID = glCreateShader(shader_type);
    const GLchar* code = shader_source.c_str();
    glShaderSource(shader_ID, 1, &code, nullptr);
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
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED " << infoLog << std::endl;
    }
}
