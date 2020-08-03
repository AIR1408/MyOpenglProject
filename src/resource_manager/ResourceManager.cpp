#include "ResourceManager.h"

std::string ResourceManager::getSource(char* FilePath)
{
    std::ifstream fin(FilePath);
    if (!fin.is_open())
    {
        std::cerr << "Can't open file " << FilePath << std::endl;
        exit(-1);
    }
    std::ostringstream buf;
    buf << fin.rdbuf();
    fin.close();
    return buf.str();
}
