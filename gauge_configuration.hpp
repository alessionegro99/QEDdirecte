#pragma once

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <cmath>

#include "random.hpp"
#include "parameters.hpp"

// Initializes the gauge configuration with a cold start. Every link
// is set to unity.
/* std::vector<U1> coldStart(const size_t ST_DIM, const size_t L, const size_t T)
{
    int lattice_volume = (ST_DIM - 1) * L * T;

    std::vector<U1> gauge_configuration;

    gauge_configuration.reserve(lattice_volume);

    for (size_t i = 0; i < lattice_volume; ++i)
    {
        gauge_configuration.emplace_back(0.0);
    }

    return gauge_configuration;
} */


std::vector<U1> hotStart(const physicalParameters &physical_parameters)
{
    std::vector<U1> gauge_configuration;

    std::mt19937 rng = initializeRNG(physical_parameters.getSeed());

    std::uniform_real_distribution<double> dist(0.0, 1.0);

    gauge_configuration.reserve(physical_parameters.totalVolume());

    for (size_t i = 0; i < physical_parameters.totalVolume(); ++i)
    {
        gauge_configuration.emplace_back(2 * M_PI * dist(rng));
    }

    return gauge_configuration;
}
