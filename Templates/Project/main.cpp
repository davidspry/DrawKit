#include "Sketch.hpp"

int main(int argc, char *argv[])
{
    Sketch sketch;
    DrawKit::Window::Attributes attr;
    
    attr.title  = "DrawKit";
    attr.width  = 900;
    attr.height = 900;

    DrawKit::setWindowPosition(60, 60);
    DrawKit::launch(&sketch, attr, DrawKit::RendererType::OPENGL);
    
    return 0;
}
