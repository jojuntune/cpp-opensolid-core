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

#ifndef vector3_H
#define vector3_H

#include "point.h"
#include "vector.h"

namespace stk
{

//! Vector in 3 space.

class vector3 : public stk::vector<3>
{
    public:

        virtual ~vector3();
    
        vector3();

        vector3 ( double i, double j, double k );

        vector3 ( const point& start, const point& end );

        virtual void generate ( const point& start, const point& end ); //!< Generate vector from start and end points.

        double x() const;
        double y() const;
        double z() const;

        void components ( double i, double j, double k );
    
        void crossProduct ( vector3& v1, vector3& v2 ); //!< Calculate cross product of v1 X v2.

        double angle ( vector3& vect ); //!< Calculate angle between this vector and vect.

        void projectXZ();  //!< Project onto the X-Z plane.        
        void projectXY();  //!< Project onto the X-Y plane.
        void projectYZ();  //!< Project onto the Y-Z plane.
};

}

#endif
