//  DrawKit
//  Created by David Spry on 14/2/21.

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "dk.pch"
#include "UITypes.h"

namespace DrawKit {

class Circle: public UIPrimitive
{
public:
    Circle(int32_t  x = 0,
           int32_t  y = 0,
           uint32_t radius   = 50,
           uint16_t segments = 64):
    UIPrimitive(x, y, 2.0f * radius, 2.0f * radius)
    {
        this->radius   = radius;
        this->segments = segments;
    }
    
public:
    const uint32_t & getRadius() const;
    const uint16_t & getNumberOfSegments() const;

public:
    void setRadius(uint32_t circleRadius);
    void setNumberOfSegments(uint16_t circleSegments);
    
public:
    void setSizeFromOrigin(int32_t width, int32_t height) override;
    void setSizeFromCentre(int32_t width, int32_t height) override;
    
private:
    uint32_t radius;
    uint16_t segments;
};

}

#endif
