//  DrawKit
//  Created by David Spry on 13/2/21.

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "dk.pch"

namespace DrawKit {

/// @brief The types of available renderers.

enum class RendererType { OPENGL };

/// @brief An abstract Renderer to be defined in subclass implementations.

class Renderer
{
public:
    Renderer()          = default;
    virtual ~Renderer() = default;

// MARK: - INITIALISATION

protected:
    /// @brief Initialise the renderer.

    virtual void initialise() = 0;
    
// MARK: - RENDER STAGE

public:
    /// @brief Destroy the renderer.

    virtual void destroy() = 0;
    
    /// @brief Begin the render cycle.
    /// @note  This is called once per frame.

    virtual void beginRender() = 0;
    
    /// @brief Complete the render cycle.
    /// @note  This is called once per frame.

    virtual void complRender() = 0;
    
// MARK: - RENDER SETTINGS
    
public:
    /// @brief Enable line and polygon smoothing.

    virtual void enableSmoothing()  = 0;
    
    /// @brief Disable line and polygon smoothing.
    
    virtual void disableSmoothing() = 0;

// MARK: - TRANSFORM
    
public:
    /// @brief Push a copy of the current matrix onto the matrix stack.

    virtual void pushMatrix() = 0;
    
    /// @brief Push the given matrix onto the matrix stack.
    /// @param matrix The matrix to be pushed onto the matrix stack.
    
    virtual void pushMatrix(const ModelViewProjectionMatrix & matrix) = 0;

    /// @brief Pop the current matrix from the matrix stack.

    virtual void popMatrix() = 0;

    /// @brief Set the scale of the current model-view-projection matrix.
    /// @param x The desired x-axis scaling factor.
    /// @param y The desired y-axis scaling factor.
    /// @param z The desired z-axis scaling factor.

    virtual void scale(float x, float y, float z) = 0;
    
    /// @brief Rotate the current model-view-projection matrix about the given axis.
    /// @param radians The desired rotation angle in radians.
    /// @param x The x-component of the desired rotation axis.
    /// @param y The y-component of the desired rotation axis.
    /// @param z The z-component of the desired rotation axis.

    virtual void rotate(float radians, float x, float y, float z) = 0;
    
    /// @brief Translate the current model-view-projection matrix.
    /// @param x The x-component of the desired translation.
    /// @param y The y-component of the desired translation.
    /// @param z The z-component of the desired translation.

    virtual void translate(float x, float y, float z = 0.0f) = 0;
    
// MARK: - CLEAR SCREEN

public:
    /// @brief Clear the screen using the current clear colour.

    virtual void clear() = 0;
    
    /// @brief Clear the screen using the given grayscale value.
    /// @param k The desired grayscale value.

    virtual void clear(float k) = 0;
    
    /// @brief Clear the screen using the given colour.
    /// @param colour The desired clear colour.

    virtual void clear(const Colour & colour) = 0;
    
    /// @brief Clear the screen using the given RGBA colour component values.
    /// @param r The red component of the desired colour.
    /// @param g The green component of the desired colour.
    /// @param b The blue component of the desired colour.
    /// @param a The alpha component of the desired colour.

    virtual void clear(float r, float g, float b, float a) = 0;
    
    /// @brief Set the current clear colour.
    /// @param colour The desired clear colour.

    virtual void setClearColour(const Colour & colour) = 0;
    
    /// @brief Get the current clear colour.

    virtual const Colour & getClearColour() = 0;

// MARK: - DRAWING PATHS

public:
    /// @brief Stroke the path represented by the given vertices.
    /// @param vertices The path's vertices, including a colour for each vertex.
    /// @param strokeWidth The desired stroke width.
    /// @param pathIsClosed A flag to indicate whether the path should be closed or not.

    virtual void drawPath(const std::vector<vertex_colour_t> & vertices, float strokeWidth, bool pathIsClosed) = 0;

// MARK: - DRAWING PRIMITIVES

public:
    /// @brief Draw a circle at the given centre point.
    /// @param x The x-coordinate of the desired centre point.
    /// @param y The y-coordinate of the desired centre point.
    /// @param z The z-coordinate of the desired centre point.
    /// @param r The desired circle radius.
    /// @param segments The desired number of triangle segments to create the circle with.
    /// @param colour The desired colour.

    virtual void drawCircle(float x, float y, float z, float r, uint16_t segments, const Colour & colour) = 0;
    
    /// @brief Draw a circle at the given centre point.
    /// @param x The x-coordinate of the desired centre point.
    /// @param y The y-coordinate of the desired centre point.
    /// @param z The z-coordinate of the desired centre point.
    /// @param r The desired circle radius.
    /// @param strokeWidth The desired stroke width.
    /// @param segments The desired number of triangle segments to create the circle with.
    /// @param colour The desired stroke colour.

    virtual void drawCircleStroke(float x, float y, float z, float r, float strokeWidth, uint16_t segments, const Colour & colour) = 0;

    /// @brief Draw a circle at the given centre point.
    /// @param x The x-coordinate of the desired centre point.
    /// @param y The y-coordinate of the desired centre point.
    /// @param z The z-coordinate of the desired centre point.
    /// @param w The desired ellipse width.
    /// @param h The desired ellipse height.
    /// @param colour The desired colour.
    /// @param segments The desired number of triangle segments to create the circle with.
    
    virtual void drawEllipse(float x, float y, float z, float w, float h, uint16_t segments, const Colour & colour) = 0;

    /// @brief Draw a rectangle at the given origin point.
    /// @param x The x-coordate of the desired origin point.
    /// @param y The y-coordate of the desired origin point.
    /// @param z The z-coordate of the desired origin point.
    /// @param w The desired width in pixels.
    /// @param h The desired height in pixels.
    /// @param colour The desired colour.

    virtual void drawRectangle(float x, float y, float z, float w, float h, const Colour & colour) = 0;

    /// @brief Draw the outline of a rectangle at the given origin point.
    /// @param x The x-coordate of the desired origin point.
    /// @param y The y-coordate of the desired origin point.
    /// @param z The z-coordate of the desired origin point.
    /// @param w The desired width in pixels.
    /// @param h The desired height in pixels.
    /// @param strokeWidth The desired stroke width.
    /// @param colour The desired stroke colour.

    virtual void drawRectangleStroke(float x, float y, float z, float w, float h, float strokeWidth, const Colour & colour) = 0;

    /// @brief Draw a triangle at the given position.
    /// @param xa The x-coordinate of the first point.
    /// @param ya The y-coordinate of the first point.
    /// @param za The z-coordinate of the first point.
    /// @param xb The x-coordinate of the second point.
    /// @param yb The y-coordinate of the second point.
    /// @param zb The z-coordinate of the second point.
    /// @param xc The x-coordinate of the third point.
    /// @param yc The y-coordinate of the third point.
    /// @param zc The z-coordinate of the third point.
    /// @param colour The desired colour.

    virtual void drawTriangle (float xa, float ya, float za,
                               float xb, float yb, float zb,
                               float xc, float yc, float zc, const Colour & colour) = 0;
    
protected:
    Colour clearColour = Colour::black;
};

}

#endif
