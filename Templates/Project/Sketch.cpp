#include "Sketch.hpp"

void Sketch::prepare()
{
    DrawKit::setFrameRate(60);
    DrawKit::enableSmoothing();
    DrawKit::setBackgroundColour(15);
}

void Sketch::update()
{
    
}

void Sketch::draw()
{
    DrawKit::translate(centre);
    
    DrawKit::drawCircle(0.0f, 0.0f, 125.0f, 32);
}

void Sketch::keyPressed(int key, int modifiers)
{
    
}

void Sketch::keyReleased(int key, int modifiers)
{
    
}

void Sketch::mouseMoved(float x, float y)
{
    
}

void Sketch::mouseScrolled(float x, float y)
{
    
}

void Sketch::mouseButtonPressed(int button, int modifiers)
{
    
}

void Sketch::mouseButtonReleased(int button, int modifiers)
{
    
}

void Sketch::windowClosed()
{
    
}

void Sketch::windowDidResize()
{
    
}

void Sketch::windowReceivedPaths(int numberOfPaths, const char * paths [])
{
    
}
