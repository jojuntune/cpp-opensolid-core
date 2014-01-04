/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
*  ian.e.mackenzie@gmail.com                                                        *
*                                                                                   *
*  This library is free software; you can redistribute it and/or                    *
*  modify it under the terms of the GNU Lesser General Public                       *
*  License as published by the Free Software Foundation; either                     *
*  version 2.1 of the License, or (at your option) any later version.               *
*                                                                                   *
*  This library is distributed in the hope that it will be useful,                  *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
*  Lesser General Public License for more details.                                  *
*                                                                                   *
*  You should have received a copy of the GNU Lesser General Public                 *
*  License along with this library; if not, write to the Free Software              *
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
*                                                                                   *
************************************************************************************/

#include <OpenSolid/Core/Matrix.hpp>

namespace opensolid
{
    const double
    Matrix3d::determinant() const {
        double a11 = component(0);
        double a21 = component(1);
        double a31 = component(2);
        double a12 = component(3);
        double a22 = component(4);
        double a32 = component(5);
        double a13 = component(6);
        double a23 = component(7);
        double a33 = component(8);

        return a11 * (a22 * a33 - a23 * a32) -
            a12 * (a21 * a33 - a23 * a31) +
            a13 * (a21 * a32 - a22 * a31);
    }

    const Matrix3d
    Matrix3d::inverse() const {
        double a11 = component(0);
        double a21 = component(1);
        double a31 = component(2);
        double a12 = component(3);
        double a22 = component(4);
        double a32 = component(5);
        double a13 = component(6);
        double a23 = component(7);
        double a33 = component(8);

        double determinant = a11 * (a22 * a33 - a23 * a32) -
            a12 * (a21 * a33 - a23 * a31) +
            a13 * (a21 * a32 - a22 * a31);
        if (determinant == Zero()) {
            assert(false);
            return Matrix3d();
        }
        double reciprocal = 1.0 / determinant;

        return Matrix3d(
            reciprocal * (a22 * a33 - a23 * a32),
            reciprocal * (a13 * a32 - a12 * a33),
            reciprocal * (a12 * a23 - a13 * a22),
            reciprocal * (a23 * a31 - a21 * a33),
            reciprocal * (a11 * a33 - a13 * a31),
            reciprocal * (a13 * a21 - a11 * a23),
            reciprocal * (a21 * a32 - a22 * a31),
            reciprocal * (a12 * a31 - a11 * a32),
            reciprocal * (a11 * a22 - a12 * a21)
        );
    }
}
