#include <Model.h>

Model::Model()
{

}

void Model::setMaterials(std::vector<Material> materials)
{
	this->materials = materials;
}

void Model::addMesh(std::shared_ptr<Mesh> new_mesh)
{
	meshes.push_back(new_mesh);
}

void Model::Draw(ShaderProgram& program)
{
	program.setMatrix("model", matrix);

	for (auto& mesh : meshes)
	{
		GLuint id = mesh->getMaterialID();
		if (id) materials[id].use(program);

		mesh->Draw(program);

		glActiveTexture(GL_TEXTURE11);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE12);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE13);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

Model translateToModel(std::vector<ext::Object>& objects)
{
	Model m_model;
	std::shared_ptr<Mesh> m_mesh(nullptr);

	for (const auto& object : objects)
		for (const auto& group : object.groups)
		{
			m_mesh = std::make_shared<Mesh>(group.vertices);
			m_mesh->setMaterialID(group.material_id);
			m_model.addMesh(m_mesh);
			m_mesh = nullptr;
		}

	return m_model;
}
