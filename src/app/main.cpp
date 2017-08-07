#include <iostream>

#include <GL/glew.h>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "shader.h"

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

    GLuint vbo;
    glGenBuffers(1, &vbo);

    float points[] = {
         0.45f,  0.45f, 1.0f, 0.0f, 0.0f,
        -0.45f,  0.45f, 0.0f, 1.0f, 0.0f,
         0.45f, -0.45f, 0.0f, 0.0f, 1.0f,
        -0.45f, -0.45f, 1.0f, 0.0f, 0.0f
    };
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLint posAttrib = glGetAttribLocation(shader.get_gl_object(), "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), 0);

    GLint colAttrib = glGetAttribLocation(shader.get_gl_object(), "inColor");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), (void*)(2*sizeof(GL_FLOAT)));

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
        }

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...

    return 0;
}
