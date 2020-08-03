#include "extra.h"

void ext::err(std::string msg)
{
    std::cerr << msg << std::endl;
    exit(-1);
}