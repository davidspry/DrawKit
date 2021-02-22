//  DrawKit
//  Created by David Spry on 21/2/21.

#ifndef RENDERER_TYPES_H
#define RENDERER_TYPES_H

#include "Colour.hpp"
#include <cstdint>

using index_t = uint32_t;

typedef struct
{
    float x, y, z;
}   vertex_t;

typedef struct
{
    float x, y, z;
    DrawKit::RGBA rgba;
}   vertex_colour_t;

#endif
