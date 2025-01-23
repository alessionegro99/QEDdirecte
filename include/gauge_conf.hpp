#pragma once

#include <iostream>
#include <string>
#include <vector>
 
#include "U1.hpp"
#include "parameters.hpp"
 
class gaugeConf
{
private:
    const size_t rows;
    const size_t cols;

    const size_t seed;
    const std::string start;

    std::vector<U1> lattice;

    size_t index(int row, int col) const
    {
        return row * cols + col;
    }

public:
    gaugeConf(const physParams &pp, const simParams &sp) : rows(pp.tot_vol),
                                                           cols(pp.ST_DIM),
                                                           lattice(pp.tot_vol * pp.ST_DIM, U1(0.0)),
                                                           seed(sp.seed),
                                                           start(sp.start)
    {
        if (start == "hot")
        {
            hotStart();
        }

        else if (start == "read")
        {
        }
    }

    // initializer
    void hotStart();

    // displayer
    void display() const;

    // updater
    void HMC(size_t tot_vol, size_t n_HMC);
};



