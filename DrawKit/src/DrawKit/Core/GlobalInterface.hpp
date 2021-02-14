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

void setBackgroundColour(uint8_t k);

void setBackgroundColour(const Colour & colour);

void setBackgroundColour(const Colour && colour);

void setBackgroundColour(uint8_t r, uint8_t g, uint8_t b);

// MARK: - DRAWING INTERFACE

void drawCircle(const Circle & circle);

void drawCircle(float x, float y, float r, uint16_t segments, Colour colour);

void drawCircle(float x, float y, float z, float r, uint16_t segments, Colour colour);

void drawRectangle(const Rectangle & rectangle);

void drawRectangle(float x, float y, float w, float h, Colour colour);

void drawRectangle(float x, float y, float z, float w, float h, Colour colour);

}

#endif
