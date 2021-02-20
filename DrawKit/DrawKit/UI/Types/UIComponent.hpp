//  DrawKit
//  Created by David Spry on 23/1/21.

#ifndef UICOMPONENT_HPP
#define UICOMPONENT_HPP

#include "UISize.h"
#include "UIPoint.h"

namespace DrawKit
{

class UIComponent
{
public:
    UIComponent(const int32_t x = 0,
                const int32_t y = 0,
                const int32_t z = 0,
                const int32_t width  = 100,
                const int32_t height = 100);

public:
    virtual const UISize<uint32_t> & getSize()   const noexcept;
    virtual const UIPoint<int32_t> & getOrigin() const noexcept;
    virtual const UIPoint<int32_t> & getCentre() const noexcept;
    virtual const DrawKit::Colour  & getColour() const noexcept;

public:
    virtual void setColour(const Colour & colour) noexcept;
    
public:
    virtual void scaleFromCentre(float scaleFactor);
    virtual void scaleFromOrigin(float scaleFactor);
    virtual void setSizeFromOrigin(int32_t width, int32_t height);
    virtual void setSizeFromOrigin(const UISize<uint32_t> & size);
    virtual void setSizeFromCentre(int32_t width, int32_t height);
    virtual void setSizeFromCentre(const UISize<uint32_t> & size);

public:
    virtual void translate(int32_t x, int32_t y, int32_t z);
    virtual void setPositionWithOrigin(int32_t x, int32_t y, int32_t z);
    virtual void setPositionWithOrigin(const UIPoint<int32_t> & xyz);
    virtual void setPositionWithCentre(int32_t x, int32_t y, int32_t z);
    virtual void setPositionWithCentre(const UIPoint<int32_t> & xyz);
    
public:
    virtual std::string const toString() const;
    friend  std::ostream & operator << (std::ostream & stream, const UIComponent & component);

protected:
    UISize<uint32_t> size;
    UIPoint<int32_t> origin;
    UIPoint<int32_t> centre;
    Colour colour = Colour::white;
};

}

#endif
