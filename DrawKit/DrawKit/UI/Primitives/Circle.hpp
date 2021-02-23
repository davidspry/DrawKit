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
    Circle(const float x = 0.0f,
           const float y = 0.0f,
           const float radius = 50.0f,
           const uint16_t segments = 64);

public:
    const float & getRadius() const;
    const uint16_t & getNumberOfSegments() const;

public:
    void setRadius(float circleRadius);
    void setNumberOfSegments(uint16_t circleSegments);
    
public:
    void setSizeFromOrigin(float width, float height) override;
    void setSizeFromCentre(float width, float height) override;
    
private:
    float radius;
    uint16_t segments;
};

}

#endif
