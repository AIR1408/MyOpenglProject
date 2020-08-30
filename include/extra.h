#ifndef EXTRA_H
#define EXTRA_H

#include <vector>
#include <string>
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

    struct Group
    {
        std::string name = "default";
        std::vector<ext::Vertex> vertices;
        unsigned int material_id = 0;
    };

    struct Object
    {
        std::string name = "default";
        std::vector<Group> groups;
    };

}

#endif // !EXTRA_H
