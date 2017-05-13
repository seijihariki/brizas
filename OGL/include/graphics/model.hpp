#include "opengl.hpp"

#ifndef __GRAPHICS_MODEL_HPP__
#define __GRAPHICS_MODEL_HPP__

class Model
{
public:
    Model(std::string filename);

    ~Model();

    void loadFromFile(std::string filename);

    void loadToGPU();
    void unloadFromGPU();

    GLuint getVertexBuffer();
    GLuint getTextureBuffer();
    GLuint getNormalBuffer();

    std::string getName();

    bool isLoaded();

    unsigned int vertexCnt();

private:
    bool loaded;
    std::string name;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texture_c;
    std::vector<glm::vec3> normals;

    GLuint VertexArrayID, vertexBuffer;
    GLuint TextureCArrayID, texturecBuffer;
    GLuint NormalArrayID, normalBuffer;
};

#endif
