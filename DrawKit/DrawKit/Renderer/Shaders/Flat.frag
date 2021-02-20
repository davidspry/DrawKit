#version 410 core

in  vec4 colour;
out vec4 fragment_colour;

void main()
{
    fragment_colour = colour;
}
