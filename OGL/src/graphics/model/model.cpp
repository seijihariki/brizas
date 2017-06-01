#include "graphics/model/model.hpp"
#include <string.h>

Model::Model(std::string filename)
{ 
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

    vertices_vd = new VertexData<glm::vec3>(vertices, 3);
    texture_vd = new VertexData<glm::vec2>(texture_c, 2);
    normals_vd = new VertexData<glm::vec3>(normals, 3);

    printf("Model %s was loaded with %lu triangles!\n", filename.c_str(), vertices.size()/3);
}

void Model::loadToGPU()
{
    if (loaded)
        return;

    printf("Loading model %s to GPU...\n", name.c_str());
   
    vertices_vd->loadToGPU();
    texture_vd->loadToGPU();
    normals_vd->loadToGPU();

    loaded = true;

    printf("Model %s loaded to GPU!\n", name.c_str());
}

void Model::unloadFromGPU()
{
    if (!loaded)
        return;

    vertices_vd->unloadFromGPU();
    texture_vd->unloadFromGPU();
    normals_vd->unloadFromGPU();
    
    loaded = false;
}

bool Model::isLoaded()
{
    return loaded;
}

void Model::activate(GLuint vertex, GLuint texture, GLuint normal)
{
    vertices_vd->activate(vertex);
    texture_vd->activate(texture);
    normals_vd->activate(normal);
}

void Model::deactivate()
{
    vertices_vd->deactivate();
    texture_vd->deactivate();
    normals_vd->deactivate();
}

std::string Model::getName()
{
    return name;
}

GLuint Model::vertexCnt()
{
    return vertices.size();
}
