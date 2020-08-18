#include "ResourceManager.h"

ResourceManager::ResourceManager(std::string resourcePath)
{
    this->resourcePath = resourcePath;
}

std::string ResourceManager::loadShader(std::string fileName)
{
    std::ifstream fin(resourcePath + "\\shaders\\" + fileName);
    if (!fin.is_open())
    {
        std::cerr << "Can't open file " << fileName << std::endl;
        exit(-1);
    }
    std::ostringstream buf;
    buf << fin.rdbuf();
    fin.close();
    return buf.str();
}

ext::Texture* ResourceManager::loadTexture(std::string fileName)
{
    std::string path = resourcePath + "\\textures\\" + fileName;
    ext::Texture* texture = new ext::Texture;
    int width = 0, height = 0, channels = 0;
    GLenum chan;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (!pixels)
    {
        std::cerr << "Can't load image: " << fileName << std::endl;
        return nullptr;
    }

    switch (channels)
    {
    case 3: chan = GL_RGB;
        break;
    case 4: chan = GL_RGBA;
        break;
    default: chan = GL_RGBA;
        break;
    }

    glGenTextures(1, &texture->id);

    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, chan, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    stbi_image_free(pixels);

    return texture;
}

ShaderProgram& ResourceManager::loadProgram()
{
    std::string 
        vertex_shader = loadShader("\\vertex.txt"), 
        fragment_shader = loadShader("\\fragment.txt");

    ShaderProgram* ID = new ShaderProgram(vertex_shader, fragment_shader);
    return *ID;
}

std::vector<OBJECT> ResourceManager::loadObject(std::string fileName)
{
    std::ifstream fin(resourcePath + "\\models\\" + fileName);
    if (!fin.is_open())
    {
        std::cerr << "ERROR::RESOURCE_MANAGER Cannot open file " << fileName << std::endl;
        exit(-1);
    }
    std::string type, vnt;

    unsigned int v_id = 0, n_id = 0, t_id = 0;

    bool success = true;

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> tex_coords;

    glm::vec3 pos;
    glm::vec3 norm;
    glm::vec2 tex_coord;

    ext::Vertex vert;

    GROUP m_group, d_group;
    OBJECT m_object, d_object;
    //d_object.groups.resize(1);

    std::vector<OBJECT> objects_vec;

    ReadingMode state = NON_DECL;

    while (fin >> type)
    {
        if (std::strcmp(type.c_str(), "v") == 0)
        {
            fin >> pos.x >> pos.y >> pos.z;
            positions.push_back(pos);
        }
        else if (std::strcmp(type.c_str(), "vt") == 0)
        {
            fin >> tex_coord.x >> tex_coord.y;
            tex_coords.push_back(tex_coord);
        }
        else if (std::strcmp(type.c_str(), "vn") == 0)
        {
            fin >> norm.x >> norm.y >> norm.z;
            normals.push_back(norm);
        }
        else if (std::strcmp(type.c_str(), "f") == 0)
        {
            for (int j = 0; j < 3 && success; j++)
            {
                v_id = 0, n_id = 0, t_id = 0;
                fin >> vnt;
                int q = 1;
                for (int i = 0; i < vnt.size() && q; i++)
                {
                    switch (q)
                    {
                    case 1:
                        if (vnt[i] >= '0' && vnt[i] <= '9')
                            v_id = 10 * v_id + vnt[i] - '0', q = 1;
                        else if (vnt[i] == '/')
                            q = 2;
                        else q = 0;
                        break;
                    case 2:
                        if (vnt[i] >= '0' && vnt[i] <= '9')
                            t_id = 10 * t_id + vnt[i] - '0', q = 3;
                        else if (vnt[i] == '/')
                            q = 4;
                        else q = 0, success = false;
                        break;
                    case 3:
                        if (vnt[i] >= '0' && vnt[i] <= '9')
                            t_id = 10 * t_id + vnt[i] - '0', q = 3;
                        else if (vnt[i] == '/')
                            q = 4;
                        else q = 0;
                        break;
                    case 4:
                        if (vnt[i] >= '0' && vnt[i] <= '9')
                            n_id = 10 * n_id + vnt[i] - '0', q = 5;
                        else q = 0, success = false;
                        break;
                    case 5:
                        if (vnt[i] >= '0' && vnt[i] <= '9')
                            n_id = 10 * n_id + vnt[i] - '0', q = 5;
                        else q = 0;
                        break;
                    }
                }

                if (v_id)
                    vert.position = positions[v_id - 1];
                else
                    success = false;
                    //std::cerr << "ERROR::RESOURCE_MANAGER .obj file syntax wrong - vertex position wasn't declared" << std::endl;
                if (t_id)
                    vert.texCoord = tex_coords[t_id - 1];
                if (n_id)
                    vert.normal = normals[n_id - 1];

                switch (state)
                {
                case ERROR:
                    break;
                case NON_DECL:
                    d_group.vertices.push_back(vert);
                    break;
                case OBJECT_DECL:
                    d_group.vertices.push_back(vert);
                    break;
                case OBJECT_GROUP_DECL:
                    m_group.vertices.push_back(vert);
                    break;
                case GROUP_DECL:
                    d_group.vertices.push_back(vert);
                    break;
                default:
                    break;
                }

            }
        }
        else if (std::strcmp(type.c_str(), "o") == 0)
        {
            switch (state)
            {
            case ERROR:
                break;
            case NON_DECL:
                state = OBJECT_DECL;
                if (d_group.vertices.size())
                    d_object.groups.push_back(d_group);
                if (d_object.groups.size())
                    objects_vec.push_back(d_object);
                d_group = GROUP(), m_object = OBJECT();
                break;
            case OBJECT_DECL:
                if (d_group.vertices.size())
                    m_object.groups.push_back(d_group);
                if (m_object.groups.size())
                    objects_vec.push_back(m_object);
                d_group = GROUP(), m_object = OBJECT();
                break;
            case OBJECT_GROUP_DECL:
                state = OBJECT_DECL;
                if (m_group.vertices.size())
                    m_object.groups.push_back(m_group);
                if (m_object.groups.size())
                    objects_vec.push_back(m_object);
                m_group = GROUP(), m_object = OBJECT();
                break;
            case GROUP_DECL:
                state = OBJECT_DECL;
                if (d_group.vertices.size())
                    d_object.groups.push_back(d_group);
                if (d_object.groups.size())
                    objects_vec.push_back(d_object);
                d_object = OBJECT();
                m_group = GROUP(), m_object = OBJECT();
                break;
            default:
                break;
            }
        }
        else if (std::strcmp(type.c_str(), "g") == 0)
        {
            switch (state)
            {
            case ERROR:
                break;
            case NON_DECL:
                state = GROUP_DECL;
                if (d_group.vertices.size())
                    d_object.groups.push_back(d_group);
                break;
            case OBJECT_DECL:
                state = OBJECT_GROUP_DECL;
                if (d_group.vertices.size())
                    m_object.groups.push_back(d_group);
                m_group = GROUP();
                break;
            case OBJECT_GROUP_DECL:
                if (m_group.vertices.size())
                    m_object.groups.push_back(m_group);
                m_group = GROUP();
                break;
            case GROUP_DECL:
                if (d_group.vertices.size())
                    d_object.groups.push_back(d_group);
                d_group = GROUP();
                break;
            default:
                break;
            }
        }
        fin.ignore(128, '\n');
    }
    switch (state)
    {
    case ERROR:
        break;
    case NON_DECL:
        if (d_group.vertices.size())
            d_object.groups.push_back(d_group);
        if (d_object.groups.size())
            objects_vec.push_back(d_object);
        d_group = GROUP(), d_object = OBJECT();
        break;
    case OBJECT_DECL:
        if (d_group.vertices.size())
            m_object.groups.push_back(d_group);
        if (m_object.groups.size())
            objects_vec.push_back(m_object);
        m_object = OBJECT();
        break;
    case OBJECT_GROUP_DECL:
        if (m_group.vertices.size())
            m_object.groups.push_back(m_group);
        if (m_object.groups.size())
            objects_vec.push_back(m_object);
        m_group = GROUP(), m_object = OBJECT();
        break;
    case GROUP_DECL:
        if (d_group.vertices.size())
            d_object.groups.push_back(d_group);
        if (d_object.groups.size())
            objects_vec.push_back(d_object);
        d_group = GROUP(), d_object = OBJECT();
        break;
    default:
        break;
    }
    if (!success)
    {
        std::cerr << "ERROR::READING obj file reading error." << std::endl;
        exit(-1);
    }

    fin.close();
    return objects_vec;
}

Model* ResourceManager::loadObjectMinimum(std::string fileName)
{
    std::ifstream fin(resourcePath + "\\models\\" + fileName);
    if (!fin.is_open())
    {
        std::cerr << "ERROR::RESOURCE_MANAGER Cannot open file " << fileName << std::endl;
        exit(-1);
    }
    std::string type, vnt;

    unsigned int v_id = 0, n_id = 0, t_id = 0;

    bool success = true;

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> tex_coords;

    glm::vec3 pos;
    glm::vec3 norm;
    glm::vec2 tex_coord;

    ext::Vertex vert;
    std::vector<ext::Vertex> vertices;

    while (fin >> type)
    {
        if (std::strcmp(type.c_str(), "v") == 0)
        {
            fin >> pos.x >> pos.y >> pos.z;
            positions.push_back(pos);
        }
        else if (std::strcmp(type.c_str(), "vt") == 0)
        {
            fin >> tex_coord.x >> tex_coord.y;
            tex_coords.push_back(tex_coord);
        }
        else if (std::strcmp(type.c_str(), "vn") == 0)
        {
            fin >> norm.x >> norm.y >> norm.z;
            normals.push_back(norm);
        }
        else if (std::strcmp(type.c_str(), "f") == 0)
        {
            for (int j = 0; j < 3 && success; j++)
            {
                v_id = 0, n_id = 0, t_id = 0;
                fin >> vnt;
                int q = 1;
                for (int i = 0; i < vnt.size() && q; i++)
                {
                    switch (q)
                    {
                    case 1:
                        if (vnt[i] >= '0' && vnt[i] <= '9')
                            v_id = 10 * v_id + vnt[i] - '0', q = 1;
                        else if (vnt[i] == '/')
                            q = 2;
                        else q = 0;
                        break;
                    case 2:
                        if (vnt[i] >= '0' && vnt[i] <= '9')
                            t_id = 10 * t_id + vnt[i] - '0', q = 3;
                        else if (vnt[i] == '/')
                            q = 4;
                        else q = 0, success = false;
                        break;
                    case 3:
                        if (vnt[i] >= '0' && vnt[i] <= '9')
                            t_id = 10 * t_id + vnt[i] - '0', q = 3;
                        else if (vnt[i] == '/')
                            q = 4;
                        else q = 0;
                        break;
                    case 4:
                        if (vnt[i] >= '0' && vnt[i] <= '9')
                            n_id = 10 * n_id + vnt[i] - '0', q = 5;
                        else q = 0, success = false;
                        break;
                    case 5:
                        if (vnt[i] >= '0' && vnt[i] <= '9')
                            n_id = 10 * n_id + vnt[i] - '0', q = 5;
                        else q = 0;
                        break;
                    }
                }

                if (v_id)
                    vert.position = positions[v_id - 1];
                else
                    success = false;
                //std::cerr << "ERROR::RESOURCE_MANAGER .obj file syntax wrong - vertex position wasn't declared" << std::endl;
                if (t_id)
                    vert.texCoord = tex_coords[t_id - 1];
                if (n_id)
                    vert.normal = normals[n_id - 1];

                vertices.push_back(vert);
            }
        }
        fin.ignore(128, '\n');
    }

    Mesh* m_mesh = new Mesh(vertices);
    Model* m_model = new Model;
    m_model->addMesh(m_mesh);

    return m_model;
}
