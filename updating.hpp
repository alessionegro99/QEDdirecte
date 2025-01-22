#pragma once

#include <random.hpp>
#include <parameters.hpp>



double hybridMonteCarlo(const physicalParameters &physical_parameters)
{
    std::mt19937 rng = initializeRNG(physical_parameters.getSeed());

    double mean = 0.0;
    double std_dev = 1.0;

    std::normal_distribution<double> normalDist(mean, std_dev);

    double beta = 1.;
}