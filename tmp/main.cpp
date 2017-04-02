#define GL_GLEXT_PROTOTYPES
#define GLM_FORCE_RADIANS

#include <GL/gl.h>
#include <GL/glext.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <vector>
#include <string>
#include <string.h>
#include <fstream>

#include <stdio.h>

// Shaders
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open()){
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }else{
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
        getchar();
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}




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
        }
    }
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

// Main
int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    settings.depthBits = 24;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Teste", sf::Style::Close, settings);

    GLuint shader_ID =  LoadShaders("shader1.vert", "shader1.frag");
    glUseProgram(shader_ID);

    glEnable(GL_DEPTH_TEST);

    glm::vec3 camera_pos = glm::vec3(2, 2, 3);
    glm::vec3 looking_at = glm::vec3(0, 0, 0);

    Camera camera(camera_pos, looking_at, glm::radians(45.f), 800.f/600.f);

    Drawable_3D object;
    object.loadFromFile("untitled.obj");
    object.genGLBuffers();

    Drawable_3D cubo2;
    cubo2.loadFromFile("untitled.obj");
    cubo2.genGLBuffers();
    cubo2.setTranslation(glm::translate(glm::mat4(1), glm::vec3(5, 0, 0)));

    while (window.isOpen())
    {
        sf::Event evn;
        while (window.pollEvent(evn))
        {
            if (evn.type == sf::Event::Closed)
                window.close();
        }

        float speed = .02;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            camera_pos.y += speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            camera_pos.y -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            camera_pos.x -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            camera_pos.x += speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            camera_pos.z -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            camera_pos.z += speed;

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        camera.setView(camera_pos, looking_at);

        object.draw(camera, shader_ID);
        cubo2.draw(camera, shader_ID);

        window.display();
    }
}
