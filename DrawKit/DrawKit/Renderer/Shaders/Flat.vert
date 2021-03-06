#version 410 core

layout (location = 0) in vec3 VertexPosition;

out vec4 VertexColour;

uniform mat4 ModelViewProjection;
uniform vec4 Colour;

void main (void)
{
    gl_Position  = ModelViewProjection * vec4(VertexPosition, 1.0);
    VertexColour = Colour;
}
