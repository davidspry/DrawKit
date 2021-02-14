//  DrawKit
//  Created by David Spry on 2/2/21.

#ifndef EVENT_RESPONDER_H
#define EVENT_RESPONDER_H

#include "dk.pch"

namespace DrawKit
{

class EventResponder
{
public:
     EventResponder() = default;
    ~EventResponder() = default;
    
public:
    virtual void keyPressed (int key, int modifiers) = 0;
    virtual void keyReleased(int key, int modifiers) = 0;
    
public:
    virtual void mouseMoved(float x, float y) = 0;
    virtual void mouseScrolled(float x, float y) = 0;
    virtual void mouseButtonPressed (int button, int modifiers) = 0;
    virtual void mouseButtonReleased(int button, int modifiers) = 0;

public:
    virtual void windowClosed() = 0;
    virtual void windowDidResize() = 0;
    virtual void windowReceivedPaths(int numberOfPaths, const char * paths []) = 0;
};

}

#endif
