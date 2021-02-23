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
    UIComponent(const float x = 0.0f,
                const float y = 0.0f,
                const float z = 0.0f,
                const float width  = 100.0f,
                const float height = 100.0f);

public:
    virtual const UISize <float> & getSize()   const noexcept;
    virtual const UIPoint<float> & getOrigin() const noexcept;
    virtual const UIPoint<float> & getCentre() const noexcept;
    virtual const DrawKit::Colour  & getColour() const noexcept;

public:
    /// @brief Set the component's colour.
    /// @param colour The desired colour.

    virtual void setColour(const Colour & colour) noexcept;

public:
    /// @brief Set the component's bounds using another's component's origin and size.
    /// @param bounds The component whose origin and size should be used to set the bounds.

    virtual void setBounds(const UIComponent & bounds);

public:
    virtual void scaleFromCentre(float scaleFactor);
    virtual void scaleFromOrigin(float scaleFactor);
    virtual void scaleFromCentre(float scaleFactorX, float scaleFactorY);
    virtual void scaleFromOrigin(float scaleFactorX, float scaleFactorY);
    
public:
    virtual void setSizeFromOrigin(float width, float height);
    virtual void setSizeFromOrigin(const UISize<float> & size);
    virtual void setSizeFromCentre(float width, float height);
    virtual void setSizeFromCentre(const UISize<float> & size);

public:
    virtual void translate(float x, float y, float z = 0);
    virtual void setPositionWithOrigin(float x, float y, float z = 0);
    virtual void setPositionWithOrigin(const UIPoint<float> & xyz);
    virtual void setPositionWithCentre(float x, float y, float z = 0);
    virtual void setPositionWithCentre(const UIPoint<float> & xyz);
    
public:
    virtual void setMargins(const float marginSize);
    virtual void setMargins(const UIMargins<float>& margins);
    virtual void setMargins(const float top, const float left, const float right, const float bottom);
    
public:
    virtual std::string const toString() const;
    friend  std::ostream & operator << (std::ostream & stream, const UIComponent & component);

protected:
    UISize <float> size;
    UIPoint<float> origin;
    UIPoint<float> centre;
    UIMargins<float> margins;

protected:
    Colour colour = Colour::white;
};

}

#endif
