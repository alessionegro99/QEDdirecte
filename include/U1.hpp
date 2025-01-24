#pragma once

#include <complex>

// struct for U1 group elements
// exp{i\theta} with -pi<\theta<pi
struct U1
{
    std::complex<double> value;

    U1() : value(1.) {}

    U1(double theta) : value(std::exp(std::complex<double>(0, theta))) {}

    U1 operator*(const U1 &other) const
    {
        return U1(std::arg(value) + std::arg(other.value));
    }

    U1 inverse() const
    {
        return U1(-std::arg(value));
    }

    void display() const
    {
        std::cout << std::arg(value) << std::endl;
    }
};