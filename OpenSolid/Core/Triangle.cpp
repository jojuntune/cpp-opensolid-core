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

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Triangle.hpp>

#include <OpenSolid/Core/ParametricExpression.hpp>
#include <OpenSolid/Core/UnitVector.hpp>

namespace opensolid
{
    double
    Triangle2d::area() const {
        Matrix2x2 matrix;
        matrix.column(0) = vertex(1).components() - vertex(0).components();
        matrix.column(1) = vertex(2).components() - vertex(0).components();
        return matrix.determinant() / 2.0;
    }

    Triangle2d
    Triangle2d::Unit() {
        return Triangle2d(Point2d::Origin(), Point2d(1, 0), Point2d(0, 1));
    }

    double
    Triangle3d::area() const {
        return (vertex(1) - vertex(0)).cross(vertex(2) - vertex(0)).norm() / 2.0;
    }

    UnitVector3d
    Triangle3d::normalVector() const {
        return (vertex(1) - vertex(0)).cross(vertex(2) - vertex(0)).normalized();
    }

    Plane3d
    Triangle3d::plane() const {
        return Plane3d(vertex(0), normalVector());
    }
}
