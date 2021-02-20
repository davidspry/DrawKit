//  DrawKit
//  Created by David Spry on 21/2/21.

#include "Random.hpp"

namespace DrawKit {

bool Random::chance()
{
    auto & random = getInstance();
    
    std::bernoulli_distribution distribution;
    
    return distribution(random.generator);
}

int Random::random(int lowerBound, int upperBound)
{
    auto & random = getInstance();

    std::uniform_int_distribution<int> distribution(lowerBound, upperBound);

    return distribution(random.generator);
}

double Random::random()
{
    auto & random = getInstance();
    
    std::uniform_real_distribution<double> distribution;
    
    return distribution(random.generator);
}

double Random::random(double lowerBound, double upperBound)
{
    auto & random = getInstance();
    
    std::uniform_real_distribution<double> distribution(lowerBound, upperBound);
    
    return distribution(random.generator);
}

}
