//  DrawKit
//  Created by David Spry on 23/1/21.

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "dk.pch"
#include "UIComponent.hpp"

namespace DrawKit {

class Rectangle: public UIComponent
{
public:
    Rectangle(const int32_t x = 0,
              const int32_t y = 0,
              const int32_t width  = 100,
              const int32_t height = 100):
    UIComponent(x, y, 0, width, height)
    {
        
    }
    
    Rectangle(const UIPoint<int32_t> & origin,
              const UISize<uint32_t> & size):
    UIComponent(origin.x, origin.y, origin.z, size.w, size.h)
    {
        
    }
};

}

#endif
