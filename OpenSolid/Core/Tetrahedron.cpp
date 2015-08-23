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

#include <OpenSolid/Core/Tetrahedron.hpp>

namespace opensolid
{
    LineSegment3d
    Tetrahedron3d::edge(int index) const {
        switch (index) {
        case 0:
            return LineSegment3d(vertex(0), vertex(1));
        case 1:
            return LineSegment3d(vertex(1), vertex(2));
        case 2:
            return LineSegment3d(vertex(0), vertex(2));
        case 3:
            return LineSegment3d(vertex(2), vertex(3));
        case 4:
            return LineSegment3d(vertex(0), vertex(3));
        case 5:
            return LineSegment3d(vertex(3), vertex(1));
        default:
            assert(false);
            return LineSegment3d();
        }
    }

    Triangle3d
    Tetrahedron3d::face(int oppositeIndex) const {
        switch (oppositeIndex) {
        case 0:
            return Triangle3d(vertex(1), vertex(2), vertex(3), handedness());
        case 1:
            return Triangle3d(vertex(0), vertex(3), vertex(2), handedness());
        case 2:
            return Triangle3d(vertex(3), vertex(0), vertex(1), handedness());
        case 3:
            return Triangle3d(vertex(2), vertex(1), vertex(0), handedness());
        default:
            assert(false);
            return Triangle3d();
        }
    }

    double
    Tetrahedron3d::volume() const {
        Matrix3d matrix;
        matrix.column(0) = vertex(1).components() - vertex(0).components();
        matrix.column(1) = vertex(2).components() - vertex(0).components();
        matrix.column(2) = vertex(3).components() - vertex(0).components();
        return handedness().sign() * matrix.determinant() / 6.0;
    }

    Point3d
    Tetrahedron3d::centroid() const {
        return vertex(0) + 0.25 * (
            (vertex(1) - vertex(0)) +
            (vertex(2) - vertex(0)) +
            (vertex(3) - vertex(0))
        );
    }

    bool
    Tetrahedron3d::contains(const Point3d& point, double precision) const {
        // TODO
        return false;
    }

    const Tetrahedron3d&
    Tetrahedron3d::UNIT() {
        static Tetrahedron3d result(
            Point3d::ORIGIN(),
            Point3d(1, 0, 0),
            Point3d(0, 1, 0),
            Point3d(0, 0, 1),
            Handedness::RIGHT_HANDED()
        );
        return result;
    }
}
