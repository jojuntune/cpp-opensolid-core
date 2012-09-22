// Copyright 2007 Scott A.E. Lanham.
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

#include "point.h"

namespace stk
{

point::point(){}

point::point ( double x, double y, double z, double w )
{
    elements[ 0 ] = x;
    elements[ 1 ] = y;
    elements[ 2 ] = z;
    elements[ 3 ] = w;
}

point::point ( double x, double y, double z )
{
    elements[ 0 ] = x;
    elements[ 1 ] = y;
    elements[ 2 ] = z;
    elements[ 3 ] = 1.0;
}

double point::x() const
{
    return elements[ 0 ];
}

double point::y() const
{
    return elements[ 1 ];
}

double point::z() const
{
    return elements[ 2 ];
}

double point::w() const
{
    return elements[ 3 ];
}

void point::x ( double val )
{
    elements[ 0 ] = val;
}

void point::y ( double val )
{
    elements[ 1 ] = val;
}

void point::z ( double val )
{
    elements[ 2 ] = val;
}

void point::w ( double val )
{
    elements[ 3 ] = val;
}

void point::components ( double x, double y, double z, double w )
{
    elements[ 0 ] = x;
    elements[ 1 ] = y;
    elements[ 2 ] = z;
    elements[ 3 ] = w;
}

void point::homogenise()
{
    if ( elements[ 3 ] == 1.0 ) return;

    double w = elements[ 3 ];
    
    elements[ 0 ] = elements[ 0 ] / w;
    elements[ 1 ] = elements[ 1 ] / w;
    elements[ 2 ] = elements[ 2 ] / w;
}

void point::operator += ( const stk::vector<3>& vect )
{
    //! @param vect Vector to add to this point.
    //! @par Notes This point is homogeneous which must be taken into account when adding a 3D vector to it.
    
    for ( int index = 0; index < 3; index ++ )
    {
        double w = elements[ 3 ];
        elements[ index ] += ( vect.elements[ index ] * w );
    }
}

}
