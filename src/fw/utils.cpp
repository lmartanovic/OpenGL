#include <fstream>
#include <iostream>
#include <sstream>

#include "utils.h"
#include "vertex.h"

namespace fw
{
std::vector<Vertex> load_vertices_from_file(const std::string& filename)
{
    std::vector<Vertex> ret;

    std::ifstream ifs(filename);
    if(!ifs.is_open())
    {
        //TODO better error handling - custom exception?
        std::cerr << "Unable to open the input file " << filename << '\n';
        return ret;
    }

    std::string line;
    while(std::getline(ifs, line))
    {
        //TODO make prettier
        std::stringstream str(line);
        auto& v = ret.emplace_back();
        str >> v.x >> v.y >> v.z >> v.r >> v.g >> v.b;

    }

    return ret;
}

std::vector<unsigned int> load_indices_from_file(const std::string& filename)
{
    std::vector<unsigned int> ret;

    std::ifstream ifs(filename);
    if(!ifs.is_open())
    {
        //TODO better error handling
        std::cerr << "Unable to open the input file " << filename << '\n';
        return ret;
    }

    unsigned int index {0};
    while(ifs >> index)
    {
        ret.emplace_back(index);
    }
    
    return ret;
}
} //namespace fw
