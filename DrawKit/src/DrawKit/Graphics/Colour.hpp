//  DrawKit
//  Created by David Spry on 3/2/21.

#ifndef COLOUR_HPP
#define COLOUR_HPP

#include "dk.pch"

namespace DrawKit {

struct RGBA
{
    float r;
    float g;
    float b;
    float a;
    
    RGBA(float const red   = 1.0f,
         float const green = 1.0f,
         float const blue  = 1.0f,
         float const alpha = 1.0f)
    {
        r = red;
        g = green;
        b = blue;
        a = alpha;
    }
};

class Colour
{
public:
    Colour() = delete;
    Colour(const Colour & colour, uint8_t alpha);
    Colour(const Colour & A, const Colour & B, float lerpFactor);
    Colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
    
public:
    void mix    (const Colour & colour, float lerpFactor) noexcept;
    void darken (float factor) noexcept;
    void lighten(float factor) noexcept;

public:
    const RGBA & getRGBA() const noexcept;
    
public:
    const static Colour lightBlack;
    const static Colour offwhite;
    const static Colour black;
    const static Colour white;
    const static Colour red;
    const static Colour blue;
    const static Colour pink;
    const static Colour green;
    const static Colour salmon;
    const static Colour yellow;

private:
    RGBA rgba;
};

}

#endif
