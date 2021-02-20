//  DrawKit
//  Created by David Spry on 23/1/21.

#include "UIComponent.hpp"

namespace DrawKit {

UIComponent::UIComponent(const int32_t x,
                         const int32_t y,
                         const int32_t z,
                         const int32_t width,
                         const int32_t height)
{
    setPositionWithOrigin(x, y, z);
    setSizeFromOrigin(width, height);
}

const UISize<uint32_t> & UIComponent::getSize() const noexcept
{
    return size;
}

const UIPoint<int32_t> & UIComponent::getOrigin() const noexcept
{
    return origin;
}

const UIPoint<int32_t> & UIComponent::getCentre() const noexcept
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

void UIComponent::scaleFromCentre(float scaleFactor)
{
    int32_t const W = static_cast<int32_t>(static_cast<float>(size.w) * scaleFactor);
    int32_t const H = static_cast<int32_t>(static_cast<float>(size.h) * scaleFactor);
    
    setSizeFromCentre(W, H);
}

void UIComponent::scaleFromOrigin(float scaleFactor)
{
    int32_t const W = static_cast<int32_t>(static_cast<float>(size.w) * scaleFactor);
    int32_t const H = static_cast<int32_t>(static_cast<float>(size.h) * scaleFactor);
    
    setSizeFromOrigin(W, H);
}

void UIComponent::setSizeFromOrigin(int32_t width, int32_t height)
{
    size.w = width;
    size.h = height;
    setPositionWithOrigin(origin);
}

void UIComponent::setSizeFromOrigin(const UISize<uint32_t> & size)
{
    setSizeFromOrigin(size.w, size.h);
}

void UIComponent::setSizeFromCentre(int32_t width, int32_t height)
{
    size.w = width;
    size.h = height;
    setPositionWithCentre(centre);
}

void UIComponent::setSizeFromCentre(const UISize<uint32_t> & size)
{
    setSizeFromCentre(size.w, size.h);
}

void UIComponent::translate(int32_t x, int32_t y, int32_t z)
{
    setPositionWithCentre(centre.x + x, centre.y + y, centre.z + z);
}

void UIComponent::setPositionWithOrigin(int32_t x, int32_t y, int32_t z)
{
    origin.x = x;
    origin.y = y;
    origin.z = z;

    centre.x = x + static_cast<int32_t>(static_cast<float>(size.w) * 0.5f);
    centre.y = y + static_cast<int32_t>(static_cast<float>(size.h) * 0.5f);
    centre.z = z;
}

void UIComponent::setPositionWithOrigin(const UIPoint<int32_t> & xyz)
{
    setPositionWithOrigin(xyz.x, xyz.y, xyz.z);
}

void UIComponent::setPositionWithCentre(int32_t x, int32_t y, int32_t z)
{
    centre.x = x;
    centre.y = y;
    centre.z = z;
    
    origin.x = x - static_cast<int32_t>(static_cast<float>(size.w) * 0.5f);
    origin.y = y - static_cast<int32_t>(static_cast<float>(size.h) * 0.5f);
    origin.z = z;
}

void UIComponent::setPositionWithCentre(const UIPoint<int32_t> & xyz)
{
    setPositionWithCentre(xyz.x, xyz.y, xyz.z);
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
