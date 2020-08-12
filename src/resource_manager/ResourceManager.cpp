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

ext::Texture* ResourceManager::loadTexture(std::string FilePath)
{
    ext::Texture* texture = new ext::Texture;
    int width = 0, height = 0, channels = 0;
    GLenum chan;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load(FilePath.c_str(), &width, &height, &channels, 0);

    if (!pixels)
    {
        std::cerr << "Can't load image: " << FilePath << std::endl;
        return nullptr;
    }

    switch (channels)
    {
    case 3: chan = GL_RGB;
        break;
    case 4: chan = GL_RGBA;
        break;
    default: chan = GL_RGBA;
        break;
    }

    glGenTextures(1, &texture->id);

    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, chan, GL_UNSIGNED_BYTE, pixels);
    //glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    stbi_image_free(pixels);

    return texture;
}
