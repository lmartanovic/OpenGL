#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>

#include <glm/glm.hpp>

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
    unsigned int get_gl_object() const noexcept {return gl_object;}

private:
    ShaderType type;
    unsigned int gl_object {0};
    std::string source;
};

using ShaderDef = std::pair<ShaderType, std::string>;

class ShaderProgram
{
public:
    ShaderProgram() = delete;
    ShaderProgram(const std::vector<ShaderDef>& shaders);
    ~ShaderProgram();

    void set_uniform(const std::string& name, int value);
    void set_uniform(const std::string& name, const glm::mat4& matrix);
    void use() const noexcept;
    unsigned int get_gl_object() const noexcept {return gl_object;}
private:
    unsigned int gl_object {0};
};

} //namespace fw
#endif
