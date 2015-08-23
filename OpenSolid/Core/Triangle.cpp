/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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

#include <OpenSolid/Core/UnitVector.hpp>

#include <iostream>

namespace opensolid
{
    bool
    Triangle2d::contains(const Point2d& point) const {
        double crossProduct0 = detail::crossProduct2d(vertex(0), point, vertex(1));
        double crossProduct1 = detail::crossProduct2d(vertex(1), point, vertex(2));
        double crossProduct2 = detail::crossProduct2d(vertex(2), point, vertex(0));
        return (
            (crossProduct0 <= 0.0 && crossProduct1 <= 0.0 && crossProduct2 <= 0.0) ||
            (crossProduct0 >= 0.0 && crossProduct1 >= 0.0 && crossProduct2 >= 0.0)
        );
    }

    const Triangle2d&
    Triangle2d::UNIT() {
        static Triangle2d result(Point2d::ORIGIN(), Point2d(1, 0), Point2d(0, 1));
        return result;
    }

    double
    Triangle3d::area() const {
        return (vertex(1) - vertex(0)).cross(vertex(2) - vertex(0)).norm() / 2.0;
    }

    UnitVector3d
    Triangle3d::normalVector() const {
        static const double epsilon = std::numeric_limits<double>::epsilon();
        Vector3d vector1 = vertex(1) - vertex(0);
        Vector3d vector2 = vertex(2) - vertex(0);
        Vector3d crossProduct = handedness().sign() * vector1.cross(vector2);
        double squaredNorm1 = vector1.squaredNorm();
        double squaredNorm2 = vector2.squaredNorm();
        double crossProductSquaredNorm = crossProduct.squaredNorm();
        if (crossProductSquaredNorm > epsilon * squaredNorm1 * squaredNorm2) {
            // Cross product is (reasonably) well conditioned - use it to
            // compute the normal vector
            return UnitVector3d((crossProduct / sqrt(crossProductSquaredNorm)).components());
        } else {
            // Cross product is poorly conditioned (i.e., triangle is degenerate
            // or nearly so) - instead of cross product, compute a unit vector
            // perpendicular to the longest of the two edges
            if (squaredNorm1 >= squaredNorm2) {
                return vector1.unitOrthogonal();
            } else {
                return vector2.unitOrthogonal();
            }
        }
    }

    Plane3d
    Triangle3d::plane() const {
        return Plane3d(vertex(0), normalVector());
    }
}
