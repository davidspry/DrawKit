//  DrawKit
//  Created by David Spry on 13/2/21.

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "dk.pch"
#include "UIPrimitives.h"

namespace DrawKit {

/// @brief Available renderers.

enum class RendererType { OPENGL };

typedef struct
{
    float x, y, z;
    DrawKit::RGBA rgba;
}   vertex_t;

class Renderer
{
public:
    Renderer()          = default;
    virtual ~Renderer() = default;

// MARK: - RENDER STAGE

public:
    virtual void destroy() = 0;
    virtual void beginRender() = 0;
    virtual void complRender() = 0;

// MARK: - CLEAR SCREEN

public:
    virtual void clear() = 0;
    virtual void clear(float k) = 0;
    virtual void clear(const Colour & colour) = 0;
    virtual void clear(float r, float g, float b, float a) = 0;
    virtual void setClearColour(const Colour & colour) = 0;
    virtual const Colour & getClearColour() = 0;
    
// MARK: - DRAWING PRIMITIVES

public:
    /// @brief Draw a circle at the given centre point.
    /// @param x The x-coordinate of the desired centre point.
    /// @param y The y-coordinate of the desired centre point.
    /// @param r The desired circle radius.
    /// @param segments The desired number of triangle segments to create the circle with.
    /// @param colour The desired colour.
    /// @note  The z-coordinate will be zero.

    virtual void drawCircle(float x, float y, float r, uint16_t segments, Colour colour) = 0;
    
    /// @brief Draw a circle at the given centre point.
    /// @param x The x-coordinate of the desired centre point.
    /// @param y The y-coordinate of the desired centre point.
    /// @param z The z-coordinate of the desired centre point.
    /// @param r The desired circle radius.
    /// @param colour The desired colour.
    /// @param segments The desired number of triangle segments to create the circle with.

    virtual void drawCircle(float x, float y, float z, float r, uint16_t segments, Colour colour) = 0;
    
    /// @brief Draw a circle at the given centre point.
    /// @param x The x-coordinate of the desired centre point.
    /// @param y The y-coordinate of the desired centre point.
    /// @param w The desired ellipse width.
    /// @param h The desired ellipse height.
    /// @param colour The desired colour.
    /// @param segments The desired number of triangle segments to create the circle with.
    /// @note  The z-coordinate will be zero.
    
    virtual void drawEllipse(float x, float y, float w, float h, uint16_t segments, Colour colour) = 0;
    
    /// @brief Draw a circle at the given centre point.
    /// @param x The x-coordinate of the desired centre point.
    /// @param y The y-coordinate of the desired centre point.
    /// @param z The z-coordinate of the desired centre point.
    /// @param w The desired ellipse width.
    /// @param h The desired ellipse height.
    /// @param colour The desired colour.
    /// @param segments The desired number of triangle segments to create the circle with.
    
    virtual void drawEllipse(float x, float y, float z, float w, float h, uint16_t segments, Colour colour) = 0;
    
    /// @brief Draw a rectangle at the given origin point.
    /// @param x The x-coordate of the desired origin point.
    /// @param y The y-coordate of the desired origin point.
    /// @param w The desired width in pixels.
    /// @param h The desired height in pixels.
    /// @param colour The desired colour.
    /// @note  The z-coordinate will be zero.

    virtual void drawRectangle(float x, float y, float w, float h, Colour colour) = 0;

    /// @brief Draw a rectangle at the given origin point.
    /// @param x The x-coordate of the desired origin point.
    /// @param y The y-coordate of the desired origin point.
    /// @param z The z-coordate of the desired origin point.
    /// @param w The desired width in pixels.
    /// @param h The desired height in pixels.
    /// @param colour The desired colour.

    virtual void drawRectangle(float x, float y, float z, float w, float h, Colour colour) = 0;
    
    
    virtual void drawRectangleStroke(float x, float y, float w, float h, Colour colour) = 0;
    
    /// @brief Draw a triangle at the given position.
    /// @param xa The x-coordinate of the first point.
    /// @param ya The y-coordinate of the first point.
    /// @param xb The x-coordinate of the second point.
    /// @param yb The y-coordinate of the second point.
    /// @param xc The x-coordinate of the third point.
    /// @param yc The y-coordinate of the third point.
    /// @param colour The desired colour.
    /// @note  The z-coordinate of each point will be zero.

    virtual void drawTriangle (float xa, float ya,
                               float xb, float yb,
                               float xc, float yc, Colour colour) = 0;

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
                               float xc, float yc, float zc, Colour colour) = 0;

// MARK: - INITIALISATION

protected:
    virtual void initialise() = 0;
    
protected:
    Colour clearColour = Colour::black;
};

}

#endif
