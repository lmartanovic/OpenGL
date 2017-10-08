#ifndef TEXTURE_H
#define TEXTURE_H

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace fw
{

class Texture2D
{
public:
    Texture2D() = default;
    explicit Texture2D(const std::string& filename)
    {
        glGenTextures(1, &gl_object);
        glBindTexture(GL_TEXTURE_2D, gl_object);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //TODO create some config-based bitmap or whatever to decide stuff like mipmaps
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width {0};
        int height {0};
        int n_channels {0};
        stbi_set_flip_vertically_on_load(true);
        float* data = stbi_loadf(filename.c_str(), &width, &height, &n_channels, 0);

        if(data)
        {
            //TODO check n_channels and use RGBA if necessary
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            //TODO better error handling
            std::cerr << "Unable to load texture data from file " << filename << '\n';
        }

        stbi_image_free(data);
    }

    unsigned int get_gl_object() const noexcept
    {
        return gl_object;
    }

private:
    unsigned int gl_object {0};
};

} //namespace fw

#endif //TEXTURE_H
