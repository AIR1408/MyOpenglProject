#ifndef MESH_H
#define MESH_H

#include <vector>

#include <glad/glad.h>

#include <extra.h>
#include <ShaderProgram.h>
#include <Texture.h>

class Mesh
{
public:
	Mesh(std::vector<ext::Vertex> vertices);
	~Mesh();

	void setIndices(std::vector<GLuint> indices);
	void setTexture(std::vector<std::shared_ptr<Texture>> textures);
	void setMaterialID(GLuint material_id);

	GLuint getMaterialID();

	void Draw(ShaderProgram& program);
	
private:
	std::vector<std::shared_ptr<Texture>> textures;

	GLuint 
		VAO, VBO, IBO,
		numberOfVertices, numberOfIndices, material_id;
};

#endif // !MESH_H
