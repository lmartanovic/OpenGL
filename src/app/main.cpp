#include <iostream>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "utils.h"
#include "vertex.h"

//std::vector<std::pair<ShaderType, const std::string&>> shaders;

int main()
{
    constexpr float screen_width {800.0};
    constexpr float screen_height {600.0};
    // create the window
    sf::Window window(sf::VideoMode(screen_width, screen_height), "OpenGL", sf::Style::Default, sf::ContextSettings(32, 32, 0, 3, 3));
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

    glEnable(GL_DEPTH_TEST);

    fw::ShaderProgram shader({{fw::ShaderType::VERTEX, "shader.vert"},{fw::ShaderType::FRAGMENT, "shader.frag"}});
    //TODO this should be elsewhere
    shader.use();
    shader.set_uniform("color_texture", 0);

    fw::Texture2D color_texture("container.jpg");

    fw::Mesh cube(fw::load_vertices_from_file("points.data"), 
                  fw::load_indices_from_file("indices.data"));
    cube.enable_attribs(shader);
    cube.add_color_texture(color_texture);

    glm::vec3 cube_positions[] = {
      glm::vec3( 0.0f,  0.0f,  0.0f), 
      glm::vec3( 2.0f,  5.0f, -15.0f), 
      glm::vec3(-1.5f, -2.2f, -2.5f),  
      glm::vec3(-3.8f, -2.0f, -12.3f),  
      glm::vec3( 2.4f, -0.4f, -3.5f),  
      glm::vec3(-1.7f,  3.0f, -7.5f),  
      glm::vec3( 1.3f, -2.0f, -2.5f),  
      glm::vec3( 1.5f,  2.0f, -2.5f), 
      glm::vec3( 1.5f,  0.2f, -1.5f), 
      glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    //for animation
    sf::Clock clock;

    //camera
    //view
    glm::mat4 view;
    view = glm::translate(view, glm::vec3(0.0, 0.0, -3.0));

    shader.set_uniform("view", view);
    //projection
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f),  //vertical fov
                                  screen_width/screen_height, //aspect ratio
                                  0.1f,  //near clipping plane
                                  100.0f); //far clipping plane

    shader.set_uniform("projection", projection);

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

        //model
        for(unsigned int i = 0; i < 10; ++i)
        {
            glm::mat4 model;
            model = glm::translate(model, cube_positions[i]);
            float angle = 20*i;
            //if(i > 4)
            //{
                angle += (clock.getElapsedTime().asSeconds()*30.0f);
                if(i%2)
                {
                    angle *= -1;
                }
            //}
            model = glm::rotate(model, glm::radians(angle) + glm::radians(angle), glm::vec3(1.0, 0.3, 0.5));
            shader.set_uniform("model", model);

            cube.draw();
        }


        // draw...
        //quad.draw();

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...

    return 0;
}
