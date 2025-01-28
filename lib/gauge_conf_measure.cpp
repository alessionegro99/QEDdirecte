#include <iostream>

#include "gauge_conf.hpp"

// computes the staple in position r, direction i
std::complex<double> configuration::staple(long r, int i)
{
    int j, l;
    long k;
    U1 link1, link2, link3, tmp;

    std::complex<double> staple; // to re-do, implement better

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

        tmp = link1 * link2.dag() * link3.dag();

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

        staple = tmp + link1.dag() * link2.dag() * link3;
    }

    return staple;
}

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
