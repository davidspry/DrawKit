//  DrawKit
//  Created by David Spry on 3/2/21.

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "dk.pch"

template <typename ...A>
inline static void DK_PRINT(A && ...arguments)
{
    ((std::cout << std::forward<A>(arguments) << " "), ...) << std::endl;
}

template <typename ...A>
inline static void DK_LOG(const std::string & module, A && ...arguments)
{
    std::cout << "[" << std::left << std::setw(15) << module << "] ";

    DK_PRINT(arguments...);
}

template <typename M, typename ...A>
inline static void DK_FATAL_ERROR(M && module, A && ...arguments)
{
    DK_LOG(module, arguments...);

    exit(1);
}

template <typename ...A>
inline static void DK_ASSERT(const bool & statement, A && ...arguments)
{
    if (statement) return;
    
    DK_FATAL_ERROR("Assertion Error", arguments...);
}

template <typename T>
[[nodiscard]] inline static T bound(T value, T minimum, T maximum)
{
    return ((value > maximum ? maximum : value) < minimum) ? minimum : value;
}

template <typename T>
[[nodiscard]] inline static T lerp(T source, T target, float factor)
{
    return static_cast<T>(static_cast<float>(source) + factor *
                          static_cast<float>(target - source));
}

template <typename T>
[[nodiscard]] inline static T normalise(T value, T minimum, T maximum)
{
    return bound((value - minimum) / (maximum - minimum), static_cast<T>(0), static_cast<T>(1));
}

template <typename T>
[[nodiscard]] inline static T denormalise(T value, T minimum, T maximum)
{
    return bound(value, static_cast<T>(0), static_cast<T>(1)) * (maximum - minimum) + minimum;
}

template <typename T>
[[nodiscard]] inline static T midpoint(T first, T second)
{
    return first + (second - first) * static_cast<T>(0.5);
}

namespace DrawKit   {
namespace WaveTable {

float sine(float x);

float cosine(float x);

}
}

#endif
