//  DrawKit
//  Created by David Spry on 3/2/21.

#include "Utilities.hpp"

namespace DrawKit   {
namespace WaveTable {

float sine(float x)
{
    constexpr float normalisation = wt_sine_length / TWO_PI;
    
    float const t = std::fmod(x, TWO_PI) * normalisation;
    float const k = std::floorf(t);
    float const r = t - k;

    float const source = wt_sine[(int) k];
    float const target = wt_sine[(int) (k + 1) % wt_sine_length];
    
    return lerp(source, target, r);
}

float cosine(float x)
{
    return sine(x + HALF_PI);
}


}
}
