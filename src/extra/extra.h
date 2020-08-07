#pragma once

#include <iostream>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace ext 
{
    struct Vertex 
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoord;
    };

    struct Texture {
        unsigned int id;
        std::string type;
    };

    void err(std::string msg);
}