#include <fstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>

#include "shader.h"

/*
 * Utils
 */
std::string load_shader_file(const std::string& filename)
{
    std::string retval;
    std::ifstream ifs(filename);
    std::string line;
    while(std::getline(ifs, line))
    {
        retval += line;
        retval += "\n";
    }
    return retval;
}

/*
 * Shader
 */
Shader::Shader(ShaderType _type, const std::string& _src)
{
    //TODO error handling
    source = load_shader_file(_src);
    const char* s_ptr = source.c_str();
    gl_object = glCreateShader(map_shader_type(_type));
    glShaderSource(gl_object, 1, &s_ptr, nullptr);
    glCompileShader(gl_object);

    GLint isCompiled = 0;
    glGetShaderiv(gl_object, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(gl_object, GL_INFO_LOG_LENGTH, &maxLength);
    
        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(gl_object, maxLength, &maxLength, &errorLog[0]);
        
        // Provide the infolog in whatever manor you deem best.
        for(auto c : errorLog)
        {
            std::cout << c;
        }
        // Exit with failure.
        glDeleteShader(gl_object); // Don't leak the shader.
        return;
    }
}

Shader::~Shader()
{
    glDeleteShader(gl_object);
}

GLenum map_shader_type(ShaderType type)
{
    GLenum ret {0};
    switch(type)
    {
        case ShaderType::VERTEX:
            ret = GL_VERTEX_SHADER;
            break;
        case ShaderType::FRAGMENT:
            ret = GL_FRAGMENT_SHADER;
            break;
        case ShaderType::GEOMETRY:
            ret = GL_GEOMETRY_SHADER;
            break;
        case ShaderType::COMPUTE:
            ret = GL_COMPUTE_SHADER;
            break;
        case ShaderType::TESS_CONTROL:
            ret = GL_TESS_CONTROL_SHADER;
            break;
        case ShaderType::TESS_EVAL:
            ret = GL_TESS_EVALUATION_SHADER;
            break;
    }
    return ret;
}

std::string print_shader_type(ShaderType type)
{
    switch(type)
    {
        case ShaderType::VERTEX:
            return "Vertex";
        case ShaderType::FRAGMENT:
            return "Fragment";
        case ShaderType::GEOMETRY:
            return "Geometry";
        case ShaderType::COMPUTE:
            return "Compute";
        case ShaderType::TESS_CONTROL:
            return "Tesselation control";
        case ShaderType::TESS_EVAL:
            return "Tesselation evaluation";
    }

    return "Unknown";
}

