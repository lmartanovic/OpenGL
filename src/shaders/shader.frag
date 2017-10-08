#version 330 core

in vec2 uv;

uniform sampler2D color_texture1;
uniform sampler2D color_texture2;

out vec4 FragColor;

void main()
{
    FragColor = mix(texture(color_texture1, uv), texture(color_texture2,uv), 0.2);
}

