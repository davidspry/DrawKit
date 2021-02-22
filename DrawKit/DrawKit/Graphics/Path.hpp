//  DrawKit
//  Created by David Spry on 21/2/21.

#ifndef PATH_HPP
#define PATH_HPP

#include "dk.pch"

namespace DrawKit {

class Path
{
public:
    Path();
    
public:
    void clear();
    void close();
    void moveTo(float x, float y);
    void lineTo(float x, float y);
    
public:
    void setStrokeWidth(float width);
    void setColour(const DrawKit::Colour & colour);

public:
    bool isEmpty() const;
    bool isClosed() const;

public:
    float getStrokeWidth() const;
    const std::vector<vertex_colour_t> & getVertices() const;
    
private:
    UIPoint <float> cursor;
    DrawKit::Colour colour;

private:
    float strokeWidth;
    bool  pathIsClosed;

private:
    std::vector<vertex_colour_t> vertices;
};

}

#endif
