#include <iostream>
#include <cmath>

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

double configuration::HMC_sweep(size_t n_hmc)
{
    long r;
    int i, j, k;
    double **momenta = nullptr;
    double dH, weight;           // change in the Hamiltonian
    long accepted_per_sweep = 0; // keep track of the acceptance rate

    double P; // auxiliary momentum
    double F; // force necessary for HMC update
    U1 Q;     // phase space coordinate (gauge link)

    // step size of the integrator
    double dt = 1.0 / double(n_hmc);

    for (r = 0; r < geo.d_vol; r++)
    {
        for (j = 0; j < geo.ST_DIM; j++)
        {
            // dynamically allocating memory for the momenta variables
            // momenta distribution needs to be refreshed at the start of every trajectory
            initMomenta(momenta, sim.seed, geo.d_vol, geo.ST_DIM);

            // first half step
            Q = lattice[r][j];
            F = force(Q, r, j);

            P = momenta[r][j] - 0.5 * dt * F;

            // (n-1) full steps
            for (k = 1; k < n_hmc; k++)
            {
                Q *= U1(dt * P);
                F = force(Q, r, j);

                P -= dt * F;
            }

            // final step
            Q *= U1(dt * P);
            F = force(Q, r, j);

            P -= 0.5 * dt * F;

            // accept-reject step
            dH = P - momenta[r][j] + dSGauge(Q, r, j);
            weight = std::exp(-dH);

            std::mt19937 rng = initializeRNG(sim.seed);
            std::uniform_real_distribution<double> dis(0.0, 1.0);

            if (dis(rng) < weight)
            {
                lattice[r][j] = Q;
                accepted_per_sweep += 1;
            }

            // freeing memory
            freeMomenta(momenta, geo.d_vol, geo.ST_DIM);
        }
    }
    return ((double)accepted_per_sweep/((double)Q.N_c)/((double)geo.ST_DIM))*geo.d_inv_vol;
}