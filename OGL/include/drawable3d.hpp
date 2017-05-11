#include "opengl.hpp"
#include "camera.hpp"

#ifndef __DRAWABLE3D_HPP__
#define __DRAWABLE3D_HPP__

// Class for 3D models
class Drawable_3D
{
public:
    Drawable_3D();

    GLuint genGLBuffers();

    void loadFromFile(std::string filename);

    void draw(Camera &camera, GLuint shader, GLuint vertex = 0, GLuint texturec = 1, GLuint normal = 2);

    void setScale(glm::vec3 scale);
    void setScale(glm::mat4 scale);

    void setRotation(glm::quat rotation);
    void setRotation(glm::mat4 rotation);

    void setTranslation(glm::vec3 translation);
    void setTranslation(glm::mat4 translation);

    ~Drawable_3D();

protected:

    void updateModelMatrix();

    glm::mat4 scale;
    glm::mat4 rotation;
    glm::mat4 translation;
    glm::mat4 model;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texture_c;
    std::vector<glm::vec3> normals;

    GLuint VertexArrayID, vertexBuffer;
    GLuint TextureCArrayID, texturecBuffer;
    GLuint NormalArrayID, normalBuffer;
};

#endif
