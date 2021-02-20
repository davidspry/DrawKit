//  DrawKit
//  Created by David Spry on 14/2/21.

#ifndef GLOBAL_INTERFACE_HPP
#define GLOBAL_INTERFACE_HPP

#include "dk.pch"
#include "Window.h"
#include "Renderer.hpp"
#include "Application.hpp"
#include "ApplicationManager.hpp"

namespace DrawKit {

class ApplicationManager;

Renderer * const getRenderer();

ApplicationManager * const getApplicationManager();

// MARK: - APPLICATION INTERFACE

void launch(Application* application, const Window::Attributes& attributes, RendererType && renderer);

// MARK: - RENDERING INTERFACE

void enableSmoothing();

void disableSmoothing();

void setFrameRate(uint16_t frameRate);

void setBackgroundColour(uint8_t k);

void setBackgroundColour(const Colour & colour);

void setBackgroundColour(const Colour && colour);

void setBackgroundColour(uint8_t r, uint8_t g, uint8_t b);

const Colour & getBackgroundColour();

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

/// @brief Draw the given UIComponent's bounding box.
/// @param component The component whose bounding box should be drawn.
/// @param colour The colour to fill the bounding box with.

void drawBoundingBox(const UIComponent & component, Colour colour = Colour::white);

void drawCircle(float x, float y, float r, uint16_t segments, Colour colour);

void drawCircle(float x, float y, float z, float r, uint16_t segments, Colour colour);

void drawEllipse(float x, float y, float w, float h, uint16_t segments, Colour colour);

void drawEllipse(float x, float y, float z, float w, float h, uint16_t segments, Colour colour);

void drawRectangle(float x, float y, float w, float h, Colour colour);

void drawRectangle(float x, float y, float z, float w, float h, Colour colour);

void drawRectangleStroke(float x, float y, float w, float h, Colour colour);

void drawTriangle(float xa, float ya, float xb, float yb, float xc, float yc, Colour colour);

void drawTriangle(float xa, float ya, float za, float xb, float yb, float zb, float xc, float yc, float zc, Colour colour);

}

#endif
