#include "drawable3d.hpp"

Drawable_3D::Drawable_3D(Model *model)
    : model_obj(model)
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

    vertexBuffer   = model_obj->getVertexBuffer();
    texturecBuffer = model_obj->getTextureBuffer();
    normalBuffer   = model_obj->getNormalBuffer();

    glm::mat4 mvp = camera.getMVP(model);
    
    GLuint MVP = glGetUniformLocation(shader, "MVP");
    glUniformMatrix4fv(MVP, 1, GL_FALSE, &mvp[0][0]);

    GLuint MT = glGetUniformLocation(shader, "MT");
    glUniformMatrix4fv(MT, 1, GL_FALSE, &model[0][0]);

    glEnableVertexAttribArray(vertex);
    glEnableVertexAttribArray(texturec);
    glEnableVertexAttribArray(normal);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, texturecBuffer);
    glVertexAttribPointer(texturec, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, model_obj->vertexCnt());

    glDisableVertexAttribArray(vertex);
    glDisableVertexAttribArray(texturec);
    glDisableVertexAttribArray(normal);
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
    glm::translate(glm::mat4(1.0f), translation);
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
