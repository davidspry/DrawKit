//  DrawKit
//  Created by David Spry on 13/2/21.

#include "OpenGLRenderer.hpp"

namespace DrawKit {

OpenGLRenderer::OpenGLRenderer()
{
    initialise();
}

OpenGLRenderer::~OpenGLRenderer()
{
    
}

void OpenGLRenderer::destroy()
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
    glDeleteProgram(program);
    glBindVertexArray(0);
    
    DK_LOG("OpenGLRenderer", "Destroyed");
}

// MARK: - RENDER STAGE

void OpenGLRenderer::beginRender()
{
    const int w = getApplicationManager()->getPlatformWindow()->getWidth();
    const int h = getApplicationManager()->getPlatformWindow()->getHeight();
    
    glm::mat4 camera;
    camera = glm::ortho(-0.5f * (float) w,  0.5f * (float) w,
                         0.5f * (float) h, -0.5f * (float) h, -10000.0f, 10000.0f);
//    camera = glm::scale(glm::mat4(1.0f), glm::vec3(0.6f, 0.6f, 1.0f)) * camera;
//    camera = glm::translate(camera, glm::vec3(translate, 0.0f, 0.0f));

//    camera = glm::rotate(camera, glm::radians(35.264f), glm::vec3(1.0f, 0.0f, 0.0f));
//    camera = glm::rotate(camera, glm::radians(45.000f), glm::vec3(0.0f, 0.0f, 1.0f));

    GLuint const location = glGetUniformLocation(program, "view_projection");
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(camera));

    clear();
}

void OpenGLRenderer::complRender()
{
    
}

// MARK: - CLEAR SCREEN

void OpenGLRenderer::clear()
{
    clear(clearColour);
}

void OpenGLRenderer::clear(float k)
{
    clear(k, k, k, 1.0f);
}

void OpenGLRenderer::clear(const Colour & colour)
{
    const RGBA & rgba = colour.getRGBA();
    
    clear(rgba.r, rgba.g, rgba.b, rgba.a);
}

void OpenGLRenderer::clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::setClearColour(const Colour & colour)
{
    clearColour = colour;
}

// MARK: - DRAWING OBJECTS

void OpenGLRenderer::draw(const Square & square)
{
    const auto & size   = square.getSize();
    const auto & origin = square.getOrigin();
    const auto & colour = square.getColour();

    drawRectangle(origin.x, origin.y, origin.z, size.width, size.height, colour);
}

void OpenGLRenderer::draw(const Rectangle & rectangle)
{
    const auto & size   = rectangle.getSize();
    const auto & origin = rectangle.getOrigin();
    const auto & colour = rectangle.getColour();
    
    drawRectangle(origin.x, origin.y, origin.z, size.width, size.height, colour);
}

// MARK: - DRAWING PRIMITIVES

void OpenGLRenderer::drawCircle(float x, float y, float r, uint16_t segments, Colour colour)
{
    drawCircle(x, y, 0, r, segments, colour);
}

void OpenGLRenderer::drawCircle(float x, float y, float z, float r, uint16_t segments, Colour colour)
{
    const int n_Indices  = segments * 3;
    const int n_Vertices = segments * 2 + 1;
    
    vertex_t vertices [n_Vertices];
    uint32_t indices  [n_Indices];

    const UIPoint<float> centre = {
        x - 0.5f * getApplicationManager()->getPlatformWindow()->getWidth(),
        y - 0.5f * getApplicationManager()->getPlatformWindow()->getHeight()
    };
    
    const float theta = 6.2831853072 / segments;
    vertices[0] = { centre.x, centre.y, z, colour.getRGBA() };

    for (size_t k = 0; k < segments; ++k)
    {
        vertices[k * 2 + 1] = { centre.x + r * std::cosf(k * theta),
                                centre.y + r * std::sinf(k * theta), z, colour.getRGBA() };
        vertices[k * 2 + 2] = { centre.x + r * std::cosf((k + 1) * theta),
                                centre.y + r * std::sinf((k + 1) * theta), z, colour.getRGBA() };
    }
    
    indices[0] = static_cast<uint32_t>(0);
    indices[1] = static_cast<uint32_t>(1);
    indices[2] = static_cast<uint32_t>(2);

    for (size_t k = 1; k < segments; ++k)
    {
        indices[k * 3 + 0] = static_cast<uint32_t>(0);
        indices[k * 3 + 1] = static_cast<uint32_t>(k * 2 + 1);
        indices[k * 3 + 2] = static_cast<uint32_t>(k * 2 + 2);
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) (sizeof(float) * 3));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) 0);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glDrawElements(GL_TRIANGLES, n_Indices, GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderer::drawRectangle(float x, float y, float w, float h, Colour colour)
{
    drawRectangle(x, y, 0, w, h, colour);
}

void OpenGLRenderer::drawRectangle(float x, float y, float z, float w, float h, Colour colour)
{
    vertex_t vertices [4];
    uint32_t indices  [6];

    const UIPoint<float> origin = {
        x - 0.5f * getApplicationManager()->getPlatformWindow()->getWidth(),
        y - 0.5f * getApplicationManager()->getPlatformWindow()->getHeight()
    };

    vertices[0] = { origin.x,     origin.y,     z, colour.getRGBA() };
    vertices[1] = { origin.x + w, origin.y,     z, colour.getRGBA() };
    vertices[2] = { origin.x + w, origin.y + h, z, colour.getRGBA() };
    vertices[3] = { origin.x,     origin.y + h, z, colour.getRGBA() };
    
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 0;
    indices[4] = 2;
    indices[5] = 3;

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) (sizeof(float) * 3));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) 0);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderer::drawTriangle(float xa, float ya, float xb, float yb, float xc, float yc, Colour colour)
{
    
}

void OpenGLRenderer::drawTriangle(float xa, float ya, float za,
                                  float xb, float yb, float zb,
                                  float xc, float yc, float zc, Colour colour)
{
    
}

// MARK: - RENDERER INITIALISATION

void OpenGLRenderer::initialise()
{
    DK_ASSERT(gladLoadGL(), "GLAD could not be loaded.");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    const std::string path = "../../DrawKit/src/DrawKit/Renderer/Shaders/";
    const auto shader = Shader::create(path + "Flat.vert", path + "Flat.frag");
    program =  shader->getRendererID();
    glUseProgram(program);
    
    const auto identity = glm::mat4(1.0f);
    const auto location = glGetUniformLocation(program, "transform");
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(identity));
    
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_POLYGON_SMOOTH);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

}
