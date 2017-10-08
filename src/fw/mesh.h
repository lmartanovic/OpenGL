#ifndef MESH_H
#define MESH_H

#include <SFML/OpenGL.hpp>

#include "shader.h"
#include "texture.h"
#include "vertex.h"

namespace fw
{

class Mesh
{
public:
    Mesh() = delete;
    Mesh(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices) : indices_count(_indices.size())
    {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, _vertices.size()*sizeof(Vertex), _vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size()*sizeof(unsigned int), _indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(0); //Unbind first, as it stores other unbind calls

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void enable_attribs(const ShaderProgram& shader) const
    {
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        auto pos_attrib = glGetAttribLocation(shader.get_gl_object(), "in_position");
        glEnableVertexAttribArray(pos_attrib);
        glVertexAttribPointer(pos_attrib, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

        auto uv_attrib = glGetAttribLocation(shader.get_gl_object(), "in_uv");
        glEnableVertexAttribArray(uv_attrib);
        glVertexAttribPointer(uv_attrib, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(3*sizeof(GL_FLOAT)));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void add_color_texture(const Texture2D& c_tex)
    {
        color_texture = c_tex;
    }

    void draw() const
    {
        //color
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, color_texture.get_gl_object());

        glBindVertexArray(vao);

        glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

private:
    unsigned int vao {0};
    unsigned int vbo {0};
    unsigned int ebo {0};
    size_t indices_count {0};

    Texture2D color_texture;
};

} //namespace fw

#endif //MESH_H
