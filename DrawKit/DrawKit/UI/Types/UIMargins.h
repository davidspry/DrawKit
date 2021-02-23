//  DrawKit
//  Created by David Spry on 24/2/21.

#ifndef UIMARGINS_H
#define UIMARGINS_H

#include "dk.pch"

/// @brief A four-component struct representing a margin around a rectangle.

template <typename T>
struct UIMargins
{
    T t;
    T l;
    T r;
    T b;

    UIMargins(T top    = static_cast<T>(0),
              T left   = static_cast<T>(0),
              T right  = static_cast<T>(0),
              T bottom = static_cast<T>(0))
    {
        static_assert(std::is_arithmetic<T>::value, "The given type must be numeric.");

        this->l = left;
        this->r = right;
        this->t = top;
        this->b = bottom;
    }

    UIMargins(T horizontal, T vertical)
    {
        static_assert(std::is_arithmetic<T>::value, "The given type must be numeric.");

        this->l = horizontal;
        this->r = horizontal;
        this->t = vertical;
        this->b = vertical;
    }
    
    void set(T top, T left, T right, T bottom)
    {
        this->l = left;
        this->r = right;
        this->t = top;
        this->b = bottom;
    }
};

#endif
