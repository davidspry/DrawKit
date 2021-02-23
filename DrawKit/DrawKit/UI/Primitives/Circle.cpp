//  DrawKit
//  Created by David Spry on 14/2/21.

#include "Circle.hpp"

namespace DrawKit {

Circle::Circle(const float x, const float y, const float radius, const uint16_t segments):
UIComponent(x, y, 0, 2.0f * radius, 2.0f * radius)
{
    this->radius   = radius;
    this->segments = segments;
}

const float & Circle::getRadius() const
{
    return radius;
}

const uint16_t & Circle::getNumberOfSegments() const
{
    return segments;
}

void Circle::setRadius(float circleRadius)
{
    radius = circleRadius;
    
    setSizeFromCentre(radius * 2, radius * 2);
}

void Circle::setNumberOfSegments(uint16_t circleSegments)
{
    segments = circleSegments;
}

void Circle::setSizeFromOrigin(float width, float height)
{
    UIComponent::setSizeFromOrigin(width, height);

    radius = std::min(std::abs(width), std::abs(height));
    radius = radius / 2;
}

void Circle::setSizeFromCentre(float width, float height)
{
    UIComponent::setSizeFromCentre(width, height);

    radius = std::min(std::abs(width), std::abs(height));
    radius = radius / 2;
}

}
