#include "Mesh.h"

Mesh::Mesh(std::vector<ext::Vertex> vertices)
{
    mode = VERT;

    this->vertices = vertices;

    setupMesh();
}

Mesh::Mesh(std::vector<ext::Vertex> vertices, std::vector<ext::Texture> textures)
{
    mode = VERT;

    this->vertices = vertices;
    this->textures = textures;

    setupMesh();
}

Mesh::Mesh(std::vector<ext::Vertex> vertices, std::vector<GLuint> indices, std::vector<ext::Texture> textures)
{
    mode = VERT_IND;

    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
}

void Mesh::setupMesh()
{
    int noc = 1;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(ext::Vertex), &vertices[0], GL_DYNAMIC_DRAW);

    if (mode == VERT_IND)
    {
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_DYNAMIC_DRAW);
    }

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ext::Vertex), (void*)0);
    glVertexAttribPointer(noc, 3, GL_FLOAT, GL_FALSE, sizeof(ext::Vertex), (void*)offsetof(ext::Vertex, normal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ext::Vertex), (void*)offsetof(ext::Vertex, texCoord));


    glEnableVertexArrayAttrib(vao, 0);
    glEnableVertexArrayAttrib(vao, noc);
    glEnableVertexArrayAttrib(vao, 2);

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

void Mesh::draw()
{
    for (int i = 0; i < textures.size(); i++) 
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glBindVertexArray(vao);

    if (mode == VERT)
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    else if (mode == VERT_IND)
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

}
