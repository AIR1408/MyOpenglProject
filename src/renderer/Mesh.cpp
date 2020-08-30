#include <Mesh.h>

Mesh::Mesh(std::vector<ext::Vertex> vertices) : VAO(0), VBO(0), IBO(0),
                                                numberOfVertices(0), numberOfIndices(0), material_id(0)
{
    numberOfVertices = vertices.size();

    int m = 1;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(ext::Vertex), &vertices[0], GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ext::Vertex), (void*)0);
    glVertexAttribPointer(m, 3, GL_FLOAT, GL_FALSE, sizeof(ext::Vertex), (void*)offsetof(ext::Vertex, normal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ext::Vertex), (void*)offsetof(ext::Vertex, texCoord));

    glEnableVertexArrayAttrib(VAO, 0);
    glEnableVertexArrayAttrib(VAO, m);
    glEnableVertexArrayAttrib(VAO, 2);

    glBindVertexArray(0);
}

void Mesh::setIndices(std::vector<GLuint> indices)
{
    numberOfIndices = indices.size();

    glBindVertexArray(VAO);

    glGenBuffers(1, &IBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_DYNAMIC_DRAW);

    glBindVertexArray(0);
}

void Mesh::setTexture(std::vector<std::shared_ptr<Texture>> textures)
{
    this->textures = textures;
}

void Mesh::setMaterialID(GLuint material_id)
{
    this->material_id = material_id;
}

GLuint Mesh::getMaterialID()
{
    return material_id;
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    glDeleteVertexArrays(1, &VAO);
}

void Mesh::Draw(ShaderProgram& program)
{
    for (unsigned int i = 0; i < textures.size(); i++) 
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures[i]->getID());
    }

    glBindVertexArray(VAO);

    if (IBO)
        glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, 0);
    else
        glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);

    glBindVertexArray(0);
    
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
