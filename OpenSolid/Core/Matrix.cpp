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
    template <>
    double
    Matrix3x3::determinant() const {
        double a00 = component(0);
        double a10 = component(1);
        double a20 = component(2);
        double a01 = component(3);
        double a11 = component(4);
        double a21 = component(5);
        double a02 = component(6);
        double a12 = component(7);
        double a22 = component(8);

        return a00 * (a11 * a22 - a12 * a21) -
            a01 * (a10 * a22 - a12 * a20) +
            a02 * (a10 * a21 - a11 * a20);
    }

    template <>
    const Matrix3x3
    Matrix3x3::inverse() const {
        double a00 = component(0);
        double a10 = component(1);
        double a20 = component(2);
        double a01 = component(3);
        double a11 = component(4);
        double a21 = component(5);
        double a02 = component(6);
        double a12 = component(7);
        double a22 = component(8);

        double determinant = a00 * (a11 * a22 - a12 * a21) -
            a01 * (a10 * a22 - a12 * a20) +
            a02 * (a10 * a21 - a11 * a20);
        if (determinant == opensolid::Zero()) {
            assert(false);
            return Matrix3x3();
        }
        double reciprocal = 1.0 / determinant;

        return Matrix3x3(
            reciprocal * (a11 * a22 - a12 * a21),
            reciprocal * (a12 * a20 - a10 * a22),
            reciprocal * (a10 * a21 - a11 * a20),
            reciprocal * (a02 * a21 - a01 * a22),
            reciprocal * (a00 * a22 - a02 * a20),
            reciprocal * (a01 * a20 - a00 * a21),
            reciprocal * (a01 * a12 - a02 * a11),
            reciprocal * (a02 * a10 - a00 * a12),
            reciprocal * (a00 * a11 - a01 * a10)
        );
    }
    template <>
    Interval
    IntervalMatrix3x3::determinant() const {
        Interval a00 = component(0);
        Interval a10 = component(1);
        Interval a20 = component(2);
        Interval a01 = component(3);
        Interval a11 = component(4);
        Interval a21 = component(5);
        Interval a02 = component(6);
        Interval a12 = component(7);
        Interval a22 = component(8);

        return a00 * (a11 * a22 - a12 * a21) -
            a01 * (a10 * a22 - a12 * a20) +
            a02 * (a10 * a21 - a11 * a20);
    }

    template <>
    const IntervalMatrix3x3
    IntervalMatrix3x3::inverse() const {
        Interval a00 = component(0);
        Interval a10 = component(1);
        Interval a20 = component(2);
        Interval a01 = component(3);
        Interval a11 = component(4);
        Interval a21 = component(5);
        Interval a02 = component(6);
        Interval a12 = component(7);
        Interval a22 = component(8);

        Interval determinant = a00 * (a11 * a22 - a12 * a21) -
            a01 * (a10 * a22 - a12 * a20) +
            a02 * (a10 * a21 - a11 * a20);
        
        Interval reciprocal = 1.0 / determinant;

        return IntervalMatrix3x3(
            reciprocal * (a11 * a22 - a12 * a21),
            reciprocal * (a12 * a20 - a10 * a22),
            reciprocal * (a10 * a21 - a11 * a20),
            reciprocal * (a02 * a21 - a01 * a22),
            reciprocal * (a00 * a22 - a02 * a20),
            reciprocal * (a01 * a20 - a00 * a21),
            reciprocal * (a01 * a12 - a02 * a11),
            reciprocal * (a02 * a10 - a00 * a12),
            reciprocal * (a00 * a11 - a01 * a10)
        );
    }
}
