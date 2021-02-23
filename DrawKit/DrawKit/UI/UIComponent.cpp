//  DrawKit
//  Created by David Spry on 23/1/21.

#include "UIComponent.hpp"

namespace DrawKit {

UIComponent::UIComponent(const float x,
                         const float y,
                         const float z,
                         const float width,
                         const float height)
{
    setPositionWithOrigin(x, y, z);
    setSizeFromOrigin(width, height);
}

const UISize<float> & UIComponent::getSize() const noexcept
{
    return size;
}

const UIPoint<float> & UIComponent::getOrigin() const noexcept
{
    return origin;
}

const UIPoint<float> & UIComponent::getCentre() const noexcept
{
    return centre;
}

const Colour & UIComponent::getColour() const noexcept
{
    return colour;
}

void UIComponent::setColour(const Colour& colour) noexcept
{
    this->colour = colour;
}

void UIComponent::setBounds(const UIComponent & bounds)
{
    setSizeFromCentre(bounds.size);
    setPositionWithCentre(bounds.centre);
}

void UIComponent::scaleFromCentre(float scaleFactor)
{
    float const W = static_cast<float>(static_cast<float>(size.w) * scaleFactor);
    float const H = static_cast<float>(static_cast<float>(size.h) * scaleFactor);
    
    setSizeFromCentre(W, H);
}

void UIComponent::scaleFromOrigin(float scaleFactor)
{
    float const W = static_cast<float>(static_cast<float>(size.w) * scaleFactor);
    float const H = static_cast<float>(static_cast<float>(size.h) * scaleFactor);
    
    setSizeFromOrigin(W, H);
}

void UIComponent::scaleFromCentre(float scaleFactorX, float scaleFactorY)
{
    float const W = static_cast<float>(static_cast<float>(size.w) * scaleFactorX);
    float const H = static_cast<float>(static_cast<float>(size.h) * scaleFactorY);
    
    setSizeFromCentre(W, H);
}

void UIComponent::scaleFromOrigin(float scaleFactorX, float scaleFactorY)
{
    float const W = static_cast<float>(static_cast<float>(size.w) * scaleFactorX);
    float const H = static_cast<float>(static_cast<float>(size.h) * scaleFactorY);
    
    setSizeFromOrigin(W, H);
}

void UIComponent::setSizeFromOrigin(float width, float height)
{
    size.w = width;
    size.h = height;
    setPositionWithOrigin(origin);
}

void UIComponent::setSizeFromOrigin(const UISize<float> & size)
{
    setSizeFromOrigin(size.w, size.h);
}

void UIComponent::setSizeFromCentre(float width, float height)
{
    size.w = width;
    size.h = height;
    setPositionWithCentre(centre);
}

void UIComponent::setSizeFromCentre(const UISize<float> & size)
{
    setSizeFromCentre(size.w, size.h);
}

void UIComponent::translate(float x, float y, float z)
{
    setPositionWithCentre(centre.x + x, centre.y + y, centre.z + z);
}

void UIComponent::setPositionWithOrigin(float x, float y, float z)
{
    origin.x = x;
    origin.y = y;
    origin.z = z;

    centre.x = x + size.w * 0.5f;
    centre.y = y + size.h * 0.5f;
    centre.z = z;
}

void UIComponent::setPositionWithOrigin(const UIPoint<float> & xyz)
{
    setPositionWithOrigin(xyz.x, xyz.y, xyz.z);
}

void UIComponent::setPositionWithCentre(float x, float y, float z)
{
    centre.x = x;
    centre.y = y;
    centre.z = z;
    
    origin.x = x - size.w * 0.5f;
    origin.y = y - size.h * 0.5f;
    origin.z = z;
}

void UIComponent::setPositionWithCentre(const UIPoint<float> & xyz)
{
    setPositionWithCentre(xyz.x, xyz.y, xyz.z);
}

void UIComponent::setMargins(const float marginSize)
{
    setMargins(marginSize, marginSize, marginSize, marginSize);
}

void UIComponent::setMargins(const UIMargins<float>& margins)
{
    setMargins(margins.t, margins.l, margins.r, margins.b);
}

void UIComponent::setMargins(const float top, const float left, const float right, const float bottom)
{
    margins.set(top, left, right, bottom);
}

std::string const UIComponent::toString() const
{
    return "<x: " + std::to_string(origin.x) + ","
           " y: " + std::to_string(origin.y) + "," +
           " z: " + std::to_string(origin.z) + "," +
           " w: " + std::to_string(size.w)   + "," +
           " h: " + std::to_string(size.h)   + ">";
}

std::ostream & operator << (std::ostream & stream, const UIComponent & component)
{
    return (stream << component.toString() << '\n');
}

}
