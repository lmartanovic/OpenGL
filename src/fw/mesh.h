#ifndef MESH_H
#define MESH_H

#include <SFML/OpenGL.hpp>

#include "shader.h"
#include "vertex.h"

namespace fw
{

class Mesh
{
public:
    Mesh() = delete;
    Mesh(const std::vector<Vertex>& _vertices) : vertices(_vertices)
    {
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        glGenVertexArrays(1, &vao);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void enable_attribs(const ShaderProgram& shader) const
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindVertexArray(vao);

        GLint pos_attrib = glGetAttribLocation(shader.get_gl_object(), "position");
        glEnableVertexAttribArray(pos_attrib);
        glVertexAttribPointer(pos_attrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

        //TODO replace with UV
        GLint col_attrib = glGetAttribLocation(shader.get_gl_object(), "inColor");
        glEnableVertexAttribArray(col_attrib);
        glVertexAttribPointer(col_attrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(3*sizeof(GL_FLOAT)));

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void draw() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size());

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

private:
    unsigned int vbo {0};
    unsigned int vao {0};
    std::vector<Vertex> vertices;
};

} //namespace fw

#endif
