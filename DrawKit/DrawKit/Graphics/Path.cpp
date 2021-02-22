//  DrawKit
//  Created by David Spry on 21/2/21.

#include "Path.hpp"

namespace DrawKit {

Path::Path()
{
    strokeWidth  = 5.0f;
    pathIsClosed = false;
}

void Path::clear()
{
    vertices.clear();
}

void Path::close()
{
    pathIsClosed = true;
}

void Path::moveTo(float x, float y)
{
    cursor.x = x;
    cursor.y = y;
}

void Path::lineTo(float x, float y)
{
    if (cursor.x == x && cursor.y == y) return;

    if (vertices.empty())
        vertices.push_back({cursor.x, cursor.y, cursor.z, colour.getRGBA()});

    vertices.push_back({x, y, 0.0f, colour.getRGBA()});

    moveTo(x, y);

    pathIsClosed = false;
}

void Path::setStrokeWidth(float width)
{
    strokeWidth = width;
}

void Path::setColour(const DrawKit::Colour & colour)
{
    this->colour = colour;
}

bool Path::isEmpty() const
{
    return vertices.empty();
}

bool Path::isClosed() const
{
    return pathIsClosed;
}

float Path::getStrokeWidth() const
{
    return strokeWidth;
}

const std::vector<vertex_colour_t> & Path::getVertices() const
{
    return vertices;
}

}
