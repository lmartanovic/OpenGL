#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>

#include <SFML/OpenGL.hpp>

enum class ShaderType : char
{
    VERTEX,
    FRAGMENT,
    GEOMETRY,
    COMPUTE,
    TESS_CONTROL,
    TESS_EVAL
};

class Shader
{
public:
    Shader() = delete;
    Shader(ShaderType _type, const std::string& _src);
    ~Shader();

    std::string get_source() const noexcept {return source;}

    ShaderType get_type() const noexcept {return type;}
    GLuint get_gl_object() const noexcept {return gl_object;}

private:
    ShaderType type;
    GLuint gl_object {0};
    std::string source;
};

GLenum map_shader_type(ShaderType type);
std::string print_shader_type(ShaderType type);

#endif
