#include "graphics/model.hpp"
#include <string.h>

Model::Model(std::string filename)
{ 
    VertexArrayID   = 0;
    TextureCArrayID = 0;
    NormalArrayID   = 0;

    vertexBuffer    = 0;
    texturecBuffer  = 0;
    normalBuffer    = 0;
    
    loadFromFile(filename);

    loaded = false;
}

Model::~Model()
{
    if (loaded)
        unloadFromGPU();
}

void Model::loadFromFile(std::string filename)
{
    vertices.clear();
    texture_c.clear();
    normals.clear();

    std::vector<glm::vec3> tmpvertices;
    std::vector<glm::vec2> tmptexture_c;
    std::vector<glm::vec3> tmpnormals;

    printf("Loading model %s...\n", filename.c_str());

    std::ifstream file;
    file.open(filename);

    if (file.fail())
    {
        printf("Could not open %s\n", filename.c_str());
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream line_stream(line);
        std::string header;

        line_stream >> header;

        if (!header.compare("v"))
        {
            glm::vec3 vertex;
            line_stream >> vertex.x >> vertex.y >> vertex.z;
            tmpvertices.push_back(vertex);
        }
        else if (!header.compare("vt"))
        {
            glm::vec2 vertex;
            line_stream >> vertex.x >> vertex.y;
            tmptexture_c.push_back(vertex);
        }
        else if (!header.compare("vn"))
        {
            glm::vec3 vertex;
            line_stream >> vertex.x >> vertex.y >> vertex.z;
            tmpnormals.push_back(vertex);
        }
        else if (!header.compare("f"))
        {
            int v1, t1, n1, v2, t2, n2, v3, t3, n3;
            char sep;
            line_stream >> v1 >> sep >> t1 >> sep >> n1 >>
                v2 >> sep >> t2 >> sep >> n2 >>
                v3 >> sep >> t3 >> sep >> n3;
            this->vertices.push_back(tmpvertices[v1 - 1]);
            this->vertices.push_back(tmpvertices[v2 - 1]);
            this->vertices.push_back(tmpvertices[v3 - 1]);

            this->texture_c.push_back(tmptexture_c[t1 - 1]);
            this->texture_c.push_back(tmptexture_c[t2 - 1]);
            this->texture_c.push_back(tmptexture_c[t3 - 1]);

            this->normals.push_back(tmpnormals[n1 - 1]);
            this->normals.push_back(tmpnormals[n2 - 1]);
            this->normals.push_back(tmpnormals[n3 - 1]);
        }
        else if (!header.compare("o"))
        {
            line_stream >> name;
        }
        else if (!header.compare("#"))
        {
            std::cout << line << '\n';
        }
        else
        {
            std::cout << "Unknown line format: " << line << '\n';
        }
    }

    file.close();
    printf("Model %s was loaded!\n", filename.c_str());
}

void Model::loadToGPU()
{
    if (loaded)
        return;

    printf("Loading model %s to GPU...\n", name.c_str());
    
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

    loaded = true;

    printf("Model %s loaded to GPU!\n", name.c_str());
}

void Model::unloadFromGPU()
{
    glDeleteVertexArrays(1, &VertexArrayID);

    glDeleteBuffers(1, &vertexBuffer);

    glDeleteVertexArrays(1, &TextureCArrayID);

    glDeleteBuffers(1, &texturecBuffer);

    glDeleteVertexArrays(1, &NormalArrayID);

    glDeleteBuffers(1, &normalBuffer);

    loaded = false;
}

GLuint Model::getVertexBuffer()
{
    return vertexBuffer;
}

GLuint Model::getTextureBuffer()
{
    return texturecBuffer;
}

GLuint Model::getNormalBuffer()
{
    return normalBuffer;
}

std::string Model::getName()
{
    return name;
}

bool Model::isLoaded()
{
    return loaded;
}

unsigned int Model::vertexCnt()
{
    return vertices.size();
}
