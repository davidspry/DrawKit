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

// MARK: - RENDERER INITIALISATION

void OpenGLRenderer::initialise()
{
    DK_ASSERT(gladLoadGL(), "GLAD could not be loaded.");

    createDefaultShaders();
    createDefaultMatrix();

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

void OpenGLRenderer::createDefaultMatrix()
{
    const float W = static_cast<float>(getWindowWidth());
    const float H = static_cast<float>(getWindowHeight());

    windowSize.w = W;
    windowSize.h = H;

    glm::mat4 const ortho = glm::ortho(-0.5f * W, 0.5f * W, 0.5f * H, -0.5f * H, -10000.0f, 10000.0f);

    defaultMatrix.setProjectionMatrix(ortho);
    defaultMatrix.setTranslation(-0.5f * W, -0.5f * H, 0.0f);
}

void OpenGLRenderer::destroy()
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
    glBindVertexArray(0);

    delete flatShader;
    delete lineShader;

    DK_LOG("OpenGLRenderer", "Destructed");
}

// MARK: - RENDER STAGE

void OpenGLRenderer::beginRender()
{
    const float W = static_cast<float>(getWindowWidth());
    const float H = static_cast<float>(getWindowHeight());

    if (!(windowSize.w == W && windowSize.h == H))
    {
        glm::mat4 const ortho =
            glm::ortho(-0.5f * W, 0.5f * W, 0.5f * H, -0.5f * H, -10000.0f, 10000.0f);

        defaultMatrix.setProjectionMatrix(ortho);
        defaultMatrix.setTranslation(-0.5f * W, -0.5f * H, 0.0f);
        
        windowSize.w = W;
        windowSize.h = H;
    }

    matrices.emplace(defaultMatrix);
    
    glViewport(0, 0, W, H);

    clear();
}

void OpenGLRenderer::complRender()
{
    matrices.pop();
}

// MARK: - RENDER SETTINGS

void OpenGLRenderer::enableSmoothing()
{
    glBlendFunc    (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    glHint  (GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_BLEND);
}

void OpenGLRenderer::disableSmoothing()
{
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_POLYGON_SMOOTH);
    glDisable(GL_BLEND);
}

// MARK: - TRANSFORM

void OpenGLRenderer::pushMatrix()
{
    const auto & matrix = matrices.top();

    matrices.emplace(matrix);
}

void OpenGLRenderer::pushMatrix(const ModelViewProjectionMatrix & matrix)
{
    matrices.push(matrix);
}

void OpenGLRenderer::popMatrix()
{
    matrices.pop();
}

void OpenGLRenderer::scale(float x, float y, float z)
{
    matrices.top().scale(x, y, z);
}

void OpenGLRenderer::rotate(float radians, float x, float y, float z)
{
    matrices.top().rotateModel(radians, x, y, z);
}

void OpenGLRenderer::translate(float x, float y, float z)
{
    matrices.top().translate(x, y, z);
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
    
    auto const VERTICES = static_cast<index_t>(vertices.size());
    auto const INDICES  = (VERTICES - static_cast<int>(!pathIsClosed)) * 4;
    auto const LAST     = (VERTICES - 1);

    index_t indices [INDICES];
    
    indices[0] = pathIsClosed ? VERTICES - 1 : 0;
    indices[1] = 0;
    indices[2] = 1;
    indices[3] = std::min(2, (int) LAST);

    if (pathIsClosed)
    {
        indices[INDICES - 4] = VERTICES - 2;
        indices[INDICES - 3] = VERTICES - 1;
        indices[INDICES - 2] = 0;
        indices[INDICES - 1] = 1;
    }

    for (size_t k = 1; k < VERTICES - 1; ++k)
    {
        indices[k * 4 + 0] = static_cast<index_t>(k - 1);
        indices[k * 4 + 1] = static_cast<index_t>(k - 0);
        indices[k * 4 + 2] = static_cast<index_t>(k + 1);
        indices[k * 4 + 3] = static_cast<index_t>((k + 2) % VERTICES);
    }

    const float W = static_cast<float>(getWindowWidth());
    const float H = static_cast<float>(getWindowHeight());

    lineShader->use();
    lineShader->setUniform("MiterLimit",  0.75f);
    lineShader->setUniform("Thickness",   strokeWidth);
    lineShader->setUniform("Viewport",    glm::vec2(W, H));
    lineShader->setUniform("ModelViewProjection", matrices.top().getMVPMatrix());

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
    flatShader->setUniform("ModelViewProjection", matrices.top().getMVPMatrix());
    flatShader->setUniform("Colour", colour.getRGBA());
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) 0);
    glEnableVertexAttribArray(0);
    
    glDrawElements(GL_TRIANGLES, INDICES, GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderer::drawCircleStroke(float x, float y, float z, float r, float strokeWidth, uint16_t segments, const Colour & colour)
{
    index_t indices [segments * 4];
    vertex_colour_t vertices [segments];
    
    const float W = static_cast<float>(getWindowWidth());
    const float H = static_cast<float>(getWindowHeight());

    UIPoint<float> point = { r, 0.0f, z };

    const float theta = TWO_PI / static_cast<float>(segments);
    const float cos = std::cosf(theta);
    const float sin = std::sinf(theta);

    for (size_t k = 0; k < segments; ++k)
    {
        vertices[k] = {
            x + point.x,
            y + point.y,
            z + point.z,
            colour.getRGBA()
        };
        
        const float t = point.x;
        point.x = cos * point.x - sin * point.y;
        point.y = cos * point.y + sin * t;
    }
    
    for (size_t k = 0; k < segments; ++k)
    {
        indices[k * 4 + 0] = (segments + k - 1) % segments;
        indices[k * 4 + 1] = (segments + k - 0) % segments;
        indices[k * 4 + 2] = (segments + k + 1) % segments;
        indices[k * 4 + 3] = (segments + k + 2) % segments;
    }

    lineShader->use();
    lineShader->setUniform("MiterLimit",  0.75f);
    lineShader->setUniform("Thickness",   strokeWidth);
    lineShader->setUniform("Viewport",    glm::vec2(W, H));
    lineShader->setUniform("ModelViewProjection", matrices.top().getMVPMatrix());

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_colour_t), (void *) 0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_colour_t), (void *) sizeof(vertex_t));
    glEnableVertexAttribArray(1);
    
    glDrawElements(GL_LINES_ADJACENCY, segments * 4, GL_UNSIGNED_INT, nullptr);
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
    flatShader->setUniform("ModelViewProjection", matrices.top().getMVPMatrix());
    flatShader->setUniform("Colour", colour.getRGBA());

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) 0);
    glEnableVertexAttribArray(0);
    
    glDrawElements(GL_TRIANGLES, INDICES, GL_UNSIGNED_INT, nullptr);
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
    flatShader->setUniform("ModelViewProjection", matrices.top().getMVPMatrix());
    flatShader->setUniform("Colour", colour.getRGBA());

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) 0);
    glEnableVertexAttribArray(0);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderer::drawRectangleStroke(float x, float y, float z, float w, float h, float strokeWidth, const Colour & colour)
{
    const UIPoint<float> origin = { x, y, z };
    const float W = static_cast<float>(getWindowWidth());
    const float H = static_cast<float>(getWindowHeight());

    const std::array<vertex_colour_t, 4> vertices = {{
        { origin.x,     origin.y,     origin.z, colour.getRGBA() },
        { origin.x + w, origin.y,     origin.z, colour.getRGBA() },
        { origin.x + w, origin.y + h, origin.z, colour.getRGBA() },
        { origin.x,     origin.y + h, origin.z, colour.getRGBA() }
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
    lineShader->setUniform("ModelViewProjection", matrices.top().getMVPMatrix());

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
    flatShader->setUniform("ModelViewProjection", matrices.top().getMVPMatrix());
    flatShader->setUniform("Colour", colour.getRGBA());

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *) 0);
    glEnableVertexAttribArray(0);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

}
