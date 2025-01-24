#include <iostream>

#include "../include/gauge_conf.hpp"
#include "../include/random.hpp"

void configuration::initGaugeConf()
{
    long r;
    int j;

    lattice = new U1 *[geo.d_vol];
    if (!lattice)
    {
        std::cerr << "Failed to allocate memory for lattice rows.\n";
    }
    for (r = 0; r < geo.d_vol; r++)
    {
        lattice[r] = new U1[geo.ST_DIM];
        if (!lattice[r])
        {
            std::cerr << "Failed to allocate memory for lattice columns at row " << r << ".\n";

            for (size_t j = 0; j < r; j++)
            {
                delete[] lattice[j];
            }
            delete[] lattice;
        }
    }

    if (sim.start == "cold")
    {
        for (r = 0; r < geo.d_vol; ++r)
        {
            for (j = 0; j < geo.ST_DIM; ++j)
            {
                lattice[r][j] = U1(0.0);
            }
        }
    }
    else if (sim.start == "hot")
    {
        std::mt19937 rng = initializeRNG(sim.seed);
        std::uniform_real_distribution<double> dist(0.0, 1.0);

        for (r = 0; r < geo.d_vol; r++)
        {
            for (j = 0; j < geo.ST_DIM; j++)
            {
                lattice[r][j] = U1(2 * M_PI * dist(rng));
            }
        }
    }
    else if (sim.start == "read")
    {
    }
    else
    {
    }
}

void configuration::freeGaugeConf()
{
    long r;

    for (r = 0; r < geo.d_vol; ++r)
    {
        delete[] lattice[r];
    }
    delete[] lattice;
}