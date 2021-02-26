//  DrawKit
//  Created by David Spry on 26/2/21.

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "dk.pch"
#include "GlobalInterface.hpp"
#include "ModelViewProjectionMatrix.hpp"

namespace DrawKit {

class Camera
{
public:
    Camera() = default;
    
public:
    virtual void begin();
    virtual void end();

public:
    virtual void lookAtPoint(const UIPoint<float> &xyz);
    virtual void lookAtPoint(float x, float y, float z);
    virtual void setPosition(const UIPoint<float> &xyz);
    virtual void setPosition(float x, float y, float z);
    
public:
    virtual void scale(float scaleFactor);
    virtual void translate(float x, float y, float z);
    virtual void rotateByDegrees(float degrees, float x, float y, float z);
    virtual void rotateByRadians(float radians, float x, float y, float z);

protected:
    ModelViewProjectionMatrix matrix;
    
protected:
    bool initialised;

protected:
    UISize <float> windowSize;
    UIPoint<float> position;
};

}

#endif
