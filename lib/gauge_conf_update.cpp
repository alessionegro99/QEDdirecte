#include <iostream>

#include "../include/gauge_conf.hpp"
#include "../include/random.hpp"

void gaugeConf::HMC(size_t tot_vol, size_t n_HMC)
{
    std::cout << std::endl;
    std::mt19937 rng = initializeRNG(seed);

    const double mean = 0.0;
    const double std_dev = 1.0;

    std::normal_distribution<double> normalDist(mean, std_dev);

    std::vector<double> momenta_conf(tot_vol);

    for (auto &momentum : momenta_conf)
    {
        momentum = normalDist(rng);
    }

    double dt = 1/double(n_HMC);

    //first half step
}