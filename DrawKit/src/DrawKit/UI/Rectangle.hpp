//  DrawKit
//  Created by David Spry on 23/1/21.

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "dk.pch"
#include "UITypes.h"

namespace DrawKit {

class Rectangle: public UIPrimitive
{
public:
    Rectangle(const int32_t x = 0,
              const int32_t y = 0,
              const int32_t width  = 100,
              const int32_t height = 100):
    UIPrimitive(x, y, width, height)
    {
        
    }
};

}

#endif
