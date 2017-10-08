#ifndef _VERTEX_H_
#define _VERTEX_H_

namespace fw
{

struct Vertex
{
    Vertex() = default;
    Vertex(float _x, float _y, float _z, float _u, float _v)
    : x(_x), y(_y), z(_z), u(_u), v(_v)
    {}

    float x {};
    float y {};
    float z {};
    float u {};
    float v {};
};

}//namespace fw

#endif
