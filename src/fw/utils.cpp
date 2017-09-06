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
        std::stringstream str(line);
        float x, y, z, r, g, b; //TODO ugly as sin - change
        str >> x >> y >> z >> r >> g >> b;

        ret.emplace_back(x, y, z, r, g, b);
    }

    return ret;
}
} //namespace fw
