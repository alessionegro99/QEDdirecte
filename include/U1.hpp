#pragma once

#include <iostream>
#include <complex>
#include <cmath>

// struct for U1 group elements
// exp{i\theta} with -pi<\theta<pi
struct U1
{
    std::complex<double> a;

    U1() : a(1.) {} // needed for dynamical allocation of memory for 2D arrays

    U1(double theta) : a(std::polar(1.0, theta)) {}

    double phase() const;
    double module() const;

    U1 dag() const;
    U1 operator*(const U1 &other) const;

    std::complex<double> operator+(const U1 &other) const;
    std::complex<double> operator-(const U1 &other) const;
};

std::complex<double> &operator+=(std::complex<double> &lhs, const U1 &rhs);