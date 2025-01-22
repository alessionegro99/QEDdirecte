#pragma once

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <cmath>

class allParameters
{
private:
    std::unordered_map<std::string, std::string> all_parameters;

public:
    // Constructor to load parameters from the file
    explicit allParameters(const std::string &filename)
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
            all_parameters[key] = value;
        }

        file.close();
    }

    // Getter function that returns the value of a parameter as a string
    std::string getString(const std::string &key) const
    {
        auto it = all_parameters.find(key);
        if (it == all_parameters.end())
        {
            throw std::runtime_error("Error: Parameter '" + key + "' not found.");
        }
        return it->second;
    }

    // Getter function that returns the value as an int
    int getInt(const std::string &key) const
    {
        return std::stoi(getString(key)); // Convert the string value to int
    }

    // Getter function that returns the value as a double
    double getDouble(const std::string &key) const
    {
        return std::stod(getString(key)); // Convert the string value to double
    }

    // Function to display all parameters
    void display() const
    {
        for (const auto &pair : all_parameters)
        {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }
};

class physicalParameters
{
private:
    const allParameters &all_parameters;

public:
    explicit physicalParameters(const allParameters &physical_parameters)
        : all_parameters(physical_parameters) {}

    size_t getST_DIM() const
    {
        return static_cast<size_t>(all_parameters.getInt("ST_DIM"));
    }

    size_t getT() const
    {
        return static_cast<size_t>(all_parameters.getInt("T"));
    }

    size_t getL() const
    {
        return static_cast<size_t>(all_parameters.getInt("L"));
    }

    size_t getSeed() const
    {
        return static_cast<size_t>(all_parameters.getInt("seed"));
    }

    size_t spatialVolume() const
    {
        const size_t ST_DIM = getST_DIM();
        const size_t L = getL();
        return static_cast<size_t>(std::pow(L, ST_DIM - 1));
    }

    size_t totalVolume() const
    {
        return spatialVolume() * getT();
    }
};