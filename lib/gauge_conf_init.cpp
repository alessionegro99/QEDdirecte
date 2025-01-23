#include <iostream>

#include "../include/gauge_conf.hpp"
#include "../include/random.hpp"

void gaugeConf::hotStart()
{
    std::mt19937 rng = initializeRNG(seed);
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            lattice[index(i, j)] = U1(2 * M_PI * dist(rng));
        }
    }
}