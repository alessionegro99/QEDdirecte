#include <iostream>

#include "gauge_conf.hpp"

// computes the staple in position r, direction i
U1 configuration::staple(long r, int i)
{
    int j, l;
    long k;
    U1 link1, link2, link3, link12, staple;

    staple = U1(0.0);

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

        staple = link1 * link2.inverse() * link3.inverse();

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

        staple = staple + link1.inverse() * link2.inverse() * link3;
    }

    return staple;
}