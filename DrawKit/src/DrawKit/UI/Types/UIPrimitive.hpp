//  DrawKit
//  Created by David Spry on 14/2/21.

#ifndef UIPRIMITIVE_HPP
#define UIPRIMITIVE_HPP

#include "dk.pch"
#include "UIComponent.hpp"

namespace DrawKit {

class UIPrimitive: public UIComponent
{
public:
    UIPrimitive(int32_t x = 0,
                int32_t y = 0,
                uint32_t width  = 100,
                uint32_t height = 100):
    UIComponent(x, y, width, height)
    {
        
    }

public:
    void setColour(const Colour& colour) noexcept;
    
public:
    const Colour & getColour() const noexcept;
    
private:
    Colour colour = Colour::white;
};

}

#endif
