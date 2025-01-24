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

/*     for (size_t r = 0; r < geo.d_vol; ++r)
    {
        for (size_t j = 0; j < geo.ST_DIM; ++j)
        {
            test.lattice[r][j].display();
        }
    } */

    test.freeGaugeConf();

    geo.freeGeometry();


    return 0;
}
