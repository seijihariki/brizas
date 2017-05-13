#define PI 3.14159265359

#include <vector>
#include <fstream>

#include <stdio.h>
#include <cmath>

#include "opengl.hpp"
#include "shaders.hpp"
#include "graphics/camera.hpp"
#include "drawable3d.hpp"

float min(float a, float b)
{
    return a > b?b:a;
}

float max(float a, float b)
{
    return a < b?b:a;
}

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

    // Load model
    Model ball_model("assets/ball.obj");
    Model terrain_model("assets/terrain.obj");

    // Objects
    Drawable_3D *obj = new Drawable_3D(&ball_model);
    objects.push_back(obj);

    obj = new Drawable_3D(&ball_model);
    objects.push_back(obj);
    obj->setTranslation(glm::translate(glm::mat4(1), glm::vec3(5, 0, 0)));

    obj = new Drawable_3D(&terrain_model);
    objects.push_back(obj);

    // Lights
    lights.push_back(glm::vec3(0, 5, 5));
    colors.push_back(glm::vec3(0, .6, .6));

    lights.push_back(glm::vec3(0, 5, 5));
    colors.push_back(glm::vec3(.6, 0, 0));

    lights.push_back(glm::vec3(0, 5, 5));
    colors.push_back(glm::vec3(0, .7, 0));

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
        float rot_speed = 2;

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

        looking_angles.y = min(looking_angles.y, PI/2 - .1);
        looking_angles.y = max(looking_angles.y, -PI/2 + .1);

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        looking_at += camera_pos;

        camera.setView(camera_pos, looking_at);

        lights[0] =
            glm::vec3(0, 3, 5)*(float)sin(time.getElapsedTime().asSeconds()) +
            glm::vec3(5, 0, 0)*(float)cos(time.getElapsedTime().asSeconds()) +
            glm::vec3(0, 5, 0);

        lights[2] = camera_pos;

        glUniform3f(glGetUniformLocation(shader_ID, "camera_pos"), camera_pos.x, camera_pos.y, camera_pos.z);
        glUniform3fv(glGetUniformLocation(shader_ID, "lights"), lights.size(), (GLfloat*)&lights[0]);
        glUniform3fv(glGetUniformLocation(shader_ID, "colors"), lights.size(), (GLfloat*)&colors[0]);

        for (Drawable_3D *obj : objects)
            obj->draw(camera, shader_ID);

        window.display();
    }
}
