#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <optional>
#include <complex>
#include <stdexcept>
#include <unordered_map>

#include "random.hpp"
#include "U1.hpp"
#include "gauge_configuration.hpp"
#include "parameters.hpp"

int main(int argc, char *argv[])
{
/*     if (argc != 3 || std::string(argv[1]) != "-f")
    {
        printUsage(argv[0]);

        return 1;
    }

    std::cout << randUnif(0, 1, 1234567) << std::endl;

    const size_t L{3};
    const size_t T{3};
    const size_t ST_DIM{3};

    std::vector<U1> gauge_configuration = coldStart(ST_DIM, L, T);

    std::cout << gauge_configuration.size() << std::endl;
    for (size_t i = 0; i < gauge_configuration.size(); ++i)
    {
        gauge_configuration[i].display();
    } */

    allParameters params("input");
    std::cout << "d: " << params.getInt("T") << std::endl;

    physicalParameters physical_parameters(params);

    std::cout << physical_parameters.getST_DIM() << std::endl;

    std::vector<U1> gauge_configuration = hotStart(physical_parameters);
    for (size_t i = 0; i < gauge_configuration.size(); ++i)
    {
        gauge_configuration[i].display();
    }
}
