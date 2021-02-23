//  DrawKit
//  Created by David Spry on 13/2/21.

#ifndef OPENGL_RENDERER_HPP
#define OPENGL_RENDERER_HPP

#include "dk.pch"
#include "Shader.hpp"
#include "Renderer.hpp"
#include "GlobalInterface.hpp"
#include "ModelViewProjectionMatrix.hpp"

namespace DrawKit {

class OpenGLRenderer: public Renderer
{
public:
     OpenGLRenderer();
    ~OpenGLRenderer();
    
// MARK: - INITIALISATION

protected:
    void initialise() override;
    void createDefaultShaders();
    void createDefaultMatrix();

public:
    void destroy() override;
    
// MARK: - RENDER STAGE

public:
    void beginRender() override;
    void complRender() override;

// MARK: - RENDER SETTINGS
    
public:
    void enableSmoothing()  override;
    void disableSmoothing() override;

// MARK: - TRANSFORM

public:
    void popMatrix()  override;
    void pushMatrix() override;

public:
    void scale(float x, float y, float z) override;
    void rotate(float radians, float x, float y, float z) override;
    void translate(float x, float y, float z = 0.0f) override;
    
// MARK: - CLEAR SCREEN

public:
    void clear() override;
    void clear(float k) override;
    void clear(const Colour & colour) override;
    void clear(float r, float g, float b, float a) override;
    void setClearColour(const Colour & colour) override;
    const Colour & getClearColour() override;

// MARK: - DRAWING PATHS

public:
    void drawPath(const std::vector<vertex_colour_t> & vertices, float strokeWidth, bool pathIsClosed) override;
    
// MARK: - DRAWING PRIMITIVES

public:
    void drawCircle(float x, float y, float z, float r, uint16_t segments, const Colour & colour) override;

    void drawCircleStroke(float x, float y, float z, float r, float strokeWidth, uint16_t segments, const Colour & colour) override;
    
    void drawEllipse(float x, float y, float z, float w, float h, uint16_t segments, const Colour & colour) override;
    
    void drawRectangle(float x, float y, float z, float w, float h, const Colour & colour) override;
    
    void drawRectangleStroke(float x, float y, float z, float w, float h, float strokeWidth, const Colour & colour) override;
    
    void drawTriangle(float xa, float ya, float za, float xb, float yb, float zb, float xc, float yc, float zc, const Colour & colour) override;
    
private:
    Shader * flatShader;
    Shader * lineShader;
    uint32_t vao;
    uint32_t vbo;
    uint32_t ibo;
    
private:
    ModelViewProjectionMatrix defaultMatrix;
    std::stack <ModelViewProjectionMatrix> matrices;
};

}

#endif
