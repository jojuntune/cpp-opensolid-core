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

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "point.h"
#include "vector3.h"
#include "matrix_4x4.h"

namespace stk // Scott's Toolkit.
{

class transform : public matrix_4x4
{
    public:

        transform();

        transform ( double* matrix ); //!< Copy matrix into transform.

        //! Multiply translation matrix to transform matrix.
        void translate ( double x, double y, double z, bool pre = false );

        void rotateX ( double angle, bool pre = false ); //!< Rotate about +ve x axis.
        void rotateY ( double angle, bool pre = false ); //!< Rotate about +ve y axis.
        void rotateZ ( double angle, bool pre = false ); //!< Rotate about +ve z axis
        
        //! Rotation wrapper function.
        void rotate ( double angle, point& axisStart, point& axisEnd, bool pre = false);
        //! Rotate about an arbitrary axis.
        void rotate ( double angle, point& axisStart, vector3& axisDirection );

        //! Multiply scaling to transform matrix.
        void scale ( double x, double y, double z, point relTo, bool pre = false );
        //! Multiply scaling to transform matrix.
        void scale ( double x, double y, double z, bool pre = false );
        
        //! Generate transform that will align vector1 to vector2
        void align ( vector3& vector1, vector3& vector2, bool pre = false );

        void apply ( point* pt ); //!< Apply transform to point.
        void apply ( point& pt ); //!< Apply transform to point.
        void apply ( vector3& vect ); //!< Apply transform to a vector treated as a point.

    protected:

        void translateIdent ( double x, double y, double z ); //!< Setup underlying matrix as translation identity.

        //! Create rotation identity for rotation about x axis
        void rotateXIdent ( double yy, double yz, double zy, double zz );
        //! Create rotation identity for rotation about y axis
        void rotateYIdent ( double xx, double xz, double zx, double zz );
        //! Create rotation identity for rotation about z axis
        void rotateZIdent ( double xx, double xy, double yx, double yy );

        //! Create scaling identity for scaling operation.
        void scaleIdent ( double x, double y, double z );
        
    private:
    
        void apply ( double* elements ); //!< Apply transform to elements of a vector or point.
};

}

#endif
