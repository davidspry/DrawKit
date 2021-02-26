// Sketch
// DrawKit

#ifndef SKETCH_HPP
#define SKETCH_HPP

#include "DrawKit.h"

class Sketch: public DrawKit::Application
{
public:
    void prepare() override;
    void update()  override;
    void draw()    override;
    
public:
    void keyPressed(int key, int modifiers)  override;
    void keyReleased(int key, int modifiers) override;

public:
    void mouseMoved(float x, float y)    override;
    void mouseScrolled(float x, float y) override;
    void mouseButtonPressed (int button, int modifiers) override;
    void mouseButtonReleased(int button, int modifiers) override;
    
public:
    void windowClosed() override;
    void windowDidResize() override;
    void windowReceivedPaths(int numberOfPaths, const char * paths []) override;
};

#endif
