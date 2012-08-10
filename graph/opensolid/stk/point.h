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

#ifndef point_H
#define point_H

#include "vector.h"

//! Homogeneous point in 4 space. Represented as position vector.

namespace stk
{

class point : public stk::vector<4>
{
    public:

        point();

        point ( double x, double y, double z, double w );
        point ( double x, double y, double z );

        double x() const; //!< Get x component of point.
        double y() const; //!< Get y component of point.
        double z() const; //!< Get z component of point.
        double w() const; //!< Get w component of point.

        void x ( double ); //!< Set x component of point.
        void y ( double ); //!< Set y component of point.
        void z ( double ); //!< Set z component of point.
        void w ( double ); //!< Set w component of point.

        void components ( double x, double y, double z, double w );

        void homogenise(); //!< Project from R4 into R3.

        void operator += ( const stk::vector<3>& vect ); //!< Add a vector3 to this point.
};

}

#endif
