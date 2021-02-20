//  DrawKit
//  Created by David Spry on 20/2/21.

#include "Triangle.hpp"

namespace DrawKit {

Triangle::Triangle(const int32_t x, const int32_t y, const int32_t width, const int32_t height):
UIComponent(x, y, 0, width, height)
{
    vertices.a.x = static_cast<float>(centre.x) - static_cast<float>(width)  * 0.5f;
    vertices.a.y = static_cast<float>(centre.y) + static_cast<float>(height) * 0.5f;
    vertices.a.z = 0.0f;

    vertices.b.x = static_cast<float>(centre.x);
    vertices.b.y = static_cast<float>(centre.y) - static_cast<float>(height) * 0.5f;
    vertices.b.z = 0.0f;

    vertices.c.x = static_cast<float>(centre.x) + static_cast<float>(width)  * 0.5f;
    vertices.c.y = static_cast<float>(centre.y) + static_cast<float>(height) * 0.5f;
    vertices.c.z = 0.0f;
}

Triangle::Triangle(const Vertices & vertices): UIComponent(), vertices(vertices)
{
    Rectangle const r = Triangle::computeBoundingBox(vertices);    
    setPositionWithCentre(r.getCentre());
    setSizeFromCentre(r.getSize());
}

Rectangle Triangle::computeBoundingBox(const Triangle::Vertices & vertices)
{
    Rectangle r;

    const auto x = std::minmax({vertices.a.x, vertices.b.x, vertices.c.x});
    const auto y = std::minmax({vertices.a.y, vertices.b.y, vertices.c.y});
    const auto z = std::minmax({vertices.a.z, vertices.b.z, vertices.c.z});
    
    r.setSizeFromCentre(x.second - x.first, y.second - y.first);
    r.setPositionWithCentre(static_cast<int32_t>(midpoint(x.first, x.second)),
                            static_cast<int32_t>(midpoint(y.first, y.second)),
                            static_cast<int32_t>(midpoint(z.first, z.second)));

    return r;
}

const Triangle::Vertices & Triangle::getVertices() const
{
    return vertices;
}
    
void Triangle::setVertices(const UIPoint<float> & a, const UIPoint<float> & b, const UIPoint<float> & c)
{
    vertices.a = a;
    vertices.b = b;
    vertices.c = c;
    
    Rectangle const r = Triangle::computeBoundingBox(vertices);
    UIComponent::setPositionWithCentre(r.getCentre());
    UIComponent::setSizeFromCentre(r.getSize());
}

void Triangle::setSizeFromOrigin(int32_t width, int32_t height)
{
    UISize<float> const delta = {
        static_cast<float>((int32_t) getSize().w - width ),
        static_cast<float>((int32_t) getSize().h - height)
    };

    for (auto & vertex : { & vertices.a, & vertices.b, & vertices.c })
    {
        vertex->x = vertex->x - (vertex->x - origin.x) / static_cast<float>(size.w) * delta.w;
        vertex->y = vertex->y - (vertex->y - origin.y) / static_cast<float>(size.h) * delta.h;
    }

    UIComponent::setSizeFromOrigin(width, height);
}

void Triangle::setSizeFromOrigin(const UISize<uint32_t> & size)
{
    setSizeFromCentre(size.w, size.h);
}

void Triangle::setSizeFromCentre(int32_t width, int32_t height)
{
    UISize<float> const delta = {
        static_cast<float>((int) getSize().w - (int) width ) * 0.5f,
        static_cast<float>((int) getSize().h - (int) height) * 0.5f
    };
    
    const UISize<float> half = {
        std::fmax(5e-5f, size.w * 0.5f),
        std::fmax(5e-5f, size.h * 0.5f)
    };

    for (auto & vertex : { & vertices.a, & vertices.b, & vertices.c })
    {
        vertex->x = vertex->x - (vertex->x - centre.x) / half.w * delta.w;
        vertex->y = vertex->y - (vertex->y - centre.y) / half.h * delta.h;
    }
    
    UIComponent::setSizeFromCentre(width, height);
}

void Triangle::setSizeFromCentre(const UISize<uint32_t> & size)
{
    setSizeFromCentre(size.w, size.h);
}

void Triangle::setPositionWithOrigin(int32_t x, int32_t y, int32_t z)
{
    UIPoint<int32_t> const delta = {
        static_cast<int32_t>(origin.x) - x,
        static_cast<int32_t>(origin.y) - y,
        static_cast<int32_t>(origin.z) - z
    };
    
    for (auto & vertex : { & vertices.a, & vertices.b, & vertices.c })
    {
        vertex->x = vertex->x + delta.x;
        vertex->y = vertex->y + delta.y;
        vertex->z = vertex->z + delta.z;
    }
    
    UIComponent::setPositionWithOrigin(x, y, z);
}

void Triangle::setPositionWithOrigin(const UIPoint<int32_t> & xyz)
{
    setPositionWithOrigin(xyz.x, xyz.y, xyz.z);
}

void Triangle::setPositionWithCentre(int32_t x, int32_t y, int32_t z)
{
    UIPoint<int32_t> const delta = {
        x - static_cast<int32_t>(centre.x),
        y - static_cast<int32_t>(centre.y),
        z - static_cast<int32_t>(centre.z)
    };
    
    for (auto & vertex : { & vertices.a, & vertices.b, & vertices.c })
    {
        vertex->x = vertex->x + delta.x;
        vertex->y = vertex->y + delta.y;
        vertex->z = vertex->z + delta.z;
    }
    
    UIComponent::setPositionWithCentre(x, y, z);
}

void Triangle::setPositionWithCentre(const UIPoint<int32_t> & xyz)
{
    setPositionWithCentre(xyz.x, xyz.y, xyz.z);
}

}
