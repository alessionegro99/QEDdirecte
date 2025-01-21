#pragma once

struct U1
{
    std::complex<double> value;

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
        std::cout << "U(1) element: " << value << std::endl;
    }
};