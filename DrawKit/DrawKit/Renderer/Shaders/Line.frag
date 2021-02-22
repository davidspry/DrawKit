#version 410 core

in  VertexData {
    vec2 mTexCoord;
    vec4 mColor;
}   VertexIn;

out vec4 FragmentColour;

void main (void)
{
    FragmentColour = VertexIn.mColor;
}
