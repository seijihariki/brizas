#include "opengl.hpp"

#ifndef __VERTEXDATA_HPP__
#define __VERTEXDATA_HPP__

template <typename type>
class VertexData {
public:
    VertexData(std::vector<type> data,
            GLint n,
            GLenum data_type = GL_FLOAT,
            GLboolean normalized = GL_FALSE);

    GLenum loadToGPU(GLenum draw_type = GL_STATIC_DRAW);
    void unloadFromGPU();

    GLenum activate(GLuint location);
    void deactivate();

private:
    bool loaded, active;
    GLuint VAO_ID, VBO_ID, location;
    std::vector<type> data;

    GLint n;
    GLenum data_type;
    GLboolean normalized;
};

#endif
