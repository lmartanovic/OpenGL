#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>

#include <SFML/OpenGL.hpp>

namespace fw
{

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

using ShaderDef = std::pair<ShaderType, std::string>;

class ShaderProgram
{
public:
    ShaderProgram() = delete;
    ShaderProgram(const std::vector<ShaderDef>& shaders);
    ~ShaderProgram();

    void use() const noexcept;
    GLuint get_gl_object() const noexcept {return gl_object;}
private:
    GLuint gl_object {0};
};

} //namespace fw
#endif
