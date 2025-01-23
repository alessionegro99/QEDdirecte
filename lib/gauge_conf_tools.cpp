#include <iostream>

#include "../include/gauge_conf.hpp"

void gaugeConf::display() const
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            std::cout << std::arg(lattice[index(i, j)].value) << std::endl;
        }
    }
    std::cout << std::endl;
} 