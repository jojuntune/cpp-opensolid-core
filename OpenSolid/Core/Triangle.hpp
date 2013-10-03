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
*************************************************************************************/

#pragma once

#include <OpenSolid/Core/Triangle.definitions.hpp>

#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Simplex.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    inline
    Triangle<2>::Triangle() {
    }

    inline
    Triangle<2>::Triangle(const Simplex<2, 3>& other) :
        Simplex<2, 3>(other) {
    }

    inline
    Triangle<2>::Triangle(
        const Point2d& firstVertex,
        const Point2d& secondVertex,
        const Point2d& thirdVertex
    ) {
        Matrix<double, 2, 3> vertices;
        vertices.col(0) = firstVertex.vector();
        vertices.col(1) = secondVertex.vector();
        vertices.col(2) = thirdVertex.vector();
        *this = Simplex<2, 3>(vertices);
    }

    inline
    Triangle<3>::Triangle() {
    }

    inline
    Triangle<3>::Triangle(const Simplex<3, 3>& other) :
        Simplex<3, 3>(other) {
    }

    inline
    Triangle<3>::Triangle(
        const Point3d& firstVertex,
        const Point3d& secondVertex,
        const Point3d& thirdVertex
    ) {
        Matrix3d vertices;
        vertices.col(0) = firstVertex.vector();
        vertices.col(1) = secondVertex.vector();
        vertices.col(2) = thirdVertex.vector();
        *this = Simplex<3, 3>(vertices);
    }
}
