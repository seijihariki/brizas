#include "drawable3d.hpp"

Drawable_3D::Drawable_3D(Model *model, Texture *texture)
    : model_obj(model), texture(texture)
{
    updateModelMatrix();
}

void Drawable_3D::draw(Camera &camera, GLuint shader, GLuint vertex, GLuint texturec, GLuint normal)
{
    GLuint vertexBuffer;
    GLuint texturecBuffer;
    GLuint normalBuffer;

    if (!model_obj->isLoaded())
        model_obj->loadToGPU();

    if (texture)
        texture->activate(0);

    glm::mat4 mvp = camera.getMVP(model);

    GLuint MVP = glGetUniformLocation(shader, "MVP");
    glUniformMatrix4fv(MVP, 1, GL_FALSE, &mvp[0][0]);

    GLuint MT = glGetUniformLocation(shader, "MT");
    glUniformMatrix4fv(MT, 1, GL_FALSE, &model[0][0]);

    GLuint text_sampler = glGetUniformLocation(shader, "text");
    glUniform1i(text_sampler, 0);

    GLuint bump_sampler = glGetUniformLocation(shader, "bump");
    glUniform1i(bump_sampler, 1);
    
    model_obj->activate(vertex, texturec, normal);

    glDrawArrays(GL_TRIANGLES, 0, model_obj->vertexCnt());

    model_obj->deactivate();
}

void Drawable_3D::setScale(glm::vec3 scale)
{
     setScale(glm::scale(glm::mat4(1.0f), scale));
}

void Drawable_3D::setScale(glm::mat4 scale)
{
    this->scale = scale;
    updateModelMatrix();
}

void Drawable_3D::setRotation(glm::quat rotation)
{
    setRotation(glm::mat4_cast(rotation));
}

void Drawable_3D::setRotation(glm::mat4 rotation)
{
    this->rotation = rotation;
    updateModelMatrix();
}

void Drawable_3D::setTranslation(glm::vec3 translation)
{
    setTranslation(glm::translate(glm::mat4(1.0f), translation));
}

void Drawable_3D::setTranslation(glm::mat4 translation)
{
    this->translation = translation;
    updateModelMatrix();
}

void Drawable_3D::updateModelMatrix()
{
    model = translation * rotation * scale;
}

Drawable_3D::~Drawable_3D()
{
}
