//  DrawKit
//  Created by David Spry on 21/2/21.

#ifndef RANDOM_HPP
#define RANDOM_HPP

#include "dk.pch"
#include "Utilities.hpp"

namespace DrawKit {

/// @brief Tools for modelling randomness.

class Random
{
private:
     Random() = default;
    ~Random() = default;
    
public:
    /// @brief Generate a boolean value randomly.

    [[nodiscard]] static bool chance();
    
    /// @brief Generate a integer in the given range randomly.
    /// @param lowerBound The lower bound of the desired range.
    /// @param upperBound The upper bound of the desired range.

    [[nodiscard]] static int random(int lowerBound, int upperBound);
    
    /// @brief Generate a number between 0.0 and 1.0 randomly.

    [[nodiscard]] static double random();
    
    /// @brief Generate a number in the given range randomly.
    /// @param lowerBound The lower bound of the desired range.
    /// @param upperBound The upper bound of the desired range.

    [[nodiscard]] static double random(double lowerBound, double upperBound);
    
protected:
    static Random & getInstance()
    {
        static Random * instance = nullptr;
        
        if (!instance)
             return *(instance = new Random());
        else return *(instance);
    }
    
private:
    std::default_random_engine generator;
};

}

#endif
