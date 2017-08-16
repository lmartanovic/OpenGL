#version 330 core

layout (location = 0)

in vec3 position;
in vec3 inColor;

out vec3 Color;

void main()
{
    Color = inColor;
    gl_Position = vec4(position, 1.0);
}

