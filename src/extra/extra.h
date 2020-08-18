#ifndef EXTRA_H
#define EXTRA_H

#include <iostream>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace ext 
{
    struct Vertex 
    {
        glm::vec3 position = { 0.0, 0.0, 0.0 };
        glm::vec3 normal = { 0.0, 0.0, 0.0 };
        glm::vec2 texCoord = { 0.0, 0.0 };
    };

    struct Texture {
        unsigned int id;
        std::string type = "";
    };

    struct GROUP
    {
        std::string name;
        std::vector<ext::Vertex> vertices;
    };

    struct OBJECT
    {
        std::string name;
        std::vector<GROUP> groups;
    };

    void err(std::string msg);
}

#endif // !EXTRA_H
