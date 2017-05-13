#include "opengl.hpp"

#ifndef __GRAPHICS_CAMERA_HPP__
#define __GRAPHICS_CAMERA_HPP__

// Class Camera
class Camera
{
public:
    Camera(glm::vec3 position, glm::vec3 lookat,
            float FoV, float AR, glm::vec3 up_vec = glm::vec3(0, 1, 0),
            float near_clip = .1f, float far_clip = 100.f);

    void setView(glm::vec3 position, glm::vec3 lookat,
            glm::vec3 up_vec = glm::vec3(0, 1, 0));
    void setView(glm::mat4 view);

    void setProjection(float FoV, float AR, float near_clip, float far_clip);
    void setProjection(glm::mat4 projection);

    glm::mat4 getMVP(glm::mat4 model);

private:
    glm::mat4 view;
    glm::mat4 projection;
};

#endif
