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

#include <OpenSolid/Core/Tetrahedron.hpp>

#include <OpenSolid/Core/ParametricExpression.hpp>
#include <OpenSolid/Core/Triangle.hpp>

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
                return Triangle3d(vertex(1), vertex(2), vertex(3));
            case 1:
                return Triangle3d(vertex(0), vertex(3), vertex(2));
            case 2:
                return Triangle3d(vertex(3), vertex(0), vertex(1));
            case 3:
                return Triangle3d(vertex(2), vertex(1), vertex(0));
            default:
                assert(false);
                return Triangle3d();
        }
    }

    double
    Tetrahedron3d::volume() const {
        Matrix3d matrix;
        matrix.col(0) = vertex(1) - vertex(0);
        matrix.col(1) = vertex(2) - vertex(0);
        matrix.col(2) = vertex(3) - vertex(0);
        return matrix.determinant() / 6.0;
    }

    Point3d
    Tetrahedron3d::centroid() const {
        return Point3d(
            (vertex(0).vector() + vertex(1).vector() +
                vertex(2).vector() + vertex(3).vector()) / 4.0
        );
    }

    CoordinateSystem3d
    Tetrahedron3d::coordinateSystem() const {
        return CoordinateSystem3d(
            vertex(0),
            vertex(1) - vertex(0),
            vertex(2) - vertex(0),
            vertex(3) - vertex(0)
        );
    }

    Tetrahedron3d
    Tetrahedron3d::Unit() {
        return Tetrahedron3d(
            Point3d::Origin(),
            Point3d(1, 0, 0),
            Point3d(0, 1, 0),
            Point3d(0, 0, 1)
        );
    }

    Tetrahedron3d
    ScalingFunction<Tetrahedron3d>::operator()(
        const Tetrahedron3d& tetrahedron,
        double scale
    ) const {
        return Tetrahedron3d(
            detail::scaled(tetrahedron.vertex(0), scale),
            detail::scaled(tetrahedron.vertex(1), scale),
            detail::scaled(tetrahedron.vertex(2), scale),
            detail::scaled(tetrahedron.vertex(3), scale)
        );
    }

    Tetrahedron3d
    TranslationFunction<Tetrahedron3d>::operator()(
        const Tetrahedron3d& tetrahedron,
        const Vector3d& vector
    ) const {
        return Tetrahedron3d(
            detail::translated(tetrahedron.vertex(0), vector),
            detail::translated(tetrahedron.vertex(1), vector),
            detail::translated(tetrahedron.vertex(2), vector),
            detail::translated(tetrahedron.vertex(3), vector)
        );
    }

    Tetrahedron3d
    TransformationFunction<Tetrahedron3d, 3>::operator()(
        const Tetrahedron3d& tetrahedron,
        const Matrix3d& matrix
    ) const {
        return Tetrahedron3d(
            detail::transformed(tetrahedron.vertex(0), matrix),
            detail::transformed(tetrahedron.vertex(1), matrix),
            detail::transformed(tetrahedron.vertex(2), matrix),
            detail::transformed(tetrahedron.vertex(3), matrix)
        );
    }

    Tetrahedron3d
    MorphingFunction<Tetrahedron3d, 3>::operator()(
        const Tetrahedron3d& tetrahedron,
        const ParametricExpression<3, 3>& morphingExpression
    ) const {
        return Tetrahedron3d(
            detail::morphed(tetrahedron.vertex(0), morphingExpression),
            detail::morphed(tetrahedron.vertex(1), morphingExpression),
            detail::morphed(tetrahedron.vertex(2), morphingExpression),
            detail::morphed(tetrahedron.vertex(3), morphingExpression)
        );
    }
}
