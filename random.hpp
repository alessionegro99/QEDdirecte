#pragma once

#include <iostream>
#include <random>

std::mt19937 initializeRNG(int seed)
{
    if (seed != 0)
    {
        return std::mt19937(seed); // Seeded RNG for reproducibility
    }
    else
    {
        std::random_device rd;
        return std::mt19937(rd()); // Random seed
    }
}
