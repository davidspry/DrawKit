//  DrawKit
//  Created by David Spry on 14/2/21.

#ifndef GLOBAL_INTERFACE_HPP
#define GLOBAL_INTERFACE_HPP

#include "dk.pch"
#include "Path.hpp"
#include "Window.h"
#include "Renderer.hpp"
#include "UIPrimitives.h"
#include "Application.hpp"
#include "ApplicationManager.hpp"

namespace DrawKit {

class ApplicationManager;

Renderer * const getRenderer();

ApplicationManager * const getApplicationManager();

// MARK: - APPLICATION INTERFACE

/// @brief Launch the given application.
/// @param application The application to be run.
/// @param attributes The application's window attributes.
/// @param renderer The desired renderer.

void launch(Application* application, const Window::Attributes& attributes, RendererType && renderer);

/// @brief Set the position of the window.
/// @param x The x component of the desired window position.
/// @param y The y component of the desired window position.
/// @note This must be called prior to launching an application.

void setWindowPosition(int x, int y);

// MARK: - RENDERING INTERFACE

void enableSmoothing();

void disableSmoothing();

void scale(float scaleFactor);

void scale(glm::vec3 scaleFactor);

void rotateByRadians(float radians, Axis axis);

void rotateByRadians(float radians, float x, float y, float z);

void rotateByDegrees(float degrees, Axis axis);

void rotateByDegrees(float degrees, float x, float y, float z);

void translate(float x, float y, float z = 0.0f);

void translate(const UIPoint<float> & xyz);

void pushMatrix();

void popMatrix();

void setFrameRate(uint16_t frameRate);

void setBackgroundColour(uint8_t k);

void setBackgroundColour(const Colour & colour);

void setBackgroundColour(const Colour && colour);

void setBackgroundColour(uint8_t r, uint8_t g, uint8_t b);

const Colour & getBackgroundColour();

// MARK: - WINDOW INTERFACE

UISize<uint32_t> getWindowSize();

uint32_t getWindowWidth();

uint32_t getWindowHeight();

// MARK: - DRAWING INTERFACE

/// @brief Draw the given circle.
/// @param circle The circle to be drawn.

void draw(const Circle & circle);

/// @brief Draw the given rectangle.
/// @param rectangle The rectangle to be drawn.

void draw(const Rectangle & rectangle);

/// @brief Draw the given triangle.
/// @param triangle The triangle to be drawn.

void draw(const Triangle & triangle);

/// @brief Draw the given path.
/// @param path The path to be drawn.

void draw(const Path & path);

/// @brief Draw the given UIComponent's bounding box.
/// @param component The component whose bounding box should be drawn.
/// @param colour The colour to fill the bounding box with.

void drawBoundingBox(const UIComponent & component, Colour colour = Colour::white);

void drawCircle(float x, float y, float r, uint16_t segments, Colour colour = Colour::white);

void drawCircle(float x, float y, float z, float r, uint16_t segments, Colour colour = Colour::white);

void drawCircleStroke(float x, float y, float r, float strokeWidth, uint16_t segments, Colour colour = Colour::white);

void drawCircleStroke(float x, float y, float z, float r, float strokeWidth, uint16_t segments, Colour colour = Colour::white);

void drawEllipse(float x, float y, float w, float h, uint16_t segments, Colour colour = Colour::white);

void drawEllipse(float x, float y, float z, float w, float h, uint16_t segments, Colour colour = Colour::white);

void drawRectangle(float x, float y, float w, float h, Colour colour = Colour::white);

void drawRectangle(float x, float y, float z, float w, float h, Colour colour = Colour::white);

void drawRectangleStroke(float x, float y, float w, float h, float strokeWidth, Colour colour = Colour::white);

void drawRectangleStroke(float x, float y, float z, float w, float h, float strokeWidth, Colour colour = Colour::white);

void drawTriangle(float xa, float ya, float xb, float yb, float xc, float yc, Colour colour = Colour::white);

void drawTriangle(float xa, float ya, float za, float xb, float yb, float zb, float xc, float yc, float zc, Colour colour = Colour::white);

}

#endif
