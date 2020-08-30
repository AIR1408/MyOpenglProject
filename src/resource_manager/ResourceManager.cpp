#include <ResourceManager.h>
#include <glad/glad.h>
#include <stb_image.h>

ResourceManager::ResourceManager(std::string resourcePath)
{
    this->resourcePath = resourcePath;
}

std::string ResourceManager::loadShaderFromFile(std::string fileName)
{
    std::ifstream fin(resourcePath + "\\shaders\\" + fileName);
    if (!fin.is_open())
    {
        std::cerr << "Can't open file " << fileName << std::endl;
        system("pause");
    }
    std::ostringstream buf;
    buf << fin.rdbuf();
    fin.close();
    return buf.str();
}

std::shared_ptr<Texture> ResourceManager::loadTextureFromFile(std::string fileName)
{
    std::string path = resourcePath + "\\textures\\" + fileName;
    int width = 0, height = 0, channels = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (!pixels)
    {
        std::cerr << "Can't load image: " << fileName << std::endl;
        system("pause");
    }

    std::shared_ptr<Texture> p_texture = std::make_shared<Texture>(pixels, width, height, channels);
    
    std::vector<TextureParameter> parameters =
    {
        {GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE},
        {GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE},
        {GL_TEXTURE_MAG_FILTER, GL_LINEAR},
        {GL_TEXTURE_MIN_FILTER, GL_LINEAR},
    };
    
    p_texture->setParameters(parameters);
    stbi_image_free(pixels);
    return p_texture;
}

ShaderProgram& ResourceManager::loadShaderProgram()
{
    std::string 
        vertex_shader = loadShaderFromFile("\\vertex.txt"), 
        fragment_shader = loadShaderFromFile("\\fragment.txt");

    ShaderProgram* ID = new ShaderProgram(vertex_shader, fragment_shader);
    return *ID;
}

void ResourceManager::loadObjectFromFile(std::string fileName, std::vector<Object>& objects, std::vector<Material>& materials)
{
    std::ifstream fin(resourcePath + "\\models\\" + fileName);
    if (!fin.is_open())
    {
        std::cerr << "ERROR::RESOURCE_MANAGER Cannot open file " << fileName << std::endl;
        system("pause");
    }
    std::string type, buf;
    std::stringstream line;

    unsigned int v_id = 0, n_id = 0, t_id = 0, material_id = 0;

    bool success = true;

    glm::vec3 tempVec3;
    glm::vec2 tempVec2;

    std::vector<glm::vec3> positions, normals;
    std::vector<glm::vec2> texCoords;

    ext::Vertex tempVertex;

    Group group;
    Object object;

    while (std::getline(fin, buf))
    {
        type = "";
        line.clear();
        line.str(buf);
        line >> type;
        if (type == "#" || type == "")
        {

        }
        else if (type == "v")
        {
            positions.push_back(readVec3FromLine(line));
        }
        else if (type == "vt")
        {
            texCoords.push_back(readVec2FromLine(line));
        }
        else if (type == "vn")
        {
            normals.push_back(readVec3FromLine(line));
        }
        else if (type == "f")
        {
            int vertex_counter = 0;
            while(!line.eof() && vertex_counter < 3 && success)
            {
                v_id = 0, n_id = 0, t_id = 0;
                int item_counter = 0;
                line >> buf;
                
                for (const auto& sym : buf)
                {
                    if (sym >= '0' && sym <= '9')
                    {
                        if (item_counter == 0) v_id = 10 * v_id + sym - '0';
                        else if (item_counter == 1) t_id = 10 * t_id + sym - '0';
                        else if (item_counter == 2) n_id = 10 * n_id + sym - '0';
                    }
                    else if (sym == '/') 
                    {
                        item_counter++;
                    }
                }

                if (v_id) tempVertex.position = positions[v_id - 1];
                else {
                    success = false;
                    std::cerr << "ERROR::RESOURCE_MANAGER .obj file syntax wrong - vertex position wasn't declared" << std::endl;
                }
                if (t_id) tempVertex.texCoord = texCoords[t_id - 1];
                if (n_id) tempVertex.normal = normals[n_id - 1];

                group.vertices.push_back(tempVertex);

                vertex_counter++;
            }
            //if (vertex_counter != 3) success = false;
        }
        else if (type == "o")
        {
            group.material_id = material_id;
            if (group.vertices.size())
                object.groups.push_back(group);
            if (object.groups.size())
                objects.push_back(object);
            group = Group(), object = Object();
            line >> buf;
            object.name = buf;
        }
        else if (type == "g")
        {
            group.material_id = material_id;
            if (group.vertices.size())
                object.groups.push_back(group);
            group = Group();
            line >> buf;
            group.name = buf;
        }
        else if (type == "usemtl")
        {
            line >> buf;
            bool t = true;
            for (unsigned int i = 1; i < materials.size() && t; i++)
                if (materials[i].getName() == buf)
                    material_id = i, t = false;
        }
        else if (type == "mtllib")
        {
            line >> buf;
            loadMaterialFromFile(buf, materials);
        }

    }
    if (group.vertices.size())
        object.groups.push_back(group);
    if (object.groups.size())
        objects.push_back(object);
    group = Group(), object = Object();
    if (!success)
    {
        std::cerr << "ERROR::READING obj file reading error." << std::endl;
        exit(-1);
    }

    fin.close();
}

void ResourceManager::loadMaterialFromFile(std::string fileName, std::vector<Material>& materials)
{
    std::ifstream fin(resourcePath + "\\models\\" + fileName);
    if (!fin.is_open())
    {
        std::cerr << "ERROR::RESOURCE_MANAGER Cannot open file " << fileName << std::endl;
        system("pause");
    }
    std::stringstream line;
    std::string buf, type;

    Material material = Material();

    while (readNextLineFromFile(fin, line))
    {
        type = "";
        line >> type;
        
        if (type == "newmtl")
        {
            line >> buf;
            materials.push_back(material);
            material = Material();
            material.setName(buf);
        }
        else if (type == "Ka")     material.setAmbient(readVec3FromLine(line));
        else if (type == "Kd")     material.setDiffuse(readVec3FromLine(line));
        else if (type == "Ks")     material.setSpecular(readVec3FromLine(line));
        else if (type == "Ns")     material.setShininess(loadFloatFromLine(line));
        else if (type == "map_Ka") material.addMap(loadTextureInLine(line), 'a');
        else if (type == "map_Kd") material.addMap(loadTextureInLine(line), 'd');
        else if (type == "map_Ks") material.addMap(loadTextureInLine(line), 's');
    }
    materials.push_back(material);
    fin.close();
}

glm::vec3 ResourceManager::readVec3FromLine(std::stringstream& stream)
{
    glm::vec3 tempVec3;
    stream >> tempVec3.x >> tempVec3.y >> tempVec3.z;
    return tempVec3;
}

glm::vec2 ResourceManager::readVec2FromLine(std::stringstream& stream)
{
    glm::vec2 tempVec2;
    stream >> tempVec2.x >> tempVec2.y;
    return tempVec2;
}

std::shared_ptr<Texture> ResourceManager::loadTextureInLine(std::stringstream& stream)
{
    std::string fileName;
    stream >> fileName;
    std::shared_ptr<Texture> tempTexture = loadTextureFromFile(fileName);
    return tempTexture;
}

float ResourceManager::loadFloatFromLine(std::stringstream& stream)
{
    float value;
    stream >> value;
    return value;
}

bool ResourceManager::readNextLineFromFile(std::ifstream& fin, std::stringstream& stream)
{
    std::string buffer;
    std::getline(fin, buffer);
    stream.clear();
    stream.str(buffer);
    return !fin.eof();
}
