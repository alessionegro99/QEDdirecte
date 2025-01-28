#include <iostream>

#include "../include/gauge_conf.hpp"
#include "../include/parameters.hpp"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " -f <filename>" << std::endl;
        return 1;
    }

    std::string flag = argv[1];
    if (flag != "-f")
    {
        std::cerr << "Error: Unknown flag " << flag << ". Expected -f." << std::endl;
        return 1;
    }

    std::string filename = argv[2];

    /**************************************/

    parameters p(filename);

    geometry geo(p);
    simulation sim(p);

    geo.printAll();

    configuration test(geo, sim);

    /*     for (long r = 0; r < geo.d_vol; ++r)
        {
            for (int j = 0; j < geo.ST_DIM; ++j)
            {
                std::cout << test.lattice[r][j].value << " " << test.lattice[geo.nnp(r, j)][j].value << std::endl;
                std::cout << test.lattice[r][j].module() << " " << test.lattice[geo.nnp(r, j)][j].module() << std::endl;
                std::cout << test.lattice[r][j].phase() << " " << test.lattice[geo.nnp(r, j)][j].phase() << std::endl;

                std::cout << test.lattice[r][j] + test.lattice[geo.nnp(r, j)][j] << " " << test.lattice[r][j] - test.lattice[geo.nnp(r, j)][j] << std::endl;

                std::cout << "####" << std::endl;
            }
            std::cout << "\n";
        } */

    long r = 0;
    int i = 0;
    int j = 1;

    /*     std::complex<double> teststaple = test.staple(r, i);

        std::cout << teststaple << std::endl; */

    U1 testplaquette = test.plaquette(r, i, j);

    std::cout << testplaquette.a << std::endl;

    std::complex<double> avgplaq = 0.;

    for (r = 0; r < geo.d_vol; r++)
    {
        for (i = 0; i < geo.ST_DIM; i++)
        {
            for (j = i + 1; j < geo.ST_DIM; j++)
            {
                testplaquette = test.plaquette(r, i, j);
                avgplaq += testplaquette;
            }
        }
    }
    //avgplaq *= geo.d_inv_vol;

    std::cout << avgplaq << std::endl;

    test.freeGaugeConf();

    geo.freeGeometry();

    return 0;
}
