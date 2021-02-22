//  DrawKit
//  Created by David Spry on 14/2/21.

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "dk.pch"
#include "UIComponent.hpp"

namespace DrawKit {

class Circle: public UIComponent
{
public:
    Circle(const int32_t  x = 0,
           const int32_t  y = 0,
           const uint32_t radius = 50,
           const uint16_t segments = 64);

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
