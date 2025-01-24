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

    // in gauge_conf_init.cpp
    //  initialize gauge configuration
    void initGaugeConf();
    void freeGaugeConf();

    /*     // in gauge_conf_init.cpp
        // initializer
        void hotStart();

        // in gauge_conf_tools.cpp
        // displayer
        void display() const;

        // in gauge_conf_update.cpp
        // updater
        void HMC(size_t tot_vol, size_t n_HMC);

        size_t index(int row, int col) const
        {
            return row * geo.ST_DIM + col;
        } */
};
