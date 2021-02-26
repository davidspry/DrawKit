//  DrawKit
//  Created by David Spry on 3/2/21.

#ifndef COLOUR_HPP
#define COLOUR_HPP

#include "dk.pch"

namespace DrawKit {

/// @brief The RGBA components that underly a Colour object.
/// Each component has a value in the range [0.0, 1.0].

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

/// @brief An colour represented by four components, RGBA.

class Colour
{
public:
    Colour() = default;
    Colour(const RGBA & rgba);
    Colour(const RGBA & rgba, uint8_t alpha);
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
    /// @brief Compute an opaque colour with random RGB components.
    
    const static Colour random();
    
    /// @brief Compute a shade of the given colour.
    /// @param colour The median colour of the shade range to be computed.
    /// @param index The index of the shade to be computed, where zero is the given colour,
    /// negative indices are darker than the given colour, and positive indices are lighter than the given colour.
    /// @param contrast The desired contrast between each shade.
    
    const static Colour shade(const Colour & colour, int16_t index, uint8_t contrast);

public:
    const static Colour lightBlack;
    const static Colour offWhite;
    const static Colour black;
    const static Colour white;
    const static Colour red;
    const static Colour sienna;
    const static Colour lightBlue;
    const static Colour darkBlue;
    const static Colour blue;
    const static Colour pink;
    const static Colour green;
    const static Colour hunter;
    const static Colour yellow;

private:
    RGBA rgba;
};

}

#endif
