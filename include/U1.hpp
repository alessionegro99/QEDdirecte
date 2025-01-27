#pragma once

#include <complex>

// struct for U1 group elements
// exp{i\theta} with -pi<\theta<pi
struct U1
{
    const size_t N_c = 1;

    std::complex<double> a;

    U1() : a(1.) {} // needed for dynamical allocation of memory for 2D arrays
    U1(double theta) : a(std::exp(std::complex<double>(0, theta))) {}

    U1 operator*(const U1 &other) const
    {
        return U1(std::arg(a) + std::arg(other.a));
    }

    U1 operator+ (const U1 &other) const
    {
        return U1(std::arg(a + other.a));
    }

    U1 inverse() const
    {
        return U1(-std::arg(a));
    }

    void display() const
    {
        std::cout << std::arg(a) << std::endl;
    }
};

struct U1 
{
    const size_t N_c = 1;

    std::complex<double> a;

    U1() : a(1.) {}
}