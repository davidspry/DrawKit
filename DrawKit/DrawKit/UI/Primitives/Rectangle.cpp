//  DrawKit
//  Created by David Spry on 24/2/21.

#include "Rectangle.hpp"

namespace DrawKit {

Rectangle Rectangle::translatedTo(int x, int y) noexcept
{
    Rectangle r = *(this);

    r.setPositionWithOrigin(x, y, 0);

    return r;
}

Rectangle & Rectangle::trim(uint32_t fromTop, uint32_t fromLeft, uint32_t fromRight, uint32_t fromBottom)
{
    trimFromTop(fromTop);
    trimFromLeft(fromLeft);
    trimFromRight(fromRight);
    trimFromBottom(fromBottom);
    
    return *(this);
}

Rectangle & Rectangle::trimFromTop(uint32_t amountToRemove)
{
    uint32_t const removed = std::fmin(amountToRemove, size.h);
    
    setSizeFromOrigin(size.w, size.h - removed);
    
    translate(0, removed);
    
    return *(this);
}

Rectangle & Rectangle::trimFromBottom(uint32_t amountToRemove)
{
    uint32_t const removed = std::fmin(amountToRemove, size.h);

    setSizeFromOrigin(size.w, size.h - removed);
    
    return *(this);
}

Rectangle & Rectangle::trimFromLeft(uint32_t amountToRemove)
{
    uint32_t const removed = std::fmin(amountToRemove, size.w);

    setSizeFromOrigin(size.w - removed, size.h);
    
    translate(removed, 0);
    
    return *(this);
}

Rectangle& Rectangle::trimFromRight(uint32_t amountToRemove)
{
    uint32_t const removed = std::fmin(amountToRemove, size.w);

    setSizeFromOrigin(size.w - removed, size.h);
    
    return *(this);
}

Rectangle Rectangle::removeFromTop(uint32_t amountToRemove)
{
    uint32_t const removed = std::fmin(amountToRemove, size.h);

    setSizeFromOrigin(size.w, size.h - removed);
    
    translate(0, removed);
    
    return {
        static_cast<float>(origin.x),
        static_cast<float>(origin.y),
        static_cast<float>(size.w),
        static_cast<float>(removed)
    };
}

Rectangle Rectangle::removeFromBottom(uint32_t amountToRemove)
{
    uint32_t const removed = std::fmin(amountToRemove, size.h);

    setSizeFromOrigin(size.w, size.h - removed);
    
    return {
        static_cast<float>(origin.x),
        static_cast<float>(origin.y + size.h - removed),
        static_cast<float>(size.w),
        static_cast<float>(removed)
    };
}

Rectangle Rectangle::removeFromLeft(uint32_t amountToRemove)
{
    uint32_t const removed = std::fmin(amountToRemove, size.w);

    setSizeFromOrigin(size.w - removed, size.h);
    
    translate(removed, 0);
    
    return {
        static_cast<float>(origin.x),
        static_cast<float>(origin.y),
        static_cast<float>(removed),
        static_cast<float>(size.h)
    };
}

Rectangle Rectangle::removeFromRight(uint32_t amountToRemove)
{
    uint32_t const removed = std::fmin(amountToRemove, size.w);

    setSizeFromOrigin(size.w - removed, size.h);
    
    return {
        static_cast<float>(origin.x + size.w - removed),
        static_cast<float>(origin.y),
        static_cast<float>(removed),
        static_cast<float>(size.h)
    };
}

std::vector<Rectangle> Rectangle::subdivide(Axis axis, uint32_t subdivisions) const noexcept(false)
{
    std::vector<Rectangle> vector;
    
    subdivisions = std::max(static_cast<int>(subdivisions), 1);

    vector.reserve(subdivisions);
    
    const float scale = 1.0f / static_cast<float>(subdivisions);
    
    for (int k = 0; k < subdivisions; ++k)
    {
        Rectangle r = *(this);
        int const w = subdivisions - k - 1;
        
        if (axis == Axis::X) {
            r.scaleFromOrigin(scale, 1.0f);
            r.translate(w * size.w * scale, 0);
        }

        else if (axis == Axis::Y) {
            r.scaleFromOrigin(1.0f, scale);
            r.translate(0, w * size.h * scale);
        }

        vector.push_back(r);
    }

    return vector;
}

}
