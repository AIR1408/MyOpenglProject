#include <Texture.h>

Texture::Texture(unsigned char* pixels, GLuint width, GLuint height, GLuint channels)
{
    id = 0, type = 0;
    GLenum gl_channels = (channels == 4 ? GL_RGBA : GL_RGB);

    glGenTextures(1, &id);

    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, gl_channels, GL_UNSIGNED_BYTE, pixels);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setID(GLuint id)
{
    this->id = id;
}

void Texture::setType(GLchar type)
{
    this->type = type;
}

void Texture::setParameters(std::vector<TextureParameter> parameters)
{
    glBindTexture(GL_TEXTURE_2D, id);

    for (const auto& parameter : parameters)
        glTexParameteri(GL_TEXTURE_2D, parameter.type, parameter.value);

    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getID()
{
    return id;
}

GLchar Texture::getType()
{
    return type;
}
