#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(std::string& vertex_shader_source, std::string& fragment_shader_source)
{
    shader_program_ID = glCreateProgram();

    linkShader(vertex_shader_source, GL_VERTEX_SHADER);
    linkShader(fragment_shader_source, GL_FRAGMENT_SHADER);
    glLinkProgram(shader_program_ID);
    glGetProgramiv(shader_program_ID, GL_LINK_STATUS, &success);
    if (!success) 
    {
        glGetProgramInfoLog(shader_program_ID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED "  << infoLog << std::endl;
        exit(-1);
    }
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(shader_program_ID);
}

void ShaderProgram::setInt(std::string name, GLuint value)
{
    glUniform1i(glGetUniformLocation(shader_program_ID, name.c_str()), value);
}

void ShaderProgram::setVector(std::string name, glm::vec3 vector)
{
    glUniform3f(glGetUniformLocation(shader_program_ID, name.c_str()), vector.x, vector.y, vector.z);
}

void ShaderProgram::setMatrix(std::string name, glm::mat4 matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(shader_program_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

bool ShaderProgram::use()
{
    glUseProgram(shader_program_ID);
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
        glAttachShader(shader_program_ID, shader_ID);
        glDeleteShader(shader_ID);
    }
    else 
    {
        glGetShaderInfoLog(shader_ID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED " << infoLog << std::endl;
    }
}
