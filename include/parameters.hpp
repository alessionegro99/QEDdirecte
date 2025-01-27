#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <unordered_map>
#include <stdexcept>

// generic container for all of the parameters read from the input file
class parameters
{
private:
    std::unordered_map<std::string, std::string> p;

public:
    explicit parameters(const std::string &filename)
    {
        loadFromFile(filename);
    }

    // Function to load parameters from the file
    void loadFromFile(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Error: Cannot open file " + filename);
        }

        std::string key, value;
        while (file >> key >> value)
        {
            p[key] = value;
        }

        file.close();
    }

    std::string getString(const std::string &key) const
    {
        auto it = p.find(key);
        if (it == p.end())
        {
            throw std::runtime_error("Error: Parameter '" + key + "' not found.");
        }
        return it->second;
    }

    int getInt(const std::string &key) const
    {
        return std::stoi(getString(key)); // string to int
    }

    double getDouble(const std::string &key) const
    {
        return std::stod(getString(key)); // string to double
    }

    void display() const
    {
        for (const auto &pair : p)
        {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }
};

// simulation parameters
class simulation
{
public:
    const size_t seed;
    const std::string start;

    simulation(const parameters &p) : seed(p.getInt("seed")),
                                      start(p.getString("start"))
    {
    }
};

// geometry of the lattice
class geometry
{
public:
    const size_t ST_DIM; // total Euclidean spacetime dimension
    const size_t T;      // temporal extent of the lattice, coordinate: $x_0$
    const size_t L;      // spatial extent of the lattice, coordinates: $x_i \in \{1,2,...,ST_DIM-1}\$

    std::vector<size_t> d_size; // size of the lattice

    size_t d_vol;           // total volume
    double d_inv_vol;       // 1/(total volume)
    size_t d_space_vol;     // spatial component of the volume
    double d_inv_space_vol; // 1/(spatial volume)

    size_t **d_nnp; // d_nnp[r][i] = next neighbour (on the local lattice) in dir +i of site r
    size_t **d_nnm; // d_nnm[r][i] = next neighbour (on the local lattice) in dir -i of site r

    explicit geometry(const parameters &p) : ST_DIM(p.getInt("ST_DIM")),
                                             T(p.getInt("T")),
                                             L(p.getInt("L"))
    {
        initGeometry();
    }

    inline long nnp(long r, int i) const
    {
        return d_nnp[r][i];
    }
    inline long nnm(long r, int i) const
    {
        return d_nnm[r][i];
    }

    void lexToCart(std::vector<int> &cart_coord, long lex);
    int cartToLex(std::vector<int> cart_coord);

    void printAll();
    void initGeometry();
    void freeGeometry();
};
