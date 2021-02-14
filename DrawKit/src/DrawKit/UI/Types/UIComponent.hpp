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

public:
    virtual void setSizeFromOrigin(int32_t width, int32_t height);
    virtual void setSizeFromCentre(int32_t width, int32_t height);
    
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
    UIPoint<int32_t> origin;
    UIPoint<int32_t> centre;
    UISize<uint32_t> size;
};

}

#endif
