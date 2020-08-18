#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include "ShaderProgram.h"

class Model
{
public:
	Model();
	~Model();

	void addMesh(Mesh* new_mesh);

	void Draw(ShaderProgram& program);
	friend Model* translateToModel(std::vector<ext::OBJECT> object_vec);

	glm::mat4 matrix = glm::mat3(1.0);
private:
	
	std::vector<Mesh*> meshes;
};

#endif // !MODEL_H