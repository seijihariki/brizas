#include "drawable3d.hpp"
#include <string.h>

Drawable_3D::Drawable_3D()
{
    updateModelMatrix();
}

GLuint Drawable_3D::genGLBuffers()
{
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    glGenVertexArrays(1, &TextureCArrayID);
    glBindVertexArray(TextureCArrayID);

    glGenBuffers(1, &texturecBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, texturecBuffer);
    glBufferData(GL_ARRAY_BUFFER, texture_c.size() * sizeof(glm::vec2), &texture_c[0], GL_STATIC_DRAW);

    glGenVertexArrays(1, &NormalArrayID);
    glBindVertexArray(NormalArrayID);

    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

    return vertexBuffer;
}

void Drawable_3D::loadFromFile(std::string filename)
{
    std::vector<glm::vec3> tmpvertices;
    std::vector<glm::vec2> tmptexture_c;
    std::vector<glm::vec3> tmpnormals;

    printf("Loading model %s...\n", filename.c_str());

    FILE *file = fopen(filename.c_str(), "r");

    if (!file)
    {
        printf("Could not open %s\n", filename.c_str());
        return;
    }

    while (true)
    {
        char lineHeader[128];

        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;

        if (!strcmp(lineHeader, "v"))
        {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            tmpvertices.push_back(vertex);
        }
        else if (!strcmp(lineHeader, "vt"))
        {
            glm::vec2 vertex;
            fscanf(file, "%f %f\n", &vertex.x, &vertex.y);
            tmptexture_c.push_back(vertex);
        }
        else if (!strcmp(lineHeader, "vn"))
        {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            tmpnormals.push_back(vertex);
        }
        else if (!strcmp(lineHeader, "f"))
        {
            int v1, t1, n1, v2, t2, n2, v3, t3, n3;
            fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                    &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);
            this->vertices.push_back(tmpvertices[v1 - 1]);
            this->vertices.push_back(tmpvertices[v2 - 1]);
            this->vertices.push_back(tmpvertices[v3 - 1]);

            this->texture_c.push_back(tmptexture_c[t1 - 1]);
            this->texture_c.push_back(tmptexture_c[t2 - 1]);
            this->texture_c.push_back(tmptexture_c[t3 - 1]);

            this->normals.push_back(tmpnormals[n1 - 1]);
            this->normals.push_back(tmpnormals[n2 - 1]);
            this->normals.push_back(tmpnormals[n3 - 1]);
        } else {
            char c = lineHeader[0];
            while (c != EOF && c != '\n')
                fscanf(file, "%c", &c);
        }
    }
    printf("Model %s was loaded!\n", filename.c_str());
}

void Drawable_3D::draw(Camera &camera, GLuint shader, GLuint vertex, GLuint texturec, GLuint normal)
{
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

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

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
