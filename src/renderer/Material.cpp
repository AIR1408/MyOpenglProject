#include <Material.h>

Material::Material() : shininess(1)
{

}

void Material::setName(std::string name)
{
	this->name = name;
}

void Material::setAmbient(glm::vec3 ambient)
{
	this->ambient = ambient;
}

void Material::setDiffuse(glm::vec3 diffuse)
{
	this->diffuse = diffuse;
}

void Material::setSpecular(glm::vec3 specular)
{
	this->specular = specular;
}

void Material::setShininess(float shininess)
{
	this->shininess = shininess;
}

/*void Material::setAmbientMap(std::shared_ptr<Texture> ambientMap)
{
	this->ambientMap = ambientMap;
}

void Material::setDiffuseMap(std::shared_ptr<Texture> diffuseMap)
{
	this->diffuseMap = diffuseMap;
}

void Material::setSpecularMap(std::shared_ptr<Texture> specularMap)
{
	this->specularMap = specularMap;
}*/

void Material::addMap(std::shared_ptr<Texture> map, char type)
{
	map->setType(type);
	maps.push_back(map);
}

std::string Material::getName()
{
	return name;
}

glm::vec3 Material::getAmbient()
{
	return ambient;
}

glm::vec3 Material::getDiffuse()
{
	return diffuse;
}

glm::vec3 Material::getSpecular()
{
	return specular;
}

float Material::getShininess()
{
	return shininess;
}
/*
std::shared_ptr<Texture> Material::getMap(int index)
{
	return maps[index];
}
*/
void Material::useLightings(ShaderProgram& shader)
{
	shader.setVector("material.ambient", ambient);
	shader.setVector("material.diffuse", diffuse);
	shader.setVector("material.specular", specular);
	shader.setFloat("material.shininess", shininess);
}

void Material::useTextureMaps()
{
	for (auto& map : maps)
	{
		switch (map->getType())
		{
		case 'a':
			glActiveTexture(GL_TEXTURE11);
			break;
		case 'd':
			glActiveTexture(GL_TEXTURE12);
			break;
		case 's':
			glActiveTexture(GL_TEXTURE13);
			break;
		}
		glBindTexture(GL_TEXTURE_2D, map->getID());
	}
}

void Material::use(ShaderProgram& shader)
{
	useLightings(shader);
	useTextureMaps();
}
