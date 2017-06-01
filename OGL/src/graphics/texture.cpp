#include "graphics/texture.hpp"

Texture::Texture(std::vector<unsigned char> image,
            GLsizei width,
            GLsizei height,
            GLuint format,
            GLuint n_type)
    :
        loaded(false),
        bound(false),
        image(image),
        width(width),
        height(height),
        format(format),
        n_type(n_type)
{
}

Texture::~Texture()
{
    unloadFromGPU();
}

void Texture::loadToGPU()
{
    if (loaded)
        return;

    printf("Loading Texture...\n");
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D,
            0,
            GL_RGBA,
            width,
            height,
            0,
            format,
            n_type,
            &image[0]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    loaded = true;
    printf("Loaded texture!\n");
}

void Texture::unloadFromGPU()
{
    if (!loaded)
        return;

    glDeleteTextures(1, &textureID);

    loaded = false;
}

GLenum Texture::activate(GLuint texture_index)
{
    glActiveTexture(GL_TEXTURE0 + texture_index);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

GLuint Texture::getTextureID()
{
    return loaded ? textureID : 0;
}
