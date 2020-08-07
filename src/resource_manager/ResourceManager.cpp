#include "ResourceManager.h"

std::string ResourceManager::loadSource(char* FilePath)
{
    std::ifstream fin(FilePath);
    if (!fin.is_open())
    {
        std::cerr << "Can't open file " << FilePath << std::endl;
        exit(-1);
    }
    std::ostringstream buf;
    buf << fin.rdbuf();
    fin.close();
    return buf.str();
}

GLuint* ResourceManager::loadTexture(std::string FilePath)
{
    int width = 0, height = 0, channels = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load(FilePath.c_str(), &width, &height, &channels, 0);

    if (!pixels)
    {
        std::cerr << "Can't load image: " << FilePath << std::endl;
        return nullptr;
    }

    GLuint* texture = new GLuint;
    glGenTextures(1, texture);

    glBindTexture(GL_TEXTURE_2D, *texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    stbi_image_free(pixels);

    return texture;
}
