//  DrawKit
//  Created by David Spry on 3/2/21.

#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Rectangle.hpp"

namespace DrawKit {

class Square: public Rectangle
{
public:
    Square(uint32_t x = 0,
           uint32_t y = 0,
           uint32_t size = 100):
    Rectangle(x, y, size, size)
    {
        
    }
};

}

#endif
