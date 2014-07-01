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

#include "matrix_4x4.h"

namespace stk
{

matrix_4x4::matrix_4x4()
{
    element = store1;
    scratch = store2;
}

void matrix_4x4::ident()
{
    for ( int index = 0; index < 16; index ++ )
    {
        element [ index ] = 0;
    }

    element [ 0 ] = 1.0;
    element [ 5 ] = 1.0;
    element [ 10 ] = 1.0;
    element [ 15 ] = 1.0;
}

void matrix_4x4::multiply ( matrix_4x4& multMatrix, bool pre )
{
    //! @param multMatrix Matrix to multiply.
    //! @param pre If true then pre multiply.

    double      cVal;

    double*     multA;
    double*     multB;

    int         pIndex = 0;  // Primary Index.
    int         pRow, sRow;
    int         sIndex = 0;  // Scratch Index.
    int         multAIndex;  // Multiplier A matrix index.

    // Multiply AB
    if ( pre )
    {
        // Pre multiply.
        multA = multMatrix.element;
        multB = element;
    }
    else
    {
        // Post multiply.
        multA = element;
        multB = multMatrix.element;
    }

    // Zero scratch space
    for ( int index = 0; index < 16; index ++ ) scratch [ index ] = 0.0;

    for ( int pCol = 0; pCol < 4; pCol ++ )
    {
        multAIndex = 0;

        for ( pRow = 0; pRow < 4; pRow ++ )
        {
            cVal = multB [ pIndex ++ ];

            for ( sRow = 0; sRow < 4; sRow ++ )
            {
                scratch [ sIndex + sRow ] += cVal * multA [ multAIndex ++ ];
            }
        }

        sIndex += 4;
    }

    // Swap scratch and element matrices.
    multA = element;  // multA is simply used as a temp variable.
    element = scratch;
    scratch = multA;
}

double* matrix_4x4::elements()
{
    return element;
}

void matrix_4x4::print()
{
    for ( int row = 0; row < 4; row ++ )
    {
        for ( int col = 0; col < 4; col ++ )
        {
            cout << element [ row + ( col * 4 ) ] << "  ";
        }

        cout << "\n";
    }
}

}
