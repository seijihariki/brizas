#include "graphics/vertexdata.hpp"
 
template<typename type>
VertexData<type>::VertexData (std::vector<type> data, GLint n, GLenum data_type, GLboolean normalized)
    :
        loaded(false),
        active(false),
        data(data),
        n(n),
        data_type(data_type),
        normalized(normalized)
{
}

template<typename type>
GLenum VertexData<type>::loadToGPU(GLenum draw_type)
{
    if (loaded)
        return GL_NO_ERROR;

    glGenVertexArrays(1, &VAO_ID);
    glBindVertexArray(VAO_ID);

    glGenBuffers(1, &VBO_ID);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(type), &data[0], draw_type);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
        loaded = true;

    return error;
}

template<typename type>
void VertexData<type>::unloadFromGPU()
{
    if (!loaded)
        return;

    glDeleteVertexArrays(1, &VAO_ID);
    glDeleteBuffers(1, &VBO_ID);

    loaded = false;
}

template<typename type>
GLenum VertexData<type>::activate(GLuint location)
{
    if (active)
        return GL_NO_ERROR;

    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
    glVertexAttribPointer(location, n, data_type, normalized, 0, 0);

    active = true;
    
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        this->location = location;
        loaded = true;
    }

    return error;
}

template<typename type>
void VertexData<type>::deactivate()
{
    if (!active)
        return;

    glDisableVertexAttribArray(location);

    location = 0;
    active = false;
}

template class VertexData<glm::vec3>;
template class VertexData<glm::vec2>;
