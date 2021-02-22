#version 410 core

in  vec4 VertexColour;
out vec4 FragmentColour;

void main (void)
{
    FragmentColour = VertexColour;
}
