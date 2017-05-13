#include "opengl.hpp"
#include "graphics/camera.hpp"
#include "graphics/model.hpp"

#ifndef __DRAWABLE3D_HPP__
#define __DRAWABLE3D_HPP__

// Class for 3D models
class Drawable_3D
{
public:
    Drawable_3D(Model *model = nullptr);

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

    Model *model_obj;

    glm::mat4 scale;
    glm::mat4 rotation;
    glm::mat4 translation;
    glm::mat4 model;
};

#endif
