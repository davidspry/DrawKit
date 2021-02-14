//  DrawKit
//  Created by David Spry on 23/1/21.

#ifndef UISIZE_H
#define UISIZE_H

namespace DrawKit
{

template <typename T>
struct UISize
{
    union
    {
        T w;
        T width;
    };
    
    union
    {
        T h;
        T height;
    };

    inline bool operator == (const UISize<T> & q)
    {
        return w == q.w && h == q.h;
    }

    friend UISize<T> operator + (const UISize<T> & p, const UISize<T> & q)
    {
        return {p.w + q.w, p.h + q.h};
    }
    
    friend UISize<T> operator - (const UISize<T> & p, const UISize<T> & q)
    {
        return {p.w - q.w, p.h - q.h};
    }
};

}

#endif
