#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#define STB_IMAGE_STATIC
#include "stb_image.h"

class ResourceManager
{
public:
	std::string loadSource(char* FilePath);
	GLuint* loadTexture(std::string FilePath);
private:

};