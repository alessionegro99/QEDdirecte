#include "U1.hpp"

// member function(s)
double U1::phase() const
{
    return std::arg(a);
}

double U1::module() const
{
    return std::abs(a);
}

U1 U1::dag() const
{
    return U1(-std::arg(a));
}

U1 U1::operator*(const U1 &other) const
{
    return U1(std::arg(a) + std::arg(other.a));
}

U1 &U1::operator*=(const U1 &other)
{
    a *= other.a;
    return *this;
}

std::complex<double> U1::operator+(const U1 &other) const
{
    return a + other.a;
}

std::complex<double> U1::operator-(const U1 &other) const
{
    return a - other.a;
}

// non member function(s)

std::complex<double> &operator+=(std::complex<double> &lhs, const U1 &rhs)
{
    lhs += rhs.a;
    return lhs;
}

std::complex<double> operator*(const U1 &u1, const std::complex<double> &z)
{
    return u1.a * z;
}

std::complex<double> operator*(const std::complex<double> &z, const U1 &u1)
{
    return z * u1.a;
}