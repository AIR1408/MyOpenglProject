#include "Model.h"

Model::Model()
{
	
}

Model::~Model()
{
	
}

void Model::addMesh(Mesh* new_mesh)
{
	meshes.push_back(new_mesh);
}

void Model::Draw(ShaderProgram& program)
{
	program.setMatrix("model", matrix);
	for (int i = 0; i < meshes.size(); i++)
		meshes[i]->draw();
}

Model* translateToModel(std::vector<ext::OBJECT> object_vec)
{
	Model* m_model = new Model;

	for (int i = 0; i < object_vec.size(); i++)
	{
		for (int j = 0; j < object_vec[i].groups.size(); j++)
		{
			Mesh* m_mesh = new Mesh(object_vec[i].groups[j].vertices);
			m_model->addMesh(m_mesh);
			m_mesh = nullptr;
		}
	}
	return m_model;
}
