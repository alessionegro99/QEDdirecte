#include <iostream>

#include "../include/gauge_conf.hpp"
#include "../include/random.hpp"

void initMomenta(double **&momenta, long seed, long d_vol, size_t ST_DIM)
{
    long r;
    int j;

    // allocating memory for momenta configuration
    momenta = new double *[d_vol];
    if (!momenta)
    {
        std::cerr << "Failed to allocate memory for momenta rows.\n";
    }
    for (r = 0; r < d_vol; r++)
    {
        momenta[r] = new double[d_vol];
        if (!momenta[r])
        {
            std::cerr << "Failed to allocate memory for momenta columns at row " << r << ".\n";

            for (size_t j = 0; j < r; j++)
            {
                delete[] momenta[j];
            }
            delete[] momenta;
        }
    }

    // random gaussian initialization of momenta variables
    std::mt19937 rng = initializeRNG(seed);

    const double mean = 0.0;
    const double std_dev = 1.0;

    std::normal_distribution<double> normalDist(mean, std_dev);

    for (r = 0; r < d_vol; r++)
    {
        for (j = 0; j < ST_DIM; j++)
        {
            momenta[r][j] = normalDist(rng);
        }
    }
}

void freeMomenta(double **&momenta, long d_vol, size_t ST_DIM)
{
    long r;

    for (r = 0; r < d_vol; ++r)
    {
        delete[] momenta[r];
    }
    delete[] momenta;
}

void configuration::hybridMonteCarlo(size_t n_hmc)
{
    long r;
    int j;
    double **momenta = nullptr;

    // dynamically allocating memory for the momentav variables
    initMomenta(momenta, sim.seed, geo.d_vol, geo.ST_DIM);

    // 
    double dt = 1 / double(n_hmc);

    for (r = 0; r < geo.d_vol; r++)
    {
        for (j = 0; j < geo.ST_DIM; j++)
        {
            std::cout << momenta[r][j] << std::endl;
        }
    }

    // freeing memory
    freeMomenta(momenta, geo.d_vol, geo.ST_DIM);
}