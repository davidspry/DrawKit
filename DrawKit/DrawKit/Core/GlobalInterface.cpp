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

void setWindowPosition(int x, int y)
{
    getApplicationManager()->setWindowPosition(x, y);
}

// MARK: - RENDERING INTERFACE

void enableSmoothing()
{
    getRenderer()->enableSmoothing();
}

void disableSmoothing()
{
    getRenderer()->disableSmoothing();
}

void scale(float scaleFactor)
{
    getRenderer()->scale(scaleFactor, scaleFactor, scaleFactor);
}

void scale(glm::vec3 scaleFactor)
{
    getRenderer()->scale(scaleFactor.x, scaleFactor.y, scaleFactor.z);
}

void rotateByRadians(float radians, Axis axis)
{
    getRenderer()->rotate(radians,
                          static_cast<float>(axis == Axis::X),
                          static_cast<float>(axis == Axis::Y),
                          static_cast<float>(axis == Axis::Z));
}

void rotateByRadians(float radians, float x, float y, float z)
{
    getRenderer()->rotate(radians, x, y, z);
}

void rotateByDegrees(float degrees, Axis axis)
{
    float const radians = glm::radians(degrees);
    
    getRenderer()->rotate(radians,
                          static_cast<float>(axis == Axis::X),
                          static_cast<float>(axis == Axis::Y),
                          static_cast<float>(axis == Axis::Z));
}

void rotateByDegrees(float degrees, float x, float y, float z)
{
    float const radians = glm::radians(degrees);
    
    getRenderer()->rotate(radians, x, y, z);
}

void translate(float x, float y, float z)
{
    getRenderer()->translate(x, y, z);
}

void translate(const UIPoint<float> & xyz)
{
    getRenderer()->translate(xyz.x, xyz.y, xyz.z);
}

void pushMatrix()
{
    getRenderer()->pushMatrix();
}

void popMatrix()
{
    getRenderer()->popMatrix();
}

void setFrameRate(uint16_t frameRate)
{
    getApplicationManager()->setFrameRate(frameRate);
}

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

const Colour & getBackgroundColour()
{
    return getRenderer()->getClearColour();
}

// MARK: - WINDOW INTERFACE

UISize<uint32_t> getWindowSize()
{
    const Window * const window = getApplicationManager()->getPlatformWindow();

    return {
        window->getWidth(),
        window->getHeight()
    };
}

uint32_t getWindowWidth()
{
    return getApplicationManager()->getPlatformWindow()->getWidth();
}

uint32_t getWindowHeight()
{
    return getApplicationManager()->getPlatformWindow()->getHeight();
}

// MARK: - DRAWING INTERFACE

void draw(const Circle & circle)
{
    const auto & radius = circle.getRadius();
    const auto & centre = circle.getCentre();
    const auto & colour = circle.getColour();
    const auto & segments = circle.getNumberOfSegments();
    
    getRenderer()->drawCircle(centre.x, centre.y, centre.z, radius, segments, colour);
}

void draw(const Rectangle & rectangle)
{
    const auto & size   = rectangle.getSize();
    const auto & origin = rectangle.getOrigin();
    const auto & colour = rectangle.getColour();
    
    getRenderer()->drawRectangle(origin.x, origin.y, origin.z, size.width, size.height, colour);
}

void draw(const Triangle & triangle)
{
    const DrawKit::Colour & colour = triangle.getColour();
    const Triangle::Vertices & v   = triangle.getVertices();

    getRenderer()->drawTriangle(v.a.x, v.a.y, v.a.z, v.b.x, v.b.y, v.b.z, v.c.x, v.c.y, v.c.z, colour);
}

void draw(const Path & path)
{
    const bool & isClosed = path.isClosed();
    const auto & vertices = path.getVertices();
    const auto & width = path.getStrokeWidth();
    
    getRenderer()->drawPath(vertices, width, isClosed);
}

void drawBoundingBox(const UIComponent & component, Colour colour)
{
    Rectangle r (component.getOrigin(), component.getSize());

    r.setColour(colour);

    draw(r);
}

void drawCircle(float x, float y, float r, uint16_t segments, Colour colour)
{
    getRenderer()->drawCircle(x, y, 0.0f, r, segments, colour);
}

void drawCircle(float x, float y, float z, float r, uint16_t segments, Colour colour)
{
    getRenderer()->drawCircle(x, y, z, r, segments, colour);
}

void drawCircleStroke(float x, float y, float r, float strokeWidth, uint16_t segments, Colour colour)
{
    drawCircleStroke(x, y, 0.0f, r, strokeWidth, segments, colour);
}

void drawCircleStroke(float x, float y, float z, float r, float strokeWidth, uint16_t segments, Colour colour)
{
    getRenderer()->drawCircleStroke(x, y, z, r, strokeWidth, segments, colour);
}

void drawEllipse(float x, float y, float w, float h, uint16_t segments, Colour colour)
{
    getRenderer()->drawEllipse(x, y, 0.0f, w, h, segments, colour);
}

void drawEllipse(float x, float y, float z, float w, float h, uint16_t segments, Colour colour)
{
    getRenderer()->drawEllipse(x, y, z, w, h, segments, colour);
}

void drawRectangle(float x, float y, float w, float h, Colour colour)
{
    getRenderer()->drawRectangle(x, y, 0.0f, w, h, colour);
}

void drawRectangle(float x, float y, float z, float w, float h, Colour colour)
{
    getRenderer()->drawRectangle(x, y, z, w, h, colour);
}

void drawRectangleStroke(float x, float y, float w, float h, float strokeWidth, Colour colour)
{
    drawRectangleStroke(x, y, 0.0f, w, h, strokeWidth, colour);
}

void drawRectangleStroke(float x, float y, float z, float w, float h, float strokeWidth, Colour colour)
{
    getRenderer()->drawRectangleStroke(x, y, z, w, h, strokeWidth, colour);
}

void drawTriangle(float xa, float ya, float xb, float yb, float xc, float yc, Colour colour)
{
    drawTriangle(xa, ya, 0.0f, xb, yb, 0.0f, xc, yc, 0.0f, colour);
}

void drawTriangle(float xa, float ya, float za, float xb, float yb, float zb, float xc, float yc, float zc, Colour colour)
{
    getRenderer()->drawTriangle(xa, ya, za, xb, yb, zb, xc, yc, zc, colour);
}

}
