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

#include "transform.h"

#include <cmath>
using namespace std;

namespace stk // Scott's Toolkit.
{

transform::transform()
    : matrix_4x4()
{
    ident();
}

transform::transform ( double* matrix )
    : matrix_4x4()
{
    //! @par Notes Expects OpenGL style array NOT c/c++ style.

    for ( int index = 0; index < 16; index ++ )
        element [ index ] = matrix [ index ];
}

void transform::translate ( double x, double y, double z, bool pre )
{
    //! @param x Translate in x direction.
    //! @param y Translate in y direction.
    //! @param z Translate in z direction.
    //! @param pre Pre multiply instead of post multiply to existing transformation matrix.

    if ( x == 0.0 && y == 0.0 && z == 0.0 ) return;

    // Construct translation matrix.

    transform tmpTransform;

    tmpTransform.translateIdent ( x, y, z );

    // Multiply it to current transform matrix.

    multiply ( tmpTransform, pre );
}

void transform::rotateX ( double angle, bool pre )
{
    //! @param angle Rotation angle in radians.
    //! @param pre Pre multiply instead of post multiply to existing transformation matrix.

    transform tmpTransform;

    tmpTransform.rotateXIdent ( cos ( angle ), - sin ( angle), sin ( angle ), cos ( angle ) );

    // Multiply it to current transform matrix.

    multiply ( tmpTransform, pre );
}

void transform::rotateY ( double angle, bool pre )
{
    //! @param angle Rotation angle in radians.
    //! @param pre Pre multiply instead of post multiply to existing transformation matrix.

    transform tmpTransform;

    tmpTransform.rotateYIdent ( cos ( angle ), sin ( angle), - sin ( angle ), cos ( angle ) );

    // Multiply it to current transform matrix.

    multiply ( tmpTransform, pre );
}

void transform::rotateZ ( double angle, bool pre )
{
    //! @param angle Rotation angle in radians.
    //! @param pre Pre multiply instead of post multiply to existing transformation matrix.

    transform tmpTransform;

    tmpTransform.rotateZIdent ( cos ( angle ), - sin ( angle), sin ( angle ), cos ( angle ) );

    // Multiply it to current transform matrix.

    multiply ( tmpTransform, pre );
}

void transform::rotate ( double angle, point& axisStart, point& axisEnd, bool pre )
{
    //! @param pre Pre multiply instead of post multiply to existing transformation matrix.
    
    vector3 axisDirection ( axisStart, axisEnd );
    
    transform tmpTransform;
    
    tmpTransform.rotate ( angle, axisStart, axisDirection );
    
    multiply ( tmpTransform, pre );
}

void transform::rotate ( double angle, point& axisStart, vector3& axisDirection )
{
    //! @param angle Angle to rotate about axis in radians.
    //! @param axisStart Start of axis.
    //! @param axisDirection Vector describing rotation axis.
    //! @par Notes:  Assumes axisStart and axisEnd have been normalised.
    //!              Only works if transform initialised to ident.

    transform   tmpTransform;

    vector3 vect ( axisDirection );
    vect.normalise();

    // Move axis to origin
    translate ( - axisStart.x(), - axisStart.y(), - axisStart.z(), true );

    if ( vect.y() == 0.0 && vect.z() == 0.0 )
    {
        // Just a rotation about the x axis.
        
        if ( vect.x() > 0.0 )
            rotateX ( angle, true );
        else
            rotateX ( - angle, true );
    }
    else if ( vect.x() == 0.0 && vect.z() == 0.0 )
    {
        // Just a rotation about the Y axis.
        
        if ( vect.y() > 0.0 )
            rotateY ( angle, true );
        else
            rotateY ( - angle, true );
    }
    else if ( vect.x() == 0.0 && vect.y() == 0.0 )
    {
        // Just a rotation about the z axis.
        
        if ( vect.z() > 0.0 )
            rotateZ ( angle, true );
        else
            rotateZ ( - angle, true );
    }
    else
    {
        // Rotate about x axis to yz plane.
        double projHyp = sqrt ( vect.y() * vect.y() + vect.z() * vect.z() );

        double sinRotX = vect.y() / projHyp;
        double cosRotX = vect.z() / projHyp;

        tmpTransform.rotateXIdent ( cosRotX, - sinRotX, sinRotX, cosRotX );
        multiply ( tmpTransform, true );

        // Rotate about y axis to z axis.
        double sinRotY = - ( vect.x() );
        double cosRotY = projHyp;

        tmpTransform.rotateYIdent ( cosRotY, sinRotY, - sinRotY, cosRotY );
        multiply ( tmpTransform, true );

        // Rotate about z axis.
        rotateZ ( angle, true );

        // Inverse rotation about y axis. ie Rotate back into yz plane. Negate angle of rotation.
        tmpTransform.rotateYIdent ( cosRotY, - sinRotY, sinRotY, cosRotY );
        multiply ( tmpTransform, true );

        // Inverse rotation about x axis.
        tmpTransform.rotateXIdent ( cosRotX, sinRotX, - sinRotX, cosRotX );
        multiply ( tmpTransform, true );
    }

    // Inverse translation.
    translate ( axisStart.x(), axisStart.y(), axisStart.z(), true );
}

void transform::scale ( double x, double y, double z, point relTo, bool pre )
{
    //! @param x Scaling factor in x direction.
    //! @param x Scaling factor in y direction.
    //! @param x Scaling factor in z direction.
    //! @param relTo Scaling is relative to this point.
    //! @param pre Pre multiply instead of post multiply to existing transformation matrix.
    
    transform   matrix;
    transform   step;

    bool isRelTo = ( relTo.x() != 0.0 || relTo.y() != 0.0 || relTo.z() != 0.0 );

    if ( isRelTo ) relTo.homogenise();

    matrix.ident();

    if ( isRelTo )
    {
        step.translateIdent ( - ( relTo.x() ), - ( relTo.y() ), - ( relTo.z() ) );

        matrix.multiply ( step, true );
    }

    step.scaleIdent ( x, y, z );

    matrix.multiply ( step, true );

    // Translate back again.
    if ( isRelTo )
    {
        step.translateIdent ( relTo.x(), relTo.y(), relTo.z() );

        matrix.multiply ( step, true );
    }

    multiply ( matrix, pre );
}

void transform::scale ( double x, double y, double z, bool pre )
{
    //! @param x Scaling factor in x direction.
    //! @param x Scaling factor in y direction.
    //! @param x Scaling factor in z direction.
    //! @param pre Pre multiply instead of post multiply to existing transformation matrix.

    point tmpPt ( 0.0, 0.0, 0.0, 1.0 );

    scale ( x, y, z, tmpPt, pre );

}

void transform::align ( vector3& vector1, vector3& vector2, bool pre )
{
    //! @param vector1 Vector to align.
    //! @param vector2 Vector to align vector 1 to.
    //! @param pre Pre multiply instead of post multiply to existing transformation matrix.
    //!
    //! @par Notes   Can be used for transforming coordinate systems.
    //!              Rotates vector1 about normal to plane described by vector1 and vector2.
    
    // Get angle to rotate through.
    double rotAngle = vector1.angle ( vector2 );

    if ( rotAngle == 0.0 ) return;
    
    // Generate normal to both vectors.
    vector3 normal;
    normal.crossProduct ( vector1, vector2 );
    
    transform tmpTransform;
    
    point origin ( 0.0, 0.0, 0.0 );
        
    // Rotate about normal.
    if ( ( rotAngle != 0.0 ) && ( ! normal.isNull() ) )
        tmpTransform.rotate ( rotAngle, origin, normal );    
    
    multiply ( tmpTransform, pre );
}

void transform::apply ( point* pt )
{
    //! @param pt Point to apply transform to.
    
    apply ( pt -> elements );
}

void transform::apply ( point& pt )
{
    //! @param pt Point to apply transform to.

    apply ( pt.elements );
}

void transform::apply ( vector3& vect )
{
    //! @par Notes To transform a vector3 it is treated as a point generated by adding the vector to the origin.

    // This is done for speed and _not_ OO correctness.
    
    double tmpElements[ 4 ];

    for ( int index = 0; index < 3; index ++ ) tmpElements[ index ] = vect.elements[ index ];

    tmpElements[ 3 ] = 1.0; // Treat as homogenised point.

    apply ( tmpElements );

    for ( int index = 0; index < 3; index ++ ) vect.elements[ index ] = tmpElements[ index ];
}

void transform::translateIdent ( double x, double y, double z )
{
    ident();

    element [ 12 ] = x;
    element [ 13 ] = y;
    element [ 14 ] = z;
}


void transform::rotateXIdent ( double yy, double yz, double zy, double zz )
{
    //! @param yy y coordinate scalar for new y.
    //! @param yz z coordinate scalar for new y.
    //! @param zy y coordinate scalar for new z.
    //! @param zz z coordinate scalar for new z.

    ident();

    element [ 5 ] = yy;
    element [ 9 ] = yz;
    element [ 6 ] = zy;
    element [ 10 ] = zz;
}

void transform::rotateYIdent ( double xx, double xz, double zx, double zz )
{
    //! @param xx x coordinate scalar for new x.
    //! @param xz z coordinate scalar for new x.
    //! @param zx x coordinate scalar for new z.
    //! @param zz z coordinate scalar for new z.

    ident();

    element [ 0 ] = xx;
    element [ 8 ] = xz;
    element [ 2 ] = zx;
    element [ 10 ] = zz;
}

void transform::rotateZIdent ( double xx, double xy, double yx, double yy )
{
    //! @param xx x coordinate scalar for new x.
    //! @param xy y coordinate scalar for new x.
    //! @param yx x coordinate scalar for new y.
    //! @param yy y coordinate scalar for new y.

    ident();

    element [ 0 ] = xx;
    element [ 4 ] = xy;
    element [ 1 ] = yx;
    element [ 5 ] = yy;
}

void transform::scaleIdent ( double x, double y, double z )
{
    //! @param x x scaling factor.
    //! @param y y scaling factor.
    //! @param z z scaling factor.

    ident();

    element [ 0 ] = x;
    element [ 5 ] = y;
    element [ 10 ] = z;
}

void transform::apply ( double* elements )
{
    //! @param elements Array of 4 doubles to apply transform to.
    
    double* ptArray = elements;

    double  tmpPt [ 4 ] = { 0.0, 0.0, 0.0, 0.0 };
    double  cVal;

    int     mRow;
    int     mIndex = 0;

    for ( int ptRow = 0; ptRow < 4; ptRow ++ )
    {
        cVal =  ptArray [ ptRow ];

        for ( mRow = 0; mRow < 4; mRow ++ )
        {
            tmpPt [ mRow ] += cVal * element [ mIndex ++ ];
        }
    }
    
    for ( int index = 0; index < 4; index ++ )
        elements [ index ] = tmpPt [ index ];
}

} // namespace stk

