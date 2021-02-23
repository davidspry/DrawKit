//  DrawKit
//  Created by David Spry on 23/1/21.

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "dk.pch"
#include "UIComponent.hpp"

namespace DrawKit {

class Rectangle: public UIComponent
{
public:
    Rectangle(const float x = 0.0f,
              const float y = 0.0f,
              const float width  = 100.0f,
              const float height = 100.0f):
    UIComponent(x, y, 0, width, height)
    {
        
    }
    
    Rectangle(const UIPoint<float> & origin,
              const UISize <float> & size):
    UIComponent(origin.x, origin.y, origin.z, size.w, size.h)
    {
        
    }

public:
    /// @brief Return a copy of the Rectangle translated to the given origin point.
    /// @param x The x-coordinate of the desired origin point for the returned Rectangle.
    /// @param y The y-coordinate of the desired origin point for the returned Rectangle.

    [[nodiscard]] Rectangle translatedTo(int x, int y) noexcept;
    
    /// @brief Remove a margin from the edges of the Rectangle.
    /// @param fromTop The desired number of pixels to remove from the top.
    /// @param fromLeft The desired number of pixels to remove from the left.
    /// @param fromRight The desired number of pixels to remove from the right.
    /// @param fromBottom The desired number of pixels to remove from the bottom.

    Rectangle & trim(uint32_t fromTop, uint32_t fromLeft, uint32_t fromRight, uint32_t fromBottom);
    
    /// @brief Remove a rectangle from the top of the Rectangle.
    /// @param amountToRemove The desired number of pixels to remove from the top.

    Rectangle & trimFromTop(uint32_t amountToRemove);
    
    /// @brief Remove a rectangle from the bottom of the Rectangle.
    /// @param amountToRemove The desired number of pixels to remove from the bottom.

    Rectangle & trimFromBottom(uint32_t amountToRemove);
    
    /// @brief Remove a rectangle from the left of the Rectangle.
    /// @param amountToRemove The desired number of pixels to remove from the left.

    Rectangle & trimFromLeft(uint32_t amountToRemove);
    
    /// @brief Remove a rectangle from the right of the Rectangle.
    /// @param amountToRemove The desired number of pixels to remove from the right.

    Rectangle & trimFromRight(uint32_t amountToRemove);
    
    /// @brief Remove a rectangle from the top of the Rectangle and return it.
    /// @param amountToRemove The desired number of pixels to remove from the top.

    [[nodiscard]] Rectangle removeFromTop(uint32_t amountToRemove);
    
    /// @brief Remove a rectangle from the bottom of the Rectangle and return it.
    /// @param amountToRemove The desired number of pixels to remove from the bottom.

    [[nodiscard]] Rectangle removeFromBottom(uint32_t amountToRemove);
    
    /// @brief Remove a rectangle from the left of the Rectangle and return it.
    /// @param amountToRemove The desired number of pixels to remove from the left.

    [[nodiscard]] Rectangle removeFromLeft(uint32_t amountToRemove);
    
    /// @brief Remove a rectangle from the right of the Rectangle and return it.
    /// @param amountToRemove The desired number of pixels to remove from the right.

    [[nodiscard]] Rectangle removeFromRight(uint32_t amountToRemove);
    
    /// @brief Subdivide the Rectangle into some number of smaller rectangles along the given axis.
    /// @param axis The axis along which to subdivide the Rectangle
    /// @param subdivisions The number of subdivisions to compute
    /// @throw An exception will be thrown in the case where the requested number of subdivisions is not positive.

    [[nodiscard]] std::vector<Rectangle> subdivide(Axis axis, uint32_t subdivisions) const noexcept(false);
    
public:
    /// @brief Subtract the given margins from the Rectangle and return the result.
    /// @param margins The margins to be subtracted from the Rectangle.

    template <typename T>
    [[nodiscard]] inline Rectangle subtractMargins(UIMargins<T> margins) noexcept
    {
        setSizeFromCentre(size.w - margins.l - margins.r, size.h - margins.t - margins.b);

        return *(this);
    }
};

}

#endif
