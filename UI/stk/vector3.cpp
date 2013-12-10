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

#include "vector3.h"

#include <cmath>
using namespace std;

namespace stk
{

vector3::~vector3()
{
}

vector3::vector3()
{
}

vector3::vector3 ( double i, double j, double k )
{
    elements[ 0 ] = i;
    elements[ 1 ] = j;
    elements[ 2 ] = k;
}

vector3::vector3 ( const point& start, const point& end )
{
    //! @param start Starting point of vector.
    //! @param end Ending point of vector.

    generate ( start, end );
}

void vector3::generate ( const point& start, const point& end )
{
    //! @param start Starting point of vector.
    //! @param end Ending point of vector.

    //! Point is homogeneous. This vector is not in projective space so make sure points
    //! are homogenised.

    point startPt ( start );
    point endPt ( end );

    startPt.homogenise();
    endPt.homogenise();

    for ( int index = 0; index < 3; index ++ )
        elements [ index ] = endPt.elements [ index ] - startPt.elements [ index ];
}

double vector3::x() const
{
    return elements[ 0 ];
}

double vector3::y() const
{
    return elements[ 1 ];
}

double vector3::z() const
{
    return elements[ 2 ];
}

void vector3::components ( double i, double j, double k )
{
    elements[ 0 ] = i;
    elements[ 1 ] = j;
    elements[ 2 ] = k;
}

void vector3::crossProduct ( vector3& v1, vector3& v2 )
{
    //! @par Notes Stores result in this vector.

    elements [ 0 ] = ( v1.elements [ 1 ] * v2.elements [ 2 ] ) -
                     ( v1.elements [ 2 ] * v2.elements [ 1 ] );

    elements [ 1 ] = ( v1.elements [ 2 ] * v2.elements [ 0 ] ) -
                     ( v1.elements [ 0 ] * v2.elements [ 2 ] );

    elements [ 2 ] = ( v1.elements [ 0 ] * v2.elements [ 1 ] ) -
                     ( v1.elements [ 1 ] * v2.elements [ 0 ] );
}

double vector3::angle ( vector3& vect )
{
    //! @param vect Vector to compare this vector to.
    //! @return Value between 0 and PI in radians.

    double cos_angle = dot ( vect ) / ( length() * vect.length() );

    if ( cos_angle > 1.0 )
        cos_angle = 1.0;
    else if ( cos_angle < -1.0 )
        cos_angle = -1.0;
    
    return acos ( cos_angle );
}

void vector3::projectXZ()
{
    elements [ 1 ] = 0.0;  // y = 0.
}

void vector3::projectXY()
{
    elements [ 2 ] = 0.0;  // z = 0.    
}

void vector3::projectYZ()
{
    elements [ 0 ] = 0.0;    
}

}
