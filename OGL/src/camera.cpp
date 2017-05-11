#include "camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 lookat,
        float FoV, float AR, glm::vec3 up_vec,
        float near_clip, float far_clip)
{
    setView(position, lookat, up_vec);
    setProjection(FoV, AR, near_clip, far_clip);
}

void Camera::setView(glm::vec3 position, glm::vec3 lookat,
        glm::vec3 up_vec)
{
    setView(glm::lookAt(position, lookat, up_vec));
}

void Camera::setView(glm::mat4 view)
{
    this->view = view;
}

void Camera::setProjection(float FoV, float AR, float near_clip, float far_clip)
{
    setProjection(glm::perspective(FoV, AR, near_clip, far_clip));
}

void Camera::setProjection(glm::mat4 projection)
{
    this->projection = projection;
}

glm::mat4 Camera::getMVP(glm::mat4 model)
{
    return projection * view * model;
}
