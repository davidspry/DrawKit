//  DrawKit
//  Created by David Spry on 20/2/21.

#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "dk.pch"
#include "UITypes.h"
#include "Rectangle.hpp"

namespace DrawKit {

class Triangle: public UIComponent
{
public:
    struct Vertices { UIPoint<float> a, b, c; };

public:
    /// @brief Create a triangle centred at the given position with the given bounding box size.
    /// @param x The x-coordinate of the desired centre position.
    /// @param y The y-coordinate of the desired centre position.
    /// @param width   The desired width of the triangle's bounding box.
    /// @param height The desired height of the triangle's bounding box.
    
    Triangle(const int32_t x = 0,
             const int32_t y = 0,
             const int32_t width  = 100,
             const int32_t height = 100);

    /// @brief Create a triangle with the given vertices.
    /// @param vertices The desired triangle vertices.

    Triangle(const Vertices & vertices);

public:
    /// @brief Get the triangle's vertices.

    const Vertices & getVertices() const;
    
    /// @brief Compute the bounding box of the given triangle vertices.
    /// @param vertices The triangle vertices whose bounding box should be computed.

    static Rectangle computeBoundingBox(const Triangle::Vertices & vertices);

public:
    void setVertices(const UIPoint<float> & a, const UIPoint<float> & b, const UIPoint<float> & c);

// MARK: - UIComponent Overrides

public:
    void setSizeFromOrigin(int32_t width, int32_t height) override;
    void setSizeFromOrigin(const UISize<uint32_t> & size) override;
    void setSizeFromCentre(int32_t width, int32_t height) override;
    void setSizeFromCentre(const UISize<uint32_t> & size) override;
    void setPositionWithOrigin(int32_t x, int32_t y, int32_t z) override;
    void setPositionWithOrigin(const UIPoint<int32_t> & xyz) override;
    void setPositionWithCentre(int32_t x, int32_t y, int32_t z) override;
    void setPositionWithCentre(const UIPoint<int32_t> & xyz) override;
    
protected:
    Vertices vertices;
};

}

#endif
