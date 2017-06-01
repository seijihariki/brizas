#include "opengl.hpp"
#include "graphics/vertexdata.hpp"

#ifndef __GRAPHICS_MODEL_MODEL_HPP__
#define __GRAPHICS_MODEL_MODEL_HPP__

class Model
{
public:
    Model(std::string filename);

    ~Model();

    void loadFromFile(std::string filename);

    void loadToGPU();
    void unloadFromGPU();

    bool isLoaded();

    void activate(GLuint vertex, GLuint texture, GLuint normal);
    void deactivate();

    std::string getName();

    GLuint vertexCnt();

private:
    bool loaded;
    std::string name;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texture_c;
    std::vector<glm::vec3> normals;

    VertexData<glm::vec3> *vertices_vd;
    VertexData<glm::vec2> *texture_vd;
    VertexData<glm::vec3> *normals_vd;
};

#endif
