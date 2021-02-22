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
    glBindVertexArray(0);
    delete flatShader;

    DK_LOG("OpenGLRenderer", "Destroyed");
}

// MARK: - RENDER STAGE

void OpenGLRenderer::beginRender()
{
    const float W = static_cast<float>(getWindowWidth());
    const float H = static_cast<float>(getWindowHeight());

    ortho = glm::ortho(-0.5f * W, +0.5f * W, +0.5f * H, -0.5f * H, -10000.0f, 10000.0f);
    model = glm::translate(model, transform);

    static float
    degrees = 0.0f;
    degrees = degrees + 2.0f;
    degrees = std::fmod(degrees, 360.0f);
    
//    camera = glm::translate(camera, glm::vec3(0.f, 0.f, 0.0f));
//    camera = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f)) * camera;
//    ortho = glm::rotate(ortho, glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f));

    // ISOMETRIC
//    ortho = glm::rotate(ortho, glm::radians(35.264f), glm::vec3(1.0f, 0.0f, 0.0f));
//    ortho = glm::rotate(ortho, glm::radians(45.000f), glm::vec3(0.0f, 0.0f, 1.0f));
    
    mvpMatrix = ortho * model;
    
    glViewport(0, 0, W, H);
    
    clear();
}

void OpenGLRenderer::complRender()
{
    
}

// MARK: - RENDER SETTINGS

void OpenGLRenderer::enableSmoothing()
{
    glHint  (GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLRenderer::disableSmoothing()
{
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_POLYGON_SMOOTH);
    glDisable(GL_BLEND);
}

// MARK: - TRANSFORM

void OpenGLRenderer::translate(const UIPoint<float> & xyz)
{
    transform.x = xyz.x - 0.5f * getWindowWidth();
    transform.y = xyz.y - 0.5f * getWindowHeight();
    transform.z = xyz.z;

    model = glm::translate(glm::mat4(1.0f), transform);

    mvpMatrix = ortho * model;
}

void OpenGLRenderer::translate(float x, float y, float z)
{
    transform.x = x - 0.5f * getWindowWidth();
    transform.y = y - 0.5f * getWindowHeight();
    transform.z = z;

    model = glm::translate(glm::mat4(1.0f), transform);

    mvpMatrix = ortho * model;
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

// MARK: - DRAWING PATHS

void OpenGLRenderer::drawPath(const std::vector<vertex_colour_t> & vertices, float strokeWidth, bool pathIsClosed)
{
    if (vertices.empty()) return;
    
    auto const VERTICES = vertices.size();
    auto const INDICES  = (VERTICES - static_cast<int>(!pathIsClosed)) * 4;
    int  const LAST     = (VERTICES - 1);

    index_t indices [INDICES];
    
    indices[0] = pathIsClosed ? VERTICES - 1 : 0;
    indices[1] = 0;
    indices[2] = 1;
    indices[3] = std::min(2, LAST);

    if (pathIsClosed)
    {
        indices[INDICES - 4] = VERTICES - 2;
        indices[INDICES - 3] = VERTICES - 1;
        indices[INDICES - 2] = 0;
        indices[INDICES - 1] = 1;
    }

    for (size_t k = 1; k < VERTICES - 1; ++k)
    {
        indices[k * 4 + 0] = k - 1;
        indices[k * 4 + 1] = k - 0;
        indices[k * 4 + 2] = k + 1;
        indices[k * 4 + 3] = (k + 2) % VERTICES;
    }

    const float W = static_cast<float>(getWindowWidth());
    const float H = static_cast<float>(getWindowHeight());

    lineShader->use();
    lineShader->setUniform("MiterLimit",  0.75f);
    lineShader->setUniform("Thickness",   strokeWidth);
    lineShader->setUniform("Viewport",    glm::vec2(W, H));
    lineShader->setUniform("ModelViewProjection", mvpMatrix);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_colour_t) * VERTICES, vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_colour_t), (void *) 0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_colour_t), (void *) sizeof(vertex_t));
    glEnableVertexAttribArray(1);

    glDrawElements(GL_LINES_ADJACENCY, INDICES, GL_UNSIGNED_INT, nullptr);
}

// MARK: - DRAWING PRIMITIVES

void OpenGLRenderer::drawCircle(float x, float y, float r, uint16_t segments, const Colour & colour)
{
    drawCircle(x, y, 0.0f, r, segments, colour);
}

void OpenGLRenderer::drawCircle(float x, float y, float z, float r, uint16_t segments, const Colour & colour)
{
    const int INDICES  = segments * 3;
    const int VERTICES = segments + 2;

    index_t  index = 0;
    index_t  indices  [INDICES ];
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
    vertices[0] = { centre.x, centre.y, z };

    for (size_t k = 1; k < VERTICES; ++k)
    {
        vertices[k] = {
            centre.x + point.x,
            centre.y + point.y,
            centre.z + point.z,
        };
        
        const float t = point.x;
        point.x = cos * point.x - sin * point.y;
        point.y = cos * point.y + sin * t;
    }

    flatShader->use();
    flatShader->setUniform("ModelViewProjection", mvpMatrix);
    flatShader->setUniform("Colour", colour.getRGBA());
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) 0);
    glEnableVertexAttribArray(0);
    
    glDrawElements(GL_TRIANGLES, INDICES, GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderer::drawEllipse(float x, float y, float w, float h, uint16_t segments, const Colour & colour)
{
    drawEllipse(x, y, 0.0f, w, h, segments, colour);
}

void OpenGLRenderer::drawEllipse(float x, float y, float z, float w, float h, uint16_t segments, const Colour & colour)
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
    vertices[0] = { x, y, z };

    for (size_t k = 1; k < VERTICES; ++k)
    {
        vertices[k] = {
            x + w * std::cosf(k * theta),
            y + h * std::sinf(k * theta),
            z
        };
    }

    flatShader->use();
    flatShader->setUniform("ModelViewProjection", mvpMatrix);
    flatShader->setUniform("Colour", colour.getRGBA());

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) 0);
    glEnableVertexAttribArray(0);
    
    glDrawElements(GL_TRIANGLES, INDICES, GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderer::drawRectangle(float x, float y, float w, float h, const Colour & colour)
{
    drawRectangle(x, y, 0.0f, w, h, colour);
}

void OpenGLRenderer::drawRectangle(float x, float y, float z, float w, float h, const Colour & colour)
{
    const UIPoint<float> origin = { x, y };

    const std::array<vertex_t, 4> vertices = {{
        { origin.x,     origin.y,     z },
        { origin.x + w, origin.y,     z },
        { origin.x + w, origin.y + h, z },
        { origin.x,     origin.y + h, z }
    }};

    constexpr static std::array<uint32_t, 6> indices = {0, 1, 2, 0, 2, 3};

    flatShader->use();
    flatShader->setUniform("ModelViewProjection", mvpMatrix);
    flatShader->setUniform("Colour", colour.getRGBA());

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) 0);
    glEnableVertexAttribArray(0);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderer::drawRectangleStroke(float x, float y, float w, float h, float strokeWidth, const Colour & colour)
{
    const UIPoint<float> origin = { x, y };
    const float W = static_cast<float>(getWindowWidth());
    const float H = static_cast<float>(getWindowHeight());

    const std::array<vertex_colour_t, 4> vertices = {{
        { origin.x,     origin.y,     0.0f, colour.getRGBA() },
        { origin.x + w, origin.y,     0.0f, colour.getRGBA() },
        { origin.x + w, origin.y + h, 0.0f, colour.getRGBA() },
        { origin.x,     origin.y + h, 0.0f, colour.getRGBA() }
    }};
    
    constexpr std::array<index_t, 16> indices = {
        3, 0, 1, 2,
        0, 1, 2, 3,
        1, 2, 3, 0,
        2, 3, 0, 1
    };

    lineShader->use();
    lineShader->setUniform("MiterLimit",  0.75f);
    lineShader->setUniform("Thickness",   strokeWidth);
    lineShader->setUniform("Viewport",    glm::vec2(W, H));
    lineShader->setUniform("ModelViewProjection", mvpMatrix);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_colour_t), (void *) 0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_colour_t), (void *) sizeof(vertex_t));
    glEnableVertexAttribArray(1);
    
    glDrawElements(GL_LINES_ADJACENCY, indices.size(), GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderer::drawTriangle(float xa, float ya, float xb, float yb, float xc, float yc, const Colour & colour)
{
    drawTriangle(xa, ya, 0.0f, xb, yb, 0.0f, xc, yc, 0.0f, colour);
}

void OpenGLRenderer::drawTriangle(float xa, float ya, float za,
                                  float xb, float yb, float zb,
                                  float xc, float yc, float zc, const Colour & colour)
{
    const std::array<vertex_t, 3> vertices = {{
        { xa, ya, za },
        { xb, yb, zb },
        { xc, yc, zc }
    }};

    flatShader->use();
    flatShader->setUniform("ModelViewProjection", mvpMatrix);
    flatShader->setUniform("Colour", colour.getRGBA());

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) 0);
    glEnableVertexAttribArray(0);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

// MARK: - RENDERER INITIALISATION

void OpenGLRenderer::initialise()
{
    DK_ASSERT(gladLoadGL(), "GLAD could not be loaded.");

    createDefaultShaders();
    createDefaultTransform();

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    glEnable(GL_MULTISAMPLE);
}

void OpenGLRenderer::createDefaultShaders()
{
    flatShader = Shader::create("Flat.vert", "Flat.frag");
    lineShader = Shader::create("Line.vert", "Line.frag", "Line.geom");
}

void OpenGLRenderer::createDefaultTransform()
{
    const float W = static_cast<float>(getWindowWidth());
    const float H = static_cast<float>(getWindowHeight());

    ortho = glm::ortho(-0.5f * W, +0.5f * W, +0.5f * H, -0.5f * H, -10000.0f, 10000.0f);
    model = glm::translate(glm::mat4(1.0f), transform);
    transform = glm::vec3(-0.5f * W, -0.5f * H, 0.0f);
    mvpMatrix = ortho * model;
}

}
