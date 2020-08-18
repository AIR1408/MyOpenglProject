#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <glad/glad.h>

#include "../extra/extra.h"
#include "../renderer/ShaderProgram.h"
#include "../renderer/Model.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#define STB_IMAGE_STATIC
#include "stb_image.h"

using ext::GROUP;
using ext::OBJECT;

enum ReadingMode
{
	ERROR,
	NON_DECL,
	OBJECT_DECL,
	OBJECT_GROUP_DECL,
	GROUP_DECL,
};

class ResourceManager
{
public:
	ResourceManager(std::string resourcePath);
	std::string loadShader(std::string fileName);
	ext::Texture* loadTexture(std::string fileName);
	ShaderProgram& loadProgram();
	std::vector<OBJECT> loadObject(std::string fileName);
	Model* loadObjectMinimum(std::string fileName);
	
private:
	std::string resourcePath;
};

#endif // !RESOURCE_MANAGER_H
