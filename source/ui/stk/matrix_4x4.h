// Copyright 2004 Scott A.E. Lanham.
// ---------------------------------
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <iostream>
#include <cmath>
    
using namespace std;

namespace stk
{

//! 4x4 Matrix of doubles

class matrix_4x4
{
    // Matrix optimised for size 4 X 4 of double

    public:

        matrix_4x4();

        void ident(); //!< Set matrix to identity

        void multiply ( matrix_4x4&, bool pre = false ); //!< multiply this matrix by given matrix
        
        double* elements();

        void print();  //!< Print matrice to standard out.

    protected:

        double*      element;  // Primary matrix data.
        double*      scratch;  // Scratch space for matrix multiplication etc.
        
    private:
    
        double      store1[ 16 ]; // OpenGL style 2D arrays ( column major ). NOT c/c++.
        double      store2[ 16 ]; // Data is not forced to be on heap.
};

}

#endif
