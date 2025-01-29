#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "U1.hpp"
#include "parameters.hpp"

class configuration
{
private:
    const geometry &geo;
    const simulation &sim;

public:
    U1 **lattice; // [total volume][ST_DIM]

    configuration(const geometry &geom, const simulation &simul) : geo(geom),
                                                                   sim(simul)
    {
        initGaugeConf();
    }

    // in gauge_conf_def.cpp
    // initialize gauge configuration
    void initGaugeConf();
    void freeGaugeConf();

    // in gauge_conf_meas.cpp
    std::complex<double> staple(long r, int i); // computes the staple at point r direction i
    std::complex<double> avgPlaquette();        // plaquette averaged over total volume
    U1 plaquette(long r, int i, int j);         // plaquette at point r in the i-j plane

    // in gauge_conf_update.cpp
    void hybridMonteCarlo(size_t n_hmc);
};
