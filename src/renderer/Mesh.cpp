#include "Mesh.h"

Mesh::Mesh(std::vector<ext::Vertex> vertices, std::vector<GLuint> indices)
{
    this->vertices = vertices;
    this->indices = indices;
    //this->textures = textures;

    setupMesh();
}

void Mesh::setupMesh()
{
    int noc = 1;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(ext::Vertex), &vertices[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices), &indices[0], GL_DYNAMIC_DRAW);

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
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

