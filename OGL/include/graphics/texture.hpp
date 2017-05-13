#include "opengl.hpp"

#ifndef __GRAPHICS_TEXTURE_HPP__
#define __GRAPHICS_TEXTURE_HPP__

class Texture
{
public:
    Texture(std::vector<unsigned char> image,
            GLsizei width,
            GLsizei height,
            GLuint format = GL_RGBA,
            GLuint n_type = GL_UNSIGNED_BYTE);

    ~Texture();

    void loadToGPU();
    void unloadFromGPU();

    GLuint getTextureID();

private:
    bool loaded;

    std::vector<unsigned char> image;
    GLsizei width, height;
    GLuint format, n_type;

    GLuint textureID;
};

#endif
