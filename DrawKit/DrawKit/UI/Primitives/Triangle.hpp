//  DrawKit
//  Created by David Spry on 20/2/21.

#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "dk.pch"
#include "Rectangle.hpp"
#include "UIComponent.hpp"

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
    
    Triangle(const float x = 0.0f,
             const float y = 0.0f,
             const float width  = 100.0f,
             const float height = 100.0f);

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
    void setSizeFromOrigin(float width, float height) override;
    void setSizeFromOrigin(const UISize<float> & size) override;
    void setSizeFromCentre(float width, float height) override;
    void setSizeFromCentre(const UISize<float> & size) override;
    void setPositionWithOrigin(float x, float y, float z) override;
    void setPositionWithOrigin(const UIPoint<float> & xyz) override;
    void setPositionWithCentre(float x, float y, float z) override;
    void setPositionWithCentre(const UIPoint<float> & xyz) override;
    
protected:
    Vertices vertices;
};

}

#endif
