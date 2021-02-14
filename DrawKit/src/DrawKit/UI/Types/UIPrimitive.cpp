//  DrawKit
//  Created by David Spry on 14/2/21.

#include "UIPrimitive.hpp"

namespace DrawKit {

void UIPrimitive::setColour(const Colour& colour) noexcept
{
    this->colour = colour;
}

const Colour & UIPrimitive::getColour() const noexcept
{
    return colour;
}

}
