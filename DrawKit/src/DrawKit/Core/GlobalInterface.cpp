//  DrawKit
//  Created by David Spry on 14/2/21.

#include "GlobalInterface.hpp"

namespace DrawKit {

Renderer * const getRenderer()
{
    return getApplicationManager()->getRenderer();
}

ApplicationManager * const getApplicationManager()
{
    static ApplicationManager * manager = nullptr;
    
    if (!manager)
    {
        manager = ApplicationManager::create();
    }
    
    return manager;
}

// MARK: - APPLICATION INTERFACE

void launch(Application* application, const Window::Attributes& attributes, RendererType && renderer)
{
    getApplicationManager()->run(application, renderer, attributes);
}

// MARK: - RENDERING INTERFACE

void setBackgroundColour(const Colour & colour)
{
    getRenderer()->setClearColour(colour);
}

void setBackgroundColour(const Colour && colour)
{
    setBackgroundColour(colour);
}

void setBackgroundColour(uint8_t k)
{
    setBackgroundColour(k, k, k);
}

void setBackgroundColour(uint8_t r, uint8_t g, uint8_t b)
{
    Colour const colour (r, g, b);
    
    getRenderer()->setClearColour(colour);
}

// MARK: - DRAWING INTERFACE

void drawCircle(const Circle & circle)
{
    const auto & centre = circle.getCentre();
    const auto & radius = circle.getRadius();
    const auto & colour = circle.getColour();
    
    drawCircle(centre.x, centre.y, centre.z, radius, circle.getNumberOfSegments(), colour);
}

void drawCircle(float x, float y, float r, uint16_t segments, Colour colour)
{
    getRenderer()->drawCircle(x, y, r, segments, colour);
}

void drawCircle(float x, float y, float z, float r, uint16_t segments, Colour colour)
{
    getRenderer()->drawCircle(x, y, z, r, segments, colour);
}

void drawRectangle(const Rectangle & rectangle)
{
    const auto & size   = rectangle.getSize();
    const auto & origin = rectangle.getOrigin();
    const auto & colour = rectangle.getColour();
    
    drawRectangle(origin.x, origin.y, origin.z, size.w, size.h, colour);
}

void drawRectangle(float x, float y, float w, float h, Colour colour)
{
    getRenderer()->drawRectangle(x, y, w, h, colour);
}

void drawRectangle(float x, float y, float z, float w, float h, Colour colour)
{
    getRenderer()->drawRectangle(x, y, z, w, h, colour);
}

}
