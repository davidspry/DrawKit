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
    const float w = static_cast<float>(getApplicationManager()->getPlatformWindow()->getWidth());
    const float h = static_cast<float>(getApplicationManager()->getPlatformWindow()->getHeight());
    
    glm::mat4 model     (1.0f);
    glm::mat4 camera    (1.0f);
    glm::mat4 transform (1.0f);

    camera = glm::ortho(-0.5f * w, +0.5f * w, +0.5f * h, -0.5f * h, -10000.0f, 10000.0f);
    model  = glm::translate(model, glm::vec3 (-0.5f * w, -0.5f * h, 0.0f));
    
    static float degrees = 0.0f;
    degrees = degrees + 1.0f;
    degrees = std::fmod(degrees, 360.0f);
    
//    camera = glm::translate(camera, glm::vec3(0.f, 0.f, 0.0f));
//    camera = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f)) * camera;
    camera = glm::rotate(camera, glm::radians(degrees), glm::vec3(1.0f, 0.0f, 0.0f));

//    camera = glm::rotate(camera, glm::radians(35.264f), glm::vec3(1.0f, 0.0f, 0.0f));
//    camera = glm::rotate(camera, glm::radians(45.000f), glm::vec3(0.0f, 0.0f, 1.0f));

    
    glUniformMatrix4fv(glGetUniformLocation(program, "view_projection"), 1, GL_FALSE, glm::value_ptr(camera));
    glUniformMatrix4fv(glGetUniformLocation(program, "model"),           1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(program, "transform"),       1, GL_FALSE, glm::value_ptr(transform));
    
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

const Colour & OpenGLRenderer::getClearColour()
{
    return clearColour;
}

// MARK: - DRAWING PRIMITIVES

void OpenGLRenderer::drawCircle(float x, float y, float r, uint16_t segments, Colour colour)
{
    drawCircle(x, y, 0.0f, r, segments, colour);
}

void OpenGLRenderer::drawCircle(float x, float y, float z, float r, uint16_t segments, Colour colour)
{
    const int INDICES  = segments * 3;
    const int VERTICES = segments + 2;

    uint32_t index = 0;
    uint32_t indices  [INDICES ];
    vertex_t vertices [VERTICES];
    
    for (size_t k = 0; k < INDICES; ++k)
    {
        index      = index - static_cast<uint32_t>(k % 3 == 0 && k > 0);
        index      = index + static_cast<uint32_t>(k % 3 != 0);
        indices[k] = index * static_cast<uint32_t>(k % 3 != 0);
    }

    const float theta = TWO_PI / static_cast<float>(segments);
    const float cos = std::cosf(theta);
    const float sin = std::sinf(theta);

    UIPoint<float> point = { r, 0.00f, z };
    UIPoint<float> const centre = { x, y };
    vertices[0] = { centre.x, centre.y, z, colour.getRGBA() };

    for (size_t k = 1; k < VERTICES; ++k)
    {
        vertices[k] = {
            centre.x + point.x,
            centre.y + point.y,
            centre.z + point.z,
            colour.getRGBA()
        };
        
        const float t = point.x;
        point.x = cos * point.x - sin * point.y;
        point.y = cos * point.y + sin * t;
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) (sizeof(float) * 3));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) 0);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glDrawElements(GL_TRIANGLES, INDICES, GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderer::drawEllipse(float x, float y, float w, float h, uint16_t segments, Colour colour)
{
    drawEllipse(x, y, 0.0f, w, h, segments, colour);
}

void OpenGLRenderer::drawEllipse(float x, float y, float z, float w, float h, uint16_t segments, Colour colour)
{
    const int INDICES  = segments * 3;
    const int VERTICES = segments + 2;

    uint32_t index = 0;
    uint32_t indices  [INDICES ];
    vertex_t vertices [VERTICES];
    
    for (size_t k = 0; k < INDICES; ++k)
    {
        index      = index - static_cast<uint32_t>(k % 3 == 0 && k > 0);
        index      = index + static_cast<uint32_t>(k % 3 != 0);
        indices[k] = index * static_cast<uint32_t>(k % 3 != 0);
    }

    const float theta = TWO_PI / static_cast<float>(segments);
    vertices[0] = { x, y, z, colour.getRGBA() };

    for (size_t k = 1; k < VERTICES; ++k)
    {
        vertices[k] = {
            x + w * std::cosf(k * theta),
            y + h * std::sinf(k * theta),
            z,  colour.getRGBA()
        };
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) (sizeof(float) * 3));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) 0);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glDrawElements(GL_TRIANGLES, INDICES, GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderer::drawRectangle(float x, float y, float w, float h, Colour colour)
{
    drawRectangle(x, y, 0.0f, w, h, colour);
}

void OpenGLRenderer::drawRectangle(float x, float y, float z, float w, float h, Colour colour)
{
    const UIPoint<float> origin = { x, y };

    const std::array<vertex_t, 4> vertices = {{
        { origin.x,     origin.y,     z, colour.getRGBA() },
        { origin.x + w, origin.y,     z, colour.getRGBA() },
        { origin.x + w, origin.y + h, z, colour.getRGBA() },
        { origin.x,     origin.y + h, z, colour.getRGBA() }
    }};

    constexpr static std::array<uint32_t, 6> indices = {0, 1, 2, 0, 2, 3};

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) (sizeof(float) * 3));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) 0);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderer::drawRectangleStroke(float x, float y, float w, float h, Colour colour)
{
    const UIPoint<float> origin = { x, y };

    const std::array<vertex_t, 4> vertices = {{
        { origin.x,     origin.y,     0.0f, colour.getRGBA() },
        { origin.x + w, origin.y,     0.0f, colour.getRGBA() },
        { origin.x + w, origin.y + h, 0.0f, colour.getRGBA() },
        { origin.x,     origin.y + h, 0.0f, colour.getRGBA() }
    }};

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) (sizeof(float) * 3));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) 0);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glDrawArrays(GL_LINES, 0, 4);
}

void OpenGLRenderer::drawTriangle(float xa, float ya, float xb, float yb, float xc, float yc, Colour colour)
{
    drawTriangle(xa, ya, 0.0f, xb, yb, 0.0f, xc, yc, 0.0f, colour);
}

void OpenGLRenderer::drawTriangle(float xa, float ya, float za,
                                  float xb, float yb, float zb,
                                  float xc, float yc, float zc, Colour colour)
{
    const std::array<vertex_t, 3> vertices = {{
        { xa, ya, za, colour.getRGBA() },
        { xb, yb, zb, colour.getRGBA() },
        { xc, yc, zc, colour.getRGBA() }
    }};

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) (sizeof(float) * 3));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) 0);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

// MARK: - RENDERER INITIALISATION

void OpenGLRenderer::initialise()
{
    DK_ASSERT(gladLoadGL(), "GLAD could not be loaded.");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    const std::string path = "../../../../DrawKit/DrawKit/Renderer/Shaders/";
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
