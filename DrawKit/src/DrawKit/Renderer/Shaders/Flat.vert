#version 410 core

layout (location = 0) in vec4 vertex_colour;
layout (location = 1) in vec3 vertex_xyz;

out vec4 colour;

uniform mat4 view_projection;
uniform mat4 transform;

void main()
{
    gl_Position = view_projection * transform * vec4(vertex_xyz, 1.0);
    colour      = vertex_colour;
}
