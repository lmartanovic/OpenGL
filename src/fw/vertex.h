#ifndef _VERTEX_H_
#define _VERTEX_H_

namespace fw
{

struct Vertex
{
    Vertex() = default;
    Vertex(float _x, float _y, float _z, float _r, float _g, float _b)
    : x(_x), y(_y), z(_z), r(_r), g(_g), b(_b)
    {}

    float x {};
    float y {};
    float z {};
    float r {};
    float g {};
    float b {};
};

}//namespace fw

#endif
