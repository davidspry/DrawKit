//  DrawKit
//  Created by David Spry on 14/2/21.

#include "Circle.hpp"

namespace DrawKit {

const uint32_t & Circle::getRadius() const
{
    return radius;
}

const uint16_t & Circle::getNumberOfSegments() const
{
    return segments;
}

void Circle::setRadius(uint32_t circleRadius)
{
    radius = circleRadius;
    
    setSizeFromCentre(radius * 2, radius * 2);
}

void Circle::setNumberOfSegments(uint16_t circleSegments)
{
    segments = circleSegments;
}

void Circle::setSizeFromOrigin(int32_t width, int32_t height)
{
    UIComponent::setSizeFromOrigin(width, height);

    radius = std::min(std::abs(width), std::abs(height));
    radius = radius / 2;
}

void Circle::setSizeFromCentre(int32_t width, int32_t height)
{
    UIComponent::setSizeFromCentre(width, height);

    radius = std::min(std::abs(width), std::abs(height));
    radius = radius / 2;
}

}
