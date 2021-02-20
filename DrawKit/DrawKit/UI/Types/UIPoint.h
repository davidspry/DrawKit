//  DrawKit
//  Created by David Spry on 23/1/21.

#ifndef UIPOINT_H
#define UIPOINT_H

#include "dk.pch"

namespace DrawKit
{

template <typename T>
struct UIPoint
{
    T x;
    T y;
    T z;
    
    UIPoint(T x = static_cast<T>(0), T y = static_cast<T>(0), T z = static_cast<T>(0))
    {
        static_assert(std::is_arithmetic<T>::value, "The given type must be numeric.");
        
        this->x = x;
        this->y = y;
        this->z = z;
    }

    inline bool operator == (const UIPoint<T> & q)
    {
        return x == q.x && y == q.y && z == q.z;
    }

    friend UIPoint<T> operator + (const UIPoint<T> & p, const UIPoint<T> & q)
    {
        return {p.x + q.x, p.y + q.y, p.z + q.z};
    }
    
    friend UIPoint<T> operator - (const UIPoint<T> & p, const UIPoint<T> & q)
    {
        return {p.x - q.x, p.y - q.y, p.z - q.z};
    }
    
    friend UIPoint<T> operator * (const UIPoint<T> & p, const UIPoint<T> & q)
    {
        return {p.x * q.x, p.y * q.y, p.z * q.z};
    }
    
    friend UIPoint<T> operator * (const UIPoint<T> & p, const T & k)
    {
        return {p.x * k, p.y * k, p.z * k};
    }
    
    friend UIPoint<T> operator / (const UIPoint<T> & p, const UIPoint<T> & q)
    {
        return {p.x / q.x, p.y / q.y, p.z / q.z};
    }

    friend UIPoint<T> operator / (const UIPoint<T> & p, const T & k)
    {
        return {p.x / k, p.y / k, p.z / k};
    }
};

}
#endif
