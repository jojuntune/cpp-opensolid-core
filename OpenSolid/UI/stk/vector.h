// Copyright 2007 Scott Lanham.
// ----------------------------
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

#ifndef VECTOR_H
#define VECTOR_H

#include "config.hpp"

namespace stk // Scott's Toolkit.
{

template< int D > class vector
{
    public:

        vector();
    
        int dimension() { return D; };

        double lengthSqrd(); //!< Length of vector squared.
        double length(); //!< Length of vector.

        void normalise(); //!< Convert this vector into a unit vector.

        double dot ( vector<D>& vect ); //!< Dot product of two vectors.

        bool isNull();

        void operator += ( vector<D>& vect ); //!< Add another vector to this one.
        void operator -= ( vector<D>& vect ); //!< Subtract another vector from this one.
        void operator *= ( double ); //!< Multiply this vector by a scalar.

        double elements[ D ];

    private:

        void diff ( vector<D>& vect1, vector<D>& vect2 );
};

template< int D > vector<D>::vector()
{
    for ( int index = 0; index < D; index ++ )
        elements[ index ] = 0.0;
}

template< int D > double vector<D>::lengthSqrd()
{
    //! @return length of this vector squared

    double sum = 0;

    for ( int index = 0; index < D; index ++ )
        sum += elements [ index ] * elements [ index ];
        
    return sum;
}

template< int D > double vector<D>::length()
{
    //! @return length of this vector

    return sqrt ( lengthSqrd() );
}

template< int D > void vector<D>::normalise()
{
    double len = length();

    for ( int index = 0; index < D; index ++ )
        elements [ index ] /= len;
}

template< int D > double vector<D>::dot ( vector<D>& vect )
{
    //! @param vect Other vector as part of dot product.

    double prod = 0.0;

    for ( int index = 0; index < D; index ++ )
    {
        prod += elements [ index ] * vect.elements [ index ];
    }

    return prod;
}

template< int D > bool vector<D>::isNull()
{
    //! @return True if all elements of vector are 0.

    bool retVal = true;

    for ( int index = 0; index < D; index ++ )
    {
        if ( elements[ index ] != 0.0 ) retVal = false;
    }

    return retVal;
}

template< int D > void vector<D>::operator += ( vector<D>& vect )
{
    //! @param vect Vector to add from this.
    
    for ( int index = 0; index < D; index ++ )
    {
        elements[ index ] += vect.elements[ index ];
    }
}

template< int D > void vector<D>::operator -= ( vector<D>& vect )
{
    //! @param vect Vector to subtract from this.
    
    for ( int index = 0; index < D; index ++ )
    {
        elements[ index ] -= vect.elements[ index ];
    }
}

template< int D > void vector<D>::operator *= ( double scalar )
{
    //! @param scalar Scalar to multiply vector by.

    for ( int index = 0; index < D; index ++ )
        elements [ index ] *= scalar;
}

// Private

template< int D > void vector<D>::diff ( vector<D>& vect1, vector<D>& vect2 )
{
    //! @param vect1 Vector to subtract.
    //! @param vect2 Vector to subtract from.
    
    for ( int index = 0; index < D; index ++ )
    {
        elements[ index ] = vect2.elements[ index ] - vect1.elements[ index ];
    }
}

} // namespace stk

#endif

