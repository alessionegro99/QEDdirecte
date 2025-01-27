#include <iostream>

#include "../include/parameters.hpp"

void geometry::lexToCart(std::vector<int> &cart_coord, long lex)
{
    long aux[ST_DIM];

    aux[0] = 1;
    for (int i = 1; i < ST_DIM; i++)
    {
        aux[i] = aux[i - 1] * d_size[i - 1];
    }
    // aux[0]=1
    // aux[1]=size[0]
    // aux[2]=size[0]*size[1]
    // ...
    // aux[STDIM-1]=size[0]*size[1]*...*size[STDIM-2]
    for (int i = (ST_DIM - 1); i >= 0; i--) // CAREFUL: DO NOT use size_t i
    {
        cart_coord[i] = (int)(lex / aux[i]);
        lex -= aux[i] * cart_coord[i];
    }
}

int geometry::cartToLex(std::vector<int> cart_coord)
{
    long res, aux;

    res = 0;
    aux = 1;

    for (size_t i = 0; i < ST_DIM; i++)
    {
        res += cart_coord[i] * aux;
        aux *= d_size[i];
    }

    // res = cart_coord[0]
    //      +cart_coord[1]*size[0]
    //      +cart_coord[2]*size[0]*size[1]
    //      +...
    //      +cart_coord[STDIM-1]*size[0]*size[1]*...*size[STDIM-2]

    return res;
}

void geometry::printAll()
{
    std::cout << "##################################" << "\n";
    std::cout << "Geometry related parameters : " << "\n";
    std::cout << "spacetime dimension = " << ST_DIM << "\n";
    std::cout << "temporal extent = " << T << "\n";
    std::cout << "spatial extent = " << L << "\n";
    std::cout << "total volume = " << d_vol << "\n";
    std::cout << "spatial volume = " << d_space_vol << std::endl;
    std::cout << "inverse total volume = " << d_inv_vol << "\n";
    std::cout << "spatial volume = " << d_inv_space_vol << std::endl;
    std::cout << "##################################" << "\n";
}

void geometry::initGeometry()
{
    int j, value, valuep, valuem;
    long r, rm, rp;
    std::vector<int> cart_coord(ST_DIM);

    // intializing fundamental and derived geometrical quantities
    d_size.push_back(T);
    for (int i = 1; i < ST_DIM; ++i)
    {
        d_size.push_back(L);
    }

    d_vol = 1;
    for (int i = 0; i < ST_DIM; ++i)
    {
        d_vol *= d_size[i];
    }

    d_space_vol = 1;
    for (int i = 1; i < ST_DIM; ++i) // direction 0 is time
    {
        d_space_vol *= d_size[i];
    }

    d_inv_vol = 1.0 / ((double)d_vol);
    d_inv_space_vol = 1.0 / ((double)d_space_vol);

    // allocating memory
    d_nnp = new size_t *[d_vol];
    if (!d_nnp)
    {
        std::cerr << "Failed to allocate memory for d_nnp rows.\n";
    }
    for (r = 0; r < d_vol; r++)
    {
        d_nnp[r] = new size_t[ST_DIM];
        if (!d_nnp[r])
        {
            std::cerr << "Failed to allocate memory for d_nnp columns at row " << r << ".\n";

            for (size_t j = 0; j < r; j++)
            {
                delete[] d_nnp[j];
            }
            delete[] d_nnp;
        }
    }

    d_nnm = new size_t *[d_vol];
    if (!d_nnm)
    {
        std::cerr << "Failed to allocate memory for d_nnm rows.\n";
    }
    for (r = 0; r < d_vol; r++)
    {
        d_nnm[r] = new size_t[ST_DIM];
        if (!d_nnm[r])
        {
            std::cerr << "Failed to allocate memory for d_nnm columns at row " << r << ".\n";

            for (size_t j = 0; j < r; j++)
            {
                delete[] d_nnm[j];
            }
            delete[] d_nnm;
        }
    }

    // initializing
    for (r = 0; r < d_vol; r++)
    {
        lexToCart(cart_coord, r);

        for (j = 0; j < ST_DIM; j++)
        {
            value = cart_coord[j];

            valuep = value + 1;
            // implementing PBC in positive direction
            if (valuep >= d_size[j])
            {
                valuep -= d_size[j];
            }
            cart_coord[j] = valuep;
            rp = cartToLex(cart_coord);
            d_nnp[r][j] = rp;

            valuem = value - 1;
            // implementing PBC in negative direction
            if (valuem < 0)
            {
                valuem += d_size[j];
            }
            cart_coord[j] = valuem;
            rm = cartToLex(cart_coord);
            d_nnm[r][j] = rm;

            cart_coord[j] = value;
        }
    }
}

void geometry::freeGeometry()
{
    long r;

    for (r = 0; r < d_vol; ++r)
    {
        delete[] d_nnp[r];
    }
    delete[] d_nnp;

    for (r = 0; r < d_vol; ++r)
    {
        delete[] d_nnm[r];
    }
    delete[] d_nnm;
}