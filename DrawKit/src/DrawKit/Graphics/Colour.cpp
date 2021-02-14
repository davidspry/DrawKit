//  DrawKit
//  Created by David Spry on 3/2/21.

#include "Colour.hpp"

namespace DrawKit {

Colour::Colour(const Colour & colour, uint8_t alpha)
{
    rgba.r = colour.rgba.r;
    rgba.g = colour.rgba.g;
    rgba.b = colour.rgba.b;
    rgba.a = static_cast<float>(bound((int) alpha, 0, 255)) / 255.0f;
}

Colour::Colour(const Colour & A, const Colour & B, float lerpFactor)
{
    rgba = A.rgba;

    mix(B, lerpFactor);
}

Colour::Colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    rgba.r = static_cast<float>(bound((int) r, 0, 255)) / 255.0f;
    rgba.g = static_cast<float>(bound((int) g, 0, 255)) / 255.0f;
    rgba.b = static_cast<float>(bound((int) b, 0, 255)) / 255.0f;
    rgba.a = static_cast<float>(bound((int) a, 0, 255)) / 255.0f;
}

void Colour::mix(const Colour & colour, float lerpFactor) noexcept
{
    lerpFactor = bound(lerpFactor, 0.0f, 1.0f);
    rgba.r = lerp(rgba.r, colour.rgba.r, lerpFactor);
    rgba.g = lerp(rgba.g, colour.rgba.g, lerpFactor);
    rgba.b = lerp(rgba.b, colour.rgba.b, lerpFactor);
    rgba.a = lerp(rgba.a, colour.rgba.a, lerpFactor);
}

void Colour::darken(float factor) noexcept
{
    if (factor < 0.0f)
        return lighten(std::fabsf(factor));
    
    rgba.r = bound(rgba.r - factor * rgba.r, 0.0f, 1.0f);
    rgba.g = bound(rgba.g - factor * rgba.g, 0.0f, 1.0f);
    rgba.b = bound(rgba.b - factor * rgba.b, 0.0f, 1.0f);
    rgba.a = bound(rgba.a - factor * rgba.a, 0.0f, 1.0f);
}

void Colour::lighten(float factor) noexcept
{
    if (factor < 0.0f)
        return darken(std::fabsf(factor));
    
    rgba.r = bound(rgba.r + factor * rgba.r, 0.0f, 1.0f);
    rgba.g = bound(rgba.g + factor * rgba.g, 0.0f, 1.0f);
    rgba.b = bound(rgba.b + factor * rgba.b, 0.0f, 1.0f);
    rgba.a = bound(rgba.a + factor * rgba.a, 0.0f, 1.0f);
}

const RGBA & Colour::getRGBA() const noexcept
{
    return rgba;
}

// MARK: - Constants

const Colour Colour::lightBlack = { 15,  15,  15, 255};

const Colour Colour::offwhite   = {235, 235, 235, 255};

const Colour Colour::black      = {  0,   0,   0, 255};

const Colour Colour::white      = {255, 255, 255, 255};

const Colour Colour::red        = {235,  85,  55, 255};

const Colour Colour::blue       = { 35, 105, 245, 255};

const Colour Colour::pink       = {255, 190, 205, 255};

const Colour Colour::green      = { 45, 215,  95, 255};

const Colour Colour::salmon     = {255, 165, 175, 255};

const Colour Colour::yellow     = {255, 205,  95, 255};

}