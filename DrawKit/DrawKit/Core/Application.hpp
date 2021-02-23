//  DrawKit
//  Created by David Spry on 23/1/21.

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "dk.pch"
#include "EventResponder.h"

namespace DrawKit
{

class Application: public EventResponder
{
public:
    Application()          = default;
    virtual ~Application() = default;
    
public:
    virtual void prepare() = 0;
    virtual void update()  = 0;
    virtual void draw()    = 0;

public:
    virtual void keyPressed (int key, int modifiers) override {}
    virtual void keyReleased(int key, int modifiers) override {}

public:
    virtual void mouseMoved(float x, float y) override {}
    virtual void mouseScrolled(float x, float y) override {}
    virtual void mouseButtonPressed (int button, int modifiers) override {}
    virtual void mouseButtonReleased(int button, int modifiers) override {}

public:
    virtual void windowClosed() override {}
    virtual void windowDidResize() override {}
    virtual void windowReceivedPaths(int numberOfPaths, const char * paths []) override {}
    
public:
    /// @brief This function is called when the window is resized.
    /// @param width The new window width.
    /// @param height The new window height.

    void windowResized(uint32_t width, uint32_t height)
    {
        size.w   = static_cast<float>(width);
        size.h   = static_cast<float>(height);
        centre.x = static_cast<float>(size.w) * 0.5f;
        centre.y = static_cast<float>(size.h) * 0.5f;
    }

protected:
    UISize <float> size;
    UIPoint<float> centre;
    
private:
    UIPoint<float> cursorPosition;
};

}

#endif
