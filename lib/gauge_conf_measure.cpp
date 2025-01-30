#include <iostream>

#include "gauge_conf.hpp"

// computes the sum of staples in direction i at position r
std::complex<double> configuration::staple(long r, int i)
{
    int j, l;
    long k;
    U1 link1, link2, link3, tmp1, tmp2;

    std::complex<double> staple = 0.0; // implement better

    for (l = i + 1; l < i + geo.ST_DIM; l++)
    {
        j = (l % geo.ST_DIM);

        //
        //       i ^
        //         |   (1)
        //         +----->-----+
        //         |           |
        //                     |
        //         |           V (2)
        //                     |
        //         |           |
        //         +-----<-----+-->   j
        //       r     (3)
        //

        link1 = lattice[geo.nnp(r, i)][j];
        link2 = lattice[geo.nnp(r, j)][i];
        link3 = lattice[r][j];

        tmp1 = link1 * link2.dag() * link3.dag();

        //
        //       i ^
        //         |   (1)
        //         |----<------+
        //         |           |
        //         |
        //     (2) V           |
        //         |
        //         |           |
        //         +------>----+--->j
        //        k     (3)    r
        //

        k = geo.nnm(r, j);

        link1 = lattice[geo.nnp(k, i)][j];
        link2 = lattice[k][i];
        link3 = lattice[k][j];

        tmp2 = link1.dag() * link2.dag() * link3;

        staple += tmp1 + tmp2;
    }

    return staple;
}

// computes the plaquette at position r in the i-j plane
U1 configuration::plaquette(long r, int i, int j)
{
    //
    //       ^ j
    //       |   (3)
    //       +---<---+
    //       |       |
    //   (4) V       ^ (2)
    //       |       |
    //       +--->---+---> i
    //       r   (1)
    //
    return lattice[r][i] * lattice[geo.nnp(r, i)][j] * lattice[r][j].dag() * lattice[geo.nnp(r, j)][i];
}

// leveraging translational invariance due to periodic boundary conditions,
// computes the plaquette averaged over the entire lattice
std::complex<double> configuration::avgPlaquette()
{
    long r;
    int i, j;
    std::complex<double> avg(0., 0.);

    for (r = 0; r < geo.d_vol; r++)
    {
        for (i = 0; i < geo.ST_DIM; i++)
        {
            for (j = i + 1; j < geo.ST_DIM; j++)
            {
                avg += plaquette(r, i, j);
            }
        }
    }
    return geo.d_inv_vol * avg;
}

double configuration::force(U1 link_proposal, long r, int j)
{
    return sim.beta / ((double)link_proposal.N_c) * std::imag(link_proposal * configuration::staple(r, j));
}

double configuration::dSGauge(U1 link_proposal, long r, int j)
{
    return sim.beta / ((double)link_proposal.N_c) * std::imag((link_proposal - lattice[r][j]) * configuration::staple(r, j));
}