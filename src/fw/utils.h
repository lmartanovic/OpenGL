#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>
#include <vector>

namespace fw
{
    struct Vertex;

    std::vector<Vertex> load_vertices_from_file(const std::string& filename);
} //namespace fw

#endif
