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

    allParams p(filename);

    physParams pp(p);
    simParams sp(p);

    gaugeConf test(pp, sp);
    test.display();

    return 0;
}
