#ifndef MODEL_H
#define MODEL_H

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#define STBI_ONLY_PNG

#include <memory>

#include <Mesh.h>
#include <ShaderProgram.h>
#include <Material.h>

class Model
{
public:
	Model();

	void setMaterials(std::vector<Material> materials);

	void addMesh(std::shared_ptr<Mesh> new_mesh);

	void Draw(ShaderProgram& program);

	friend Model translateToModel(std::vector<ext::Object>& object_vec);

	glm::mat4 matrix = glm::mat3(1.0);
private:
	
	std::vector<std::shared_ptr<Mesh>> meshes;
	std::vector<Material> materials;
};

#endif // !MODEL_H