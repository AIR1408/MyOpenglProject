#include "ObjectMesh.h"

Mesh::Mesh(GLfloat* vertex, GLuint sizev_bytes, GLuint* index, GLuint sizei_bytes, GLenum draw_type)
{
    sizei = sizei_bytes / sizeof(index[0]);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizev_bytes, vertex, draw_type);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizei_bytes, index, draw_type);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(vertex[0]), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(vertex[0]), (void*)(3 * sizeof(vertex[0])));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(vertex[0]), (void*)(6 * sizeof(vertex[0])));


    glEnableVertexArrayAttrib(vao, 0);
    glEnableVertexArrayAttrib(vao, 1);
    glEnableVertexArrayAttrib(vao, 2);

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

void Mesh::setTexture(GLuint* texture)
{
    this->texture = texture;
}

void Mesh::draw()
{
    if (texture)
        glBindTexture(GL_TEXTURE_2D, *texture);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, sizei, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

