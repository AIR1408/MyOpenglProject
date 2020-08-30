#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#define STBI_ONLY_PNG

#include <sstream>
#include <fstream>

#include <extra.h>
#include <ShaderProgram.h>
#include <Texture.h>
#include <Material.h>

using ext::Group;
using ext::Object;

class ResourceManager
{
public:
	ResourceManager(std::string resourcePath);

	std::string				 loadShaderFromFile(std::string fileName);
	std::shared_ptr<Texture> loadTextureFromFile(std::string fileName);
	void					 loadObjectFromFile(std::string fileName, std::vector<Object>& objects, std::vector<Material>& materials);
	void					 loadMaterialFromFile(std::string fileName, std::vector<Material>& materials);

	ShaderProgram&			 loadShaderProgram();
	
private:

	bool					 readNextLineFromFile(std::ifstream& fin, std::stringstream& stream);
	float					 loadFloatFromLine(std::stringstream& stream);
	glm::vec2				 readVec2FromLine(std::stringstream& stream);
	glm::vec3				 readVec3FromLine(std::stringstream& stream);
	std::shared_ptr<Texture> loadTextureInLine(std::stringstream& stream);
	


	std::string resourcePath;
};

#endif // !RESOURCE_MANAGER_H
