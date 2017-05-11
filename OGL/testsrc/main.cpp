#define PI 3.14159265359

#include <vector>
#include <fstream>

#include <stdio.h>
#include <cmath>

#include "opengl.hpp"
#include "shaders.hpp"
#include "camera.hpp"
#include "drawable3d.hpp"

// Main
int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    settings.depthBits = 24;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Teste", sf::Style::Close, settings);

    GLuint shader_ID =  LoadShaders("assets/shader1.vert", "assets/shader1.frag");
    glUseProgram(shader_ID);

    glEnable(GL_DEPTH_TEST);

    glm::vec3 camera_pos = glm::vec3(2, 2, 3);
    glm::vec2 looking_angles = glm::vec2(0, 0);
    glm::vec3 looking_at = glm::vec3(0, 0, 0);

    Camera camera(camera_pos, looking_at, glm::radians(45.f), 800.f/600.f);

    std::vector<Drawable_3D*> objects;
    std::vector<glm::vec3> lights;
    std::vector<glm::vec3> colors;

    // Objects
    Drawable_3D *obj = new Drawable_3D;
    objects.push_back(obj);
    obj->loadFromFile("assets/untitled.obj");
    obj->genGLBuffers();

    obj = new Drawable_3D;
    objects.push_back(obj);
    obj->loadFromFile("assets/obj2.obj");
    obj->genGLBuffers();
    obj->setTranslation(glm::translate(glm::mat4(1), glm::vec3(5, 0, 0)));

    for (int i = 0; i < 5000; i++)
    {
        obj = new Drawable_3D;
        objects.push_back(obj);
        obj->loadFromFile("assets/obj2.obj");
        obj->genGLBuffers();
        obj->setTranslation(glm::translate(glm::mat4(1), glm::vec3(i + 1 + 10.f, 5*sin(i/1.5), 0.f)));
    }

    // Lights
    lights.push_back(glm::vec3(0, 5, 5));
    colors.push_back(glm::vec3(0, .6, .6));

    lights.push_back(glm::vec3(0, 5, 5));
    colors.push_back(glm::vec3(.6, 0, 0));

    sf::Clock time;
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event evn;
        while (window.pollEvent(evn))
        {
            if (evn.type == sf::Event::Closed)
                window.close();
        }

        float delta_t = clock.restart().asSeconds();

        looking_at.x = cos(looking_angles.y)*cos(looking_angles.x);
        looking_at.z = cos(looking_angles.y)*sin(looking_angles.x);
        looking_at.y = sin(looking_angles.y);

        float speed = 5;
        float rot_speed = 1.4;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            camera_pos += looking_at*speed*delta_t;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            camera_pos -= looking_at*speed*delta_t;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            camera_pos -= glm::vec3(cos(looking_angles.x - PI/2), 0, sin(looking_angles.x - PI/2))*speed*delta_t;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            camera_pos += glm::vec3(cos(looking_angles.x - PI/2), 0, sin(looking_angles.x - PI/2))*speed*delta_t;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            looking_angles.y += rot_speed*delta_t;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            looking_angles.y -= rot_speed*delta_t;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            looking_angles.x -= rot_speed*delta_t;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            looking_angles.x += rot_speed*delta_t;

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        looking_at += camera_pos;

        camera.setView(camera_pos, looking_at);

        lights[0] = glm::vec3(sin(time.getElapsedTime().asSeconds()), cos(time.getElapsedTime().asSeconds()), 0) * 2.5f;
        lights[1] = glm::vec3(cos(1.333*time.getElapsedTime().asSeconds()), 0, sin(1.333*time.getElapsedTime().asSeconds())) * 2.5f;

        objects[1]->setTranslation(glm::translate(glm::mat4(1), glm::vec3(5 + sin(time.getElapsedTime().asSeconds()), 0, 0)));

        glUniform3fv(glGetUniformLocation(shader_ID, "lights"), lights.size(), (GLfloat*)&lights[0]);
        glUniform3fv(glGetUniformLocation(shader_ID, "colors"), lights.size(), (GLfloat*)&colors[0]);

        for (Drawable_3D *obj : objects)
            obj->draw(camera, shader_ID);

        window.display();
    }
}
