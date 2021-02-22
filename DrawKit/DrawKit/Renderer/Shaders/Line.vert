#version 410 core

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec4 VertexColour;

out VertexData {
    vec4 mColor;
}   VertexOut;

uniform mat4 ModelViewProjection;

void main (void)
{
    gl_Position  = ModelViewProjection * vec4(VertexPosition, 1.0);
    VertexOut.mColor = VertexColour;
}
