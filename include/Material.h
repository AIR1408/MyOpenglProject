#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>
#include <memory>
#include <string>

#include <glm/vec3.hpp>

#include <ShaderProgram.h>
#include <Texture.h>

class Material
{
public:
	Material();

	void setName(std::string name);
	void setAmbient(glm::vec3 ambient);
	void setDiffuse(glm::vec3 diffuse);
	void setSpecular(glm::vec3 specular);
	void setShininess(float shininess);
	
	void addMap(std::shared_ptr<Texture> map, char type = ' ');

	std::string getName();
	glm::vec3   getAmbient();
	glm::vec3   getDiffuse();
	glm::vec3   getSpecular();
	float       getShininess();
	//std::shared_ptr<Texture> getMap(int index);


	void useLightings(ShaderProgram& shader);
	void useTextureMaps();
	void use(ShaderProgram& shader);

private:
	std::string name;
	glm::vec3 ambient, diffuse, specular;

	float shininess;

	std::vector<std::shared_ptr<Texture>> maps;
};

#endif // !MATERIAL_H
