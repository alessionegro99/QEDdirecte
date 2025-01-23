#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <unordered_map>
#include <stdexcept>


// generic container for all of the parameters read from the input file
class allParams
{
private:
    std::unordered_map<std::string, std::string> p;

public:
    explicit allParams(const std::string &filename)
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

// physical parameters
class physParams
{
public:
    const size_t ST_DIM;
    const size_t T;
    const size_t L;
    const size_t spatial_vol;
    const size_t tot_vol;

    explicit physParams(const allParams &p) : ST_DIM(p.getInt("ST_DIM")),
                                              T(p.getInt("T")),
                                              L(p.getInt("L")),
                                              spatial_vol(static_cast<size_t>(std::pow(L, ST_DIM - 1))),
                                              tot_vol(spatial_vol * T)

    {
    }
};

// simulation parameters
class simParams
{
public:
    const size_t seed;
    const std::string start;

    simParams(const allParams &p) : seed(p.getInt("seed")),
                                    start(p.getString("start"))
    {
    }
};