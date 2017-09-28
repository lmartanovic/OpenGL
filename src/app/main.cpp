#include <iostream>

#include <GL/glew.h>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "mesh.h"
#include "shader.h"
#include "utils.h"
#include "vertex.h"

//std::vector<std::pair<ShaderType, const std::string&>> shaders;

int main()
{
    // create the window
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // activate the window
    window.setActive(true);

    // load resources, initialize the OpenGL states, ...

    glewExperimental = true;
    if(glewInit() != GLEW_OK)
    {
        std::cerr << "GLEW init failed" << std::endl;
        return -1;
    }

    fw::ShaderProgram shader({{fw::ShaderType::VERTEX, "shader.vert"},{fw::ShaderType::FRAGMENT, "shader.frag"}});

    shader.use();

    //std::vector<fw::Vertex> points = {
    //    { 0.45f,  0.45f, 0.0f, 1.0f, 0.0f, 0.0f},
    //    {-0.45f,  0.45f, 0.0f, 0.0f, 1.0f, 0.0f},
    //    { 0.45f, -0.45f, 0.0f, 0.0f, 0.0f, 1.0f},
    //    {-0.45f, -0.45f, 0.0f, 1.0f, 0.0f, 0.0f}
    //};
    std::vector<fw::Vertex> points = fw::load_vertices_from_file("points.data");

    fw::Mesh quad(points);
    quad.enable_attribs(shader);

    // run the main loop
    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
            //TODO implement a keyboard controller
            else if (event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Escape:
                        running = false;
                        break;
                    default:
                        break;
                }
            }
        }

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...
        quad.draw();

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...

    return 0;
}
