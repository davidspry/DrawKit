//  DrawKit
//  Created by David Spry on 13/2/21.

#ifndef OPENGL_RENDERER_HPP
#define OPENGL_RENDERER_HPP

#include "dk.pch"
#include "Shader.hpp"
#include "Renderer.hpp"
#include "UIPrimitives.h"
#include "GlobalInterface.hpp"

namespace DrawKit {

class OpenGLRenderer: public Renderer
{
public:
     OpenGLRenderer();
    ~OpenGLRenderer();
    
public:
    void destroy() override;
    
// MARK: - RENDER STAGE

public:
    void beginRender() override;
    void complRender() override;

// MARK: - CLEAR SCREEN

public:
    void clear() override;
    void clear(float k) override;
    void clear(const Colour & colour) override;
    void clear(float r, float g, float b, float a) override;
    void setClearColour(const Colour & colour) override;
    const Colour & getClearColour() override;

// MARK: - DRAWING PRIMITIVES

public:
    void drawCircle(float x, float y, float r, uint16_t segments, Colour colour) override;
    void drawCircle(float x, float y, float z, float r, uint16_t segments, Colour colour) override;
    
    void drawEllipse(float x, float y, float w, float h, uint16_t segments, Colour colour) override;
    void drawEllipse(float x, float y, float z, float w, float h, uint16_t segments, Colour colour) override;
    
    void drawRectangle(float x, float y, float w, float h, Colour colour) override;
    void drawRectangle(float x, float y, float z, float w, float h, Colour colour) override;
    
    void drawRectangleStroke(float x, float y, float w, float h, Colour colour) override;
    
    void drawTriangle(float xa, float ya, float xb, float yb, float xc, float yc, Colour colour) override;
    void drawTriangle(float xa, float ya, float za,
                      float xb, float yb, float zb,
                      float xc, float yc, float zc, Colour colour) override;

// MARK: - INITIALISATION

protected:
    void initialise() override;
    
private:
    uint32_t program;
    uint32_t vao;
    uint32_t vbo;
    uint32_t ibo;
};

}

#endif
