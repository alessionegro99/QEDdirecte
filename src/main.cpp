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

    // initialize
    parameters p(filename);
    geometry geo(p);
    simulation sim(p);

    std::cout << "/*****************************/" << "\n";

    // print all geometric parameters
    geo.printAll();

    std::cout << "/*****************************/" << "\n";

    // print all simulation parameters
    sim.printAll();
    std::cout << "/*****************************/" << "\n";

    // create configuration
    configuration test(geo, sim);

    /********* UPDATE **********/

    double ar = test.HMC_sweep(sim.n_hmc);

    std::cout << ar << std::endl;

    /***************************/

    // free memory
    test.freeGaugeConf();
    geo.freeGeometry();

    return 0;
}
